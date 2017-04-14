/*
*  File:    NXTerrain.cpp
*
*  author:  张雄(zhang xiong, 1025679612@qq.com)
*  date:    2017_04_09
*  purpose: define Terrain, A terrain is the surface that the player can walk on
*/


#include "NXTerrain.h"
#include "../math/NXAlgorithm.h"
#include "../../engine/entity/NXTerrain.h"
#include "../../engine/render/NXCamera.h"
#include "../render/NXDX9TextureManager.h"
#include "../render/NXEngine.h"
#include "../render/NXEffectManager.h"
#include "../common/NXLog.h"

namespace NX {
	extern IDirect3DDevice9 * glb_GetD3DDevice();
}

NX::Terrain::Terrain(const int Row, const int Col, const float dx, const float dz, const std::string &strTextureFilePath) {
	m_RowCount                  =     Row;
	m_ColCount                  =     Col;
	m_dx                        =     dx;
	m_dz                        =     dz;
	m_Width                     =     m_dx * (m_RowCount - 1);
	m_Height                    =     m_dz * (m_ColCount - 1);
	m_strTextureFilePath        =     strTextureFilePath;
	m_pVertexData               =     nullptr;
	m_pVertexDesc               =     nullptr;
	m_pEffect                   =     nullptr;
	m_pVertexBuffer             =     nullptr;
	m_pIndexBuffer              =     nullptr;

	CreateVertexs();
	CompileEffectFile();
	CreateVertexAndIndexBuffer();
}

NX::Terrain::~Terrain() {
	NX::NXSafeDeleteArray(m_pVertexData);
	NX::NXSafeDeleteArray(m_pVertexData);
	NX::NXSafeRelease(m_pVertexDesc);
	NX::NXSafeRelease(m_pEffect);
	NX::NXSafeRelease(m_pVertexBuffer);
	NX::NXSafeRelease(m_pIndexBuffer);
}

float NX::Terrain::GetHeight(const float x, const float y) const {
	NXAssert(x >= 0 && x <= m_Width && y >=0 && y <= m_Height);
	int r = x / m_dx, c = y / m_dz;
	float dr = x - r * m_dx, dc = y - c * m_dz;
	int idx = r * m_RowCount + c;
	if (dr / m_dx + dc / m_dz >= 1.0f) {
		return GetHeight(m_pVertexData[idx + m_RowCount].Position, m_pVertexData[idx + m_RowCount + 1].Position, m_pVertexData[idx + 1].Position, x, y);
	} else {
		return GetHeight(m_pVertexData[idx + m_RowCount].Position, m_pVertexData[idx].Position, m_pVertexData[idx + 1].Position, x, y);
	}
}

float NX::Terrain::GetHeight(float3 &pA, float3 &pB, float3 &pC, const float x, const float z) const{
	Matrix<float, 2, 2> M;
	float2 V;
	{
		M[0][0] = pA.x - pC.x, M[0][1] = pB.x - pC.x;
		M[1][0] = pA.z - pC.z, M[1][1] = pB.z - pC.z;
		V[0] = x - pC.x, V[1] = z - pC.z;
		auto result = SolveEquation(M, V);
		auto cof = result.second;
		return cof[0] * pA.y + cof[1] * pB.y + (1.f - cof[0] - cof[1]) * pC.y;
	}
}

void NX::Terrain::Render(struct RenderParameter &renderer) {
	glb_GetD3DDevice()->SetVertexDeclaration(m_pVertexDesc);
	m_pEffect->SetMatrixTranspose(m_pEffect->GetParameterByName(NULL, "ModelMatrix"),   (D3DXMATRIX*)(&GetTransform().GetTransformMatrix()));
	m_pEffect->SetMatrixTranspose(m_pEffect->GetParameterByName(NULL, "ViewMatrix"),    (D3DXMATRIX*)&renderer.pMVController->GetMVMatrix());
	m_pEffect->SetMatrixTranspose(m_pEffect->GetParameterByName(NULL, "ProjectMatrix"), (D3DXMATRIX*)&renderer.pProjectController->GetProjectMatrix());

	{//commit data
		if (m_pVertexBuffer) {
			void *pBase = nullptr;
			m_pVertexBuffer->Lock(0, 0, &pBase, D3DLOCK_DISCARD);
			if (pBase != NULL) {
				memcpy(pBase, m_pVertexData, sizeof(Vertex) * m_RowCount *m_ColCount);
			}
			m_pVertexBuffer->Unlock();
		}
	}

	{//set HLSL variable
		m_pEffect->SetTexture(m_pEffect->GetParameterByName(NULL, "RoadTexture"), DX9TextureManager::Instance().GetTexture("../../../../engine/EngineResouces/Road/dirt01.jpg"));
		m_pEffect->SetTexture(m_pEffect->GetParameterByName(NULL, "GrassTexture"), DX9TextureManager::Instance().GetTexture("../../../../engine/EngineResouces/Grass/Grass01.jpg"));
	}

	{//render
		m_pEffect->SetTechnique(m_pEffect->GetTechniqueByName("TerrainShader"));
		UINT uPass;
		m_pEffect->Begin(&uPass, 0);
		for(int i = 0; i < uPass; ++i){
			m_pEffect->BeginPass(i);
			renderer.pDXDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(Vertex));
			renderer.pDXDevice->SetIndices(m_pIndexBuffer);
			renderer.pDXDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, (m_RowCount - 1) * (m_ColCount - 1) * 6, 0, (m_RowCount - 1) * (m_ColCount - 1) * 2);
			m_pEffect->EndPass();
		}
	}
}

