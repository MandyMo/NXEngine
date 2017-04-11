
/**
*  File:      NXChap17_3.cpp
*
*  Author:    张雄(zhangxiong 1025679612@qq.com)
*  Date:	  2017_03_08
*  Purpose:   DX9 Effect test
*/

#include "NXChap17_3.h"

#include "..\..\..\..\engine\common\nxcore.h"
#include "..\..\..\..\engine\common\NXLog.h"
#include "..\..\..\..\engine\math\NXAlgorithm.h"

NX::NXChap17_3::NXChap17_3() {
	WorldMatrixHandle   =   nullptr;
	ViewMatrixHandle    =   nullptr;
	ProjMatrixHandle    =   nullptr;
	TexAHandle			=	NULL;
	TexBHandle			=	NULL;
	m_pIB				=	NULL;
	m_pVB				=	NULL;
	m_pVertexDesc		=	NULL;
	m_pTexA				=	NULL;
	m_pTexB				=	NULL;
}

NX::NXChap17_3::~NXChap17_3() {
	
}

void NX::NXChap17_3::PostRender() {
	GetD3D9Device()->EndScene();
	GetD3D9Device()->Present(NULL, NULL, NULL, NULL);
}

void NX::NXChap17_3::PreRender() {
	GetD3D9Device()->BeginScene();
	GetD3D9Device()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.f, 0);

	{//set value
		m_pEffect->SetTexture(TexAHandle, m_pTexA);
	}
}

void NX::NXChap17_3::Render() {
	{//set vertex & index buffer
		Vertex *v;
		m_pVB->Lock(0, 0, (void**)&v, D3DLOCK_DISCARD);
		memcpy(v, m_v, sizeof(m_v));
		m_pVB->Unlock();

		NXUInt32 idx[] = {0, 1, 2, 1, 2, 3};
		NXUInt32 *pI = NULL;
		m_pIB->Lock(0, 0, (void**)&pI, D3DLOCK_DISCARD);
		memcpy(pI, idx, sizeof(idx));
		m_pIB->Unlock();
	}

	{//set transform
		NX::float4X4 World = NX::GetMatrixRotateByZ(Angle);
		m_pEffect->SetMatrixTranspose(WorldMatrixHandle, (D3DXMATRIX*)&World);
		m_pEffect->SetMatrixTranspose(ViewMatrixHandle, (D3DXMATRIX*)&m_pCamera->GetMVMatrix());
		m_pEffect->SetMatrixTranspose(ProjMatrixHandle, (D3DXMATRIX*)&m_pCamera->GetProjectMatrix());
	}

	{//render
		m_pEffect->SetTechnique(TechHandle);
		UINT uPasses;
		m_pEffect->Begin(&uPasses, 0);
		for(int i = 0; i < uPasses; ++i){
			m_pEffect->BeginPass(i);
			GetD3D9Device()->SetVertexDeclaration(m_pVertexDesc);
			GetD3D9Device()->SetStreamSource(0, m_pVB, 0, sizeof(Vertex));
			GetD3D9Device()->SetIndices(m_pIB);
			GetD3D9Device()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 2);
			m_pEffect->EndPass();
		}
	}
}


void NX::NXChap17_3::OnInitDX3Succeed() {
	ID3DXBuffer *shader = NULL;
	ID3DXBuffer *errorBuffer = NULL;
	HRESULT hr;
	do {
		{//vertex declaration
			D3DVERTEXELEMENT9 decl[] = {
				{ 0, 0,                                D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION, 0 },
				{ 0, CLS_MEM_OFFSET(Vertex, TexCoord), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD, 0 },
				{ 0, CLS_MEM_OFFSET(Vertex, Normal),   D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_NORMAL,   0 },
				D3DDECL_END(),
			};

			hr = GetD3D9Device()->CreateVertexDeclaration(decl, &m_pVertexDesc);
		}

		{//set m_v
			m_v[0] = Vertex(0,   0,  0,   0, 0, 0, 0, 0);
			m_v[1] = Vertex(0.5, 0,  0,   0, 1, 0, 1, 0);
			m_v[2] = Vertex(0,   0,  0.5, 1, 0, 1, 0, 0);
			m_v[3] = Vertex(0.5, 0,  0.5, 1, 1, 1, 1, 0);
		}

		{//compile effect files
			hr = ::D3DXCreateEffectFromFile(GetD3D9Device(), "NXChap17_3_effect.hlsl", NULL, NULL, D3DXSHADER_DEBUG, NULL, &m_pEffect, &errorBuffer);
			if (errorBuffer != NULL) {
				glb_GetLog().logToConsole("compile effect file %s", errorBuffer->GetBufferPointer());
				break;
			}

			if (m_pEffect == NULL) {
				break;
			}
		}

		{//get effect handles

			WorldMatrixHandle = m_pEffect->GetParameterByName(NULL, "ModelMatrix");
			ViewMatrixHandle  = m_pEffect->GetParameterByName(NULL, "ViewMatrix");
			ProjMatrixHandle  = m_pEffect->GetParameterByName(NULL, "ProjectMatrix");
			TexAHandle		  = m_pEffect->GetParameterByName(NULL, "BaseColor");
			TechHandle		  = m_pEffect->GetTechniqueByName("TerrainShader");
		}

		{//create textures
			::D3DXCreateTextureFromFile(GetD3D9Device(), "Textures/sb.jpg",		&m_pTexA);
			::D3DXCreateTextureFromFile(GetD3D9Device(), "Textures/Women.jpg",	&m_pTexB);
		}

		{//create vertex & index buffer
			GetD3D9Device()->CreateVertexBuffer(sizeof(m_v), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &m_pVB, NULL);
			GetD3D9Device()->CreateIndexBuffer(6 * sizeof(NXUInt32), D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_pIB, NULL);
		}

		{
			float3  Eye(0, 1.6, 0);
			float3  at(Eye + float3(1.f, -1.f, 1.f));
			float3  up(.0f, 1.f, .0f);
			m_pCamera = new PerspectCamera(Eye, at, up, 75.f, MAINFRAME_WIDTH * 1.f / MAINFRAME_HEIGHT, 0.01f, 1000.f);
		}
	}while(false);

	NX::NXSafeRelease(shader);
	NX::NXSafeRelease(errorBuffer);
}


void NX::NXChap17_3::OnTick(NXUInt32 uDelta) {
	Angle += uDelta * 0.001;
}