/*
*  File:    NXCube.cpp
*
*  author:  ÕÅÐÛ(zhang xiong, 1025679612@qq.com)
*  date:    2017_04_12
*  purpose: define a cube
*/

#include "NXCube.h"
#include "../Window/NXDX9Window.h"
#include "../render/NXDX9TextureManager.h"
#include "../render/NXCamera.h"
#include "../render/NXEngine.h"
#include "../render/NXEffectManager.h"

struct NX::Cube::Vertex{
	Vertex(float _x, float _y, float _z, float _u, float _v):x(_x), y(_y), z(_z), u(_u), v(_v) {
		/**empty here*/
	}

	Vertex(const Vertex &_v): Position(_v.Position), TexCoord(_v.TexCoord){
		/**empty here*/
	}

	union {
		struct {
			float x, y, z;
		};
		float3 Position;
	};

	union {
		struct {
			float u, v;
		};
		float2 TexCoord;
	};
};

NX::Cube::Cube(const Size3D &_size) :m_Size(_size) {
	m_pIndexBuffer        = nullptr;
	m_pVertexBuffer       = nullptr;
	m_pVertexDesc         = nullptr;
	m_pEffect             = NX::EffectManager::Instance().GetEffect("../../../../engine/Shaders/DirectX/Cube3D_Effect.hlsl");
	{
		DX9Window *pWindow = glb_GetD3DWindow();
		pWindow->GetD3D9Device()->CreateIndexBuffer(sizeof(NXUInt16) * 36, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIndexBuffer, NULL);
		pWindow->GetD3D9Device()->CreateVertexBuffer(sizeof(Vertex) * 8, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL);
		D3DVERTEXELEMENT9 VertexDesc[] = {
			{0, CLS_MEM_OFFSET(Vertex, x), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
			{0, CLS_MEM_OFFSET(Vertex, u), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
			D3DDECL_END(),
		};
		pWindow->GetD3D9Device()->CreateVertexDeclaration(VertexDesc, &m_pVertexDesc);
	}
}

NX::Cube::~Cube() {
	NX::NXSafeRelease(m_pIndexBuffer);
	NX::NXSafeRelease(m_pVertexBuffer);
	NX::NXSafeRelease(m_pEffect);
}

void NX::Cube::Render(struct RenderParameter &renderer) {
	DX9Window *pWindow = glb_GetD3DWindow();
	pWindow->GetD3D9Device()->SetVertexDeclaration(m_pVertexDesc);

	{//vb
		Size3D sz = m_Size * 0.5f;
		Vertex v[8] = {
			Vertex(sz.x,  sz.y,  sz.z,  0, 0),
			Vertex(sz.x, -sz.y,  sz.z,  1, 0),
			Vertex(sz.x, -sz.y, -sz.z,  0, 1),
			Vertex(sz.x,  sz.y, -sz.z,  1, 1),
			Vertex(-sz.x, sz.y, -sz.z,  0, 0),
			Vertex(-sz.x, sz.y,  sz.z,  1, 0),
			Vertex(-sz.x,-sz.y,  sz.z,  0, 1),
			Vertex(-sz.z,-sz.y, -sz.z,  1, 1),
		};

		void *pBase = NULL;
		m_pVertexBuffer->Lock(0, 0, &pBase, D3DLOCK_DISCARD);
		memcpy(pBase, v, sizeof(v));
		m_pVertexBuffer->Unlock();
	}

	{//ib
		NXUInt16 idx[][3] = {
			{0, 1, 2}, {0, 2, 3},
			{0, 3, 4}, {0, 4, 5},
			{4, 5, 6}, {4, 6, 7},
			{1, 6, 7}, {1, 7, 2},
			{0, 1, 6}, {0, 6, 5},
			{2, 3, 7}, {3, 7, 4},
		};

		void *pBase = nullptr;
		m_pIndexBuffer->Lock(0, 0, &pBase, D3DLOCK_DISCARD);
		memcpy(pBase, idx, sizeof(idx));
		m_pIndexBuffer->Unlock();
	}
	
	{//shader variables
		m_pEffect->SetMatrixTranspose(m_pEffect->GetParameterByName(NULL, "MVP"), (D3DXMATRIX*)&(renderer.pProjectController->GetProjectMatrix() * renderer.pMVController->GetMVMatrix() * GetTransform().GetTransformMatrix()));
		m_pEffect->SetTexture(m_pEffect->GetParameterByName(NULL, "BaseColor"), DX9TextureManager::Instance().GetTexture("../../../../engine/EngineResouces/Road/dirt01.jpg"));
	}

	{//commit to gpu
		m_pEffect->SetTechnique(m_pEffect->GetTechniqueByName("Cube3DShader"));
		UINT uPasses = 0;
		m_pEffect->Begin(&uPasses, 0);
		for (int i = 0; i < uPasses; ++i) {
			pWindow->GetD3D9Device()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(Vertex));
			pWindow->GetD3D9Device()->SetIndices(m_pIndexBuffer);
			m_pEffect->BeginPass(i);
			pWindow->GetD3D9Device()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 36, 0, 12);
			m_pEffect->EndPass();
		}
	}
}

NX::ENTITY_TYPE NX::Cube::GetEntityType() {
	return ENTITY_TYPE_CUBE3D;
}

void NX::Cube::OnTick(const float fDelta) {
	GetTransform().SetRotation(GetTransform().GetRotation() + float3(0, fDelta, 0));
}