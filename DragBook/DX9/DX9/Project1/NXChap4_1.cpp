
/**
*  File:      NXChap4_1.cpp
*
*  Author:    张雄(zhangxiong 1025679612@qq.com)
*  Date:	  2017_03_14
*  Purpose:   DX animationset
*/

#include "NXChap4_1.h"
#include "../../../../engine/Render/NXDX9TextureManager.h"

class NX::NXChap4_1::Animation {
public:
	Animation() {
		m_pAnimation	= NULL;
		m_fDeltaTime	= 0.f;
		m_pLine			= NULL;
		CreateAnimation();
	}

	virtual ~Animation() {
		NX::NXSafeRelease(m_pAnimation);
		NX::NXSafeRelease(m_pLine);
	}

public:
	void Render() {
		D3DXVECTOR3 sc;
		D3DXVECTOR3 ps;
		m_pAnimation->GetSRT(m_fDeltaTime, 0, &sc, NULL, &ps);
		m_pLine->SetWidth(sc.x  * 20.f);
		m_pLine->Begin();

		{//render line
			float sz = sc.x * 20.f;

			D3DVIEWPORT9	vp;
			glb_GetD3DDevice()->GetViewport(&vp);

			ps.x *= vp.Width;
			ps.y *= vp.Height;

			D3DXVECTOR2 line[] = {
				D3DXVECTOR2(ps.x - sz * 0.5f, ps.y),
				D3DXVECTOR2(ps.x + sz * 0.5f, ps.y),
			};
			m_pLine->Draw(line, 2, 0xffff0000);
		}
		m_pLine->End();
	}

	void OnTick(const NXUInt32	dwDelta) {
		m_fDeltaTime += dwDelta * 0.001f;
		float fPeriod = m_pAnimation->GetPeriod();
		if (m_fDeltaTime > fPeriod) {
			m_fDeltaTime -= fPeriod;
		}
	}

private:
	void CreateAnimation() {
		D3DXCreateLine(glb_GetD3DDevice(), &m_pLine);
		D3DXCreateKeyframedAnimationSet("AnimationSet", 500, D3DXPLAY_PINGPONG, 1, 0, NULL, &m_pAnimation);
		D3DXKEY_VECTOR3	sc[3];
		{//init scale animation
			sc[0] = {0, D3DXVECTOR3(.1f, .1f, .1f)};
			sc[1] = {1000, D3DXVECTOR3(4.f, 4.f, 4.f)};
			sc[2] = {2000, D3DXVECTOR3(.5f, .5f, .5f)};
		}
		
		D3DXKEY_VECTOR3		ps[3];
		{//init position animation
			ps[0] = {0, D3DXVECTOR3(0.2, 0.2, 0.f)};
			ps[1] = {1200, D3DXVECTOR3(0.8f, 0.5f, 0.f)};
			ps[2] = {2000, D3DXVECTOR3(0.5f, 0.9f, 0.f)};
		}
		m_pAnimation->RegisterAnimationSRTKeys("AnimationA", 3, 0, 3, sc, NULL, ps, NULL);

	}

private:
	ID3DXKeyframedAnimationSet		*m_pAnimation;
	float							 m_fDeltaTime;
	ID3DXLine						*m_pLine;
};


NX::NXChap4_1::NXChap4_1() {
	m_pAnimation = NULL;
}

NX::NXChap4_1::~NXChap4_1() {
	delete m_pAnimation;
}


void NX::NXChap4_1::PostRender() {
	GetD3D9Device()->EndScene();
	GetD3D9Device()->Present(NULL, NULL, NULL, NULL);
}

void NX::NXChap4_1::PreRender() {
	GetD3D9Device()->BeginScene();
	GetD3D9Device()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.f, 0);
}

void NX::NXChap4_1::Render() {
	m_pAnimation->Render();
}

void NX::NXChap4_1::OnInitDX3Succeed() {
	m_pAnimation = new Animation();
}

void NX::NXChap4_1::OnTick(NXUInt32 uDelta) {
	m_pAnimation->OnTick(uDelta);
}