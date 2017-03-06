
/**
 *  File:      NXChap17_2.cpp
 *
 *  Author:    张雄(zhangxiong 1025679612@qq.com)
 *  Date:	   2017_03_06
 *  Purpose:   DX Demo3
 */

#include "NXChap17_2.h"

#include "..\..\..\..\engine\common\nxcore.h"
#include "..\..\..\..\engine\common\NXLog.h"
#include "..\..\..\..\engine\math\NXAlgorithm.h"

NX::NXChap17_2::NXChap17_2() {
	ViewProjHandle		=	NULL;
	m_pVertexShader		=	NULL;
	m_pPixelShader		=	NULL;
	TexAHandle			=	NULL;
	TexBHandle			=	NULL;
	m_pVertexConstant	=	NULL;
	m_pPixelConstant	=	NULL;
	m_pTexA				=	NULL;
	m_pTexB				=	NULL;
	m_pIB				=	NULL;
	m_pVB				=	NULL;
}

NX::NXChap17_2::~NXChap17_2() {
	
}

DWORD NX::NXChap17_2::Vertex::FVF = D3DFVF_XYZ | D3DFVF_TEX2;

void NX::NXChap17_2::PostRender() {
	GetD3D9Device()->EndScene();
	GetD3D9Device()->Present(NULL, NULL, NULL, NULL);
}

void NX::NXChap17_2::PreRender() {
	GetD3D9Device()->BeginScene();
	GetD3D9Device()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.f, 0);
}

void NX::NXChap17_2::Render() {
	{//set vertex & index buffer
		Vertex *v;
		m_pVB->Lock(0, 0, (void**)&v, D3DLOCK_DISCARD);
		memcpy(v, m_v, sizeof(m_v));
		m_pVB->Unlock();

		NXUInt16 idx[] = {0, 1, 2, 1, 2, 3};
		NXUInt16 *pI = NULL;
		m_pIB->Lock(0, 0, (void**)&pI, D3DLOCK_DISCARD);
		memcpy(pI, idx, sizeof(idx));
		m_pIB->Unlock();
	}

	{//render
		GetD3D9Device()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		GetD3D9Device()->SetVertexShader(m_pVertexShader);
		GetD3D9Device()->SetPixelShader(m_pPixelShader);
		GetD3D9Device()->SetFVF(Vertex::FVF);
		GetD3D9Device()->SetRenderState(D3DRS_LIGHTING, false);
		GetD3D9Device()->SetStreamSource(0, m_pVB, 0, sizeof(Vertex));
		GetD3D9Device()->SetIndices(m_pIB);
		GetD3D9Device()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 2);
	}
}


void NX::NXChap17_2::OnInitDX3Succeed() {
	ID3DXBuffer *shader = NULL;
	ID3DXBuffer *errorBuffer = NULL;
	do {
		HRESULT hr;
		{//set m_v
			m_v[0] = Vertex(-5,  5, 0, 0, 0, 0, 0);
			m_v[1] = Vertex(-5, -5, 0, 0, 1, 0, 1);
			m_v[2] = Vertex( 5,  5, 0, 1, 0, 1, 0);
			m_v[3] = Vertex( 5, -5, 0, 1, 1, 1, 1);
		}
		{//create two textures
			hr = ::D3DXCreateTextureFromFile(GetD3D9Device(), _T("Textures/sb.jpg"), &m_pTexA);
			if (FAILED(hr)) {
				glb_GetLog().logToConsole("create texture failed");
				break;
			}

			hr = ::D3DXCreateTextureFromFile(GetD3D9Device(), _T("Textures/Women.jpg"), &m_pTexB);
			if (FAILED(hr)) {
				break;
			}
		}

		{//compile shaders
			hr = D3DXCompileShaderFromFile("NXChap17_2_vs.hlsl", NULL, NULL, "Main", "vs_1_1", D3DXSHADER_DEBUG, &shader, &errorBuffer, &m_pVertexConstant);
			if (errorBuffer != NULL) {
				glb_GetLog().logToConsole("compile vertex shader from file failed [%s]", errorBuffer->GetBufferPointer());
				break;
			}
			if (FAILED(hr)) {
				break;
			}
			GetD3D9Device()->CreateVertexShader((DWORD*)shader->GetBufferPointer(), &m_pVertexShader);
			NX::NXSafeRelease(shader);
			NX::NXSafeRelease(errorBuffer);


			hr = D3DXCompileShaderFromFile("NXChap17_2_ps.hlsl", NULL, NULL, "Main", "ps_1_1", D3DXSHADER_DEBUG, &shader, &errorBuffer, &m_pPixelConstant);
			if (errorBuffer != NULL) {
				glb_GetLog().logToConsole("compile pixel shader from file failed [%s]", errorBuffer->GetBufferPointer());
			}
			if (FAILED(hr)) {
				break;
			}
			GetD3D9Device()->CreatePixelShader((DWORD*)shader->GetBufferPointer(), &m_pPixelShader);
		}

		{//get constant handler
			ViewProjHandle	= m_pVertexConstant->GetConstantByName(NULL, "ViewProjMatrix");
			TexAHandle		= m_pPixelConstant->GetConstantByName(NULL, "BaseColor");
			TexBHandle		= m_pPixelConstant->GetConstantByName(NULL, "GlossColor");
		}

		{//create vertex & index buffer
			GetD3D9Device()->CreateVertexBuffer(sizeof(m_v), D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_MANAGED, &m_pVB, NULL);
			GetD3D9Device()->CreateIndexBuffer(6 * sizeof(NXInt16), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB, NULL);
		}
	}while(false);

	NX::NXSafeRelease(shader);
	NX::NXSafeRelease(errorBuffer);
}


void NX::NXChap17_2::OnTick(NXUInt32 uDelta) {
	static float Angle = 0.0f;
	Angle += uDelta * 0.001;
	{
		D3DXMATRIX World;
		D3DXMatrixRotationZ(&World, Angle);
		D3DXMATRIX View;
		D3DXMATRIX Proj;
		D3DXVECTOR3 position(0.f, 0.f, -10.f);
		D3DXVECTOR3 target(0.f, 0.f, 0.f);
		D3DXVECTOR3 up(0.f, 1.f, 0.f);


		D3DXMatrixLookAtLH(&View, &position, &target, &up);
		D3DXMatrixPerspectiveFovLH(&Proj, D3DX_PI * 0.5f, MAINFRAME_WIDTH * 1.0f / MAINFRAME_HEIGHT, 1.0f, 1000.f);
		D3DXMATRIX v = World * View * Proj;
		m_pVertexConstant->SetMatrix(GetD3D9Device(), ViewProjHandle, &v);
	}


	{//attach textures
		UINT count;
		D3DXCONSTANT_DESC desc;
		NX::NXClearStruct(desc);
		m_pPixelConstant->GetConstantDesc(TexAHandle, &desc, &count);
		GetD3D9Device()->SetTexture(desc.RegisterIndex, m_pTexA);

		NX::NXClearStruct(desc);
		m_pPixelConstant->GetConstantDesc(TexBHandle, &desc, &count);
		GetD3D9Device()->SetTexture(desc.RegisterIndex, m_pTexB);
	}
}