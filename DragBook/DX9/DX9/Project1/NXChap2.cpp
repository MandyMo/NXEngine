
/**
 *  File:      NXChap1.cpp
 *
 *  Author:    张雄(zhangxiong 1025679612@qq.com)
 *  Date:	   2017_03_02
 *  Purpose:   DX Demo1
 */

#include "NXChap2.h"

#include "..\..\..\..\engine\common\nxcore.h"
#include "..\..\..\..\engine\common\NXLog.h"
#include "..\..\..\..\engine\math\NXAlgorithm.h"

NX::NXChap2::NXChap2() {
	/**empty*/
}

NX::NXChap2::~NXChap2() {
	/**empty*/
}

void NX::NXChap2::PostRender() {
	GetD3D9Device()->EndScene();
	GetD3D9Device()->Present(NULL, NULL, NULL, NULL);
}

void NX::NXChap2::PreRender() {
	GetD3D9Device()->BeginScene();
	GetD3D9Device()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.f, 0);
}

void NX::NXChap2::Render() {
	{//fill vb data
		Vertex *v = NULL;
		m_pVB->Lock(0, 0, (void**)&v, 0);
		memcpy(v, m_v, sizeof(m_v));
		m_pVB->Unlock();
	}

	{//fill ib data
		NXUInt16 idx[3] = {0, 1, 2};
		NXUInt16 *pI = NULL;
		m_pIB->Lock(0, 0, (void**)&pI, 0);
		memcpy(pI, idx, sizeof(idx));
		m_pIB->Unlock();
	}

	{//set world matrix
		D3DXMATRIX v;
		D3DXMatrixTranslation(&v, -3.0f, 0, 0);
		GetD3D9Device()->SetTransform(D3DTS_WORLD, &v);
	}

	{//set view matrix
		D3DXVECTOR3   at(0, 0, -3);
		D3DXVECTOR3   target(0, 0, 0);
		D3DXVECTOR3   up(0, 1, 0);
		D3DXMATRIX	  v;

		D3DXMatrixLookAtLH(&v, &at, &target, &up);

		GetD3D9Device()->SetTransform(D3DTS_VIEW, &v);
	}


	{//set projection matrix
		D3DXMATRIX v;
		D3DXMatrixPerspectiveFovLH(&v, D3DX_PI * 0.5f, MAINFRAME_WIDTH *1.f / MAINFRAME_HEIGHT, 1.f, 1000.f);
		GetD3D9Device()->SetTransform(D3DTS_PROJECTION, &v);
	}

	{//set render state
		GetD3D9Device()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		GetD3D9Device()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		GetD3D9Device()->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	{//commit data
		GetD3D9Device()->SetStreamSource(0, m_pVB, 0, sizeof(Vertex));
		GetD3D9Device()->SetIndices(m_pIB);
		GetD3D9Device()->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

		GetD3D9Device()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 3, 0, 1);
	}

	{//set world matrix
		D3DXMATRIX v;
		D3DXMatrixTranslation(&v, 3.0f, 0, 0);
		GetD3D9Device()->SetTransform(D3DTS_WORLD, &v);
		GetD3D9Device()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
		GetD3D9Device()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 3, 0, 1);
	}
}


void NX::NXChap2::OnInitDX3Succeed() {
	m_pIB	=	NULL;
	m_pVB	=	NULL;
	NX::NXZeroArray(m_v);

	do {
		{//create vertex
			m_v[0] = Vertex(0xffff0000, -1.f, -1.f, 1.f);
			m_v[1] = Vertex(0xff00ff00, -1.f, 1.f, 1.f);
			m_v[2] = Vertex(0xff0000ff, 1.f, 1.f, 1.f);
		}

		{//create vb
			GetD3D9Device()->CreateVertexBuffer(sizeof(m_v), D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_DIFFUSE, D3DPOOL_MANAGED, &m_pVB, NULL);
			glb_GetLog().logToConsole("create vb %s", m_pVB != NULL ? "succeed" : "failed");
			if (m_pVB == NULL) {
				break;
			}
		}

		{//create ib
			GetD3D9Device()->CreateIndexBuffer(sizeof(NXUInt16) * 3, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB, NULL);
			glb_GetLog().logToConsole("create ib %s", m_pIB != NULL ? "succeed" : "failed");
			if (m_pIB == NULL) {
				break;
			}
		}

		return;
	}while(false);

	NX::NXSafeRelease(m_pIB);
	NX::NXSafeRelease(m_pVB);
}


void NX::NXChap2::OnTick(NXUInt32 uDelta) {

}