NX::Terrain::Vertex&	NX::Terrain::GetVertex(const int r, const int c) {
	NXAssert(r >= 0 && r < m_RowCount && c >= 0 && c< m_ColCount);
	return m_pVertexData[r * m_RowCount + c];
}

void NX::Terrain::CreateVertexs() {
	NXAssert(m_RowCount > 0 && m_ColCount > 0);

	{//create vertex data
		m_pVertexData = new Vertex[m_RowCount * m_ColCount];
		Vertex *pVertex = m_pVertexData;
		for (int r = 0; r < m_RowCount; ++r) {
			for (int c = 0; c < m_ColCount; ++c) {
				*pVertex++ = Vertex(r * m_dx, 0, c * m_dz, r & 1, c & 1, .0f, 0.f, .0f);
			}
		}
	}

	{//set height
		for (int r = 0; r < m_RowCount; ++r) {
			for (int c = 0; c < m_ColCount; ++c) {
				GetVertex(r, c).y = NX::RandFloatInRange(0.2, 0.6);
			}
		}
	}

	{//calculate normals
		for (int r = 0; r < m_RowCount; ++r) {
			for (int c = 0; c < m_ColCount; ++c) {
				GetVertex(r, c).Normal = GetNormalized(GetVertex(r, c).Position);
			}
		}
	}
}


NX::ENTITY_TYPE NX::Terrain::GetEntityType() {
	return ENTITY_TYPE::ENTITY_TYPE_TERRAIN;
}

void NX::Terrain::OnTick(const float fDelta) {

}

bool NX::Terrain::CompileEffectFile() {
	const char *pszEffectFilePath = "../../../../engine/Shaders/DirectX/Terrain_Effect.hlsl";
	m_pEffect = NX::EffectManager::Instance().GetEffect(pszEffectFilePath);

	{
		D3DVERTEXELEMENT9 VertexDescs[] = {
			{ 0, 0,                                D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION, 0 },
			{ 0, CLS_MEM_OFFSET(Vertex, TexCoord), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD, 0 },
			{ 0, CLS_MEM_OFFSET(Vertex, Normal),   D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_NORMAL,   0 },
			D3DDECL_END(),
		};
		glb_GetD3DDevice()->CreateVertexDeclaration(VertexDescs, &m_pVertexDesc);
	}
	return true;
}

void NX::Terrain::CreateVertexAndIndexBuffer() {
	HRESULT hr;
	do {
		hr = glb_GetD3DDevice()->CreateVertexBuffer(sizeof(Vertex) * m_RowCount *m_ColCount, D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);
		if (FAILED(hr) || !m_pVertexBuffer) {
			glb_GetLog().logToConsole("Create terrain vertex buffer failed");
			break;
		}

		hr = glb_GetD3DDevice()->CreateIndexBuffer(sizeof(int) * (m_RowCount - 1) * (m_ColCount - 1) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_pIndexBuffer, NULL);
		if (FAILED(hr) || !m_pIndexBuffer) {
			glb_GetLog().logToConsole("Create terrain index buffer failed");
			break;
		}

		NXUInt32 *pIndex  = new NXUInt32[(m_RowCount - 1) * (m_ColCount - 1) * 6];
		NXUInt32 *pWriter = pIndex;
		for (int r = 0; r < m_RowCount - 1; ++r) {
			for (int c = 0; c < m_ColCount - 1; ++c) {
				int idx = r * m_RowCount + c;
				*pWriter++ = idx;
				*pWriter++ = idx + 1;
				*pWriter++ = idx + m_RowCount;
				*pWriter++ = idx + m_RowCount;
				*pWriter++ = idx + 1;
				*pWriter++ = idx + m_RowCount + 1;
			}
		}
		void *pBase = NULL;
		m_pIndexBuffer->Lock(0, 0, &pBase, D3DLOCK_DISCARD);
		if(pBase != NULL){
			memcpy(pBase, pIndex, sizeof(int) * (m_RowCount - 1) * (m_ColCount - 1) * 6);
		}
		m_pIndexBuffer->Unlock();
		delete[] pIndex;
	}while(false);
}

float NX::Terrain::GetMaxRangeByXAxis() const {
	return m_Width;
}

float NX::Terrain::GetMaxRangeByZAxis() const {
	return m_Height;
}