
/**
 *  File:      NXChap1.cpp
 *
 *  Author:    张雄(zhangxiong 1025679612@qq.com)
 *  Date:	   2017_03_02
 *  Purpose:   DX Demo1
 */

#include "NXEngineDemo.h"

#include "..\..\..\..\engine\common\nxcore.h"
#include "..\..\..\..\engine\common\NXLog.h"
#include "..\..\..\..\engine\math\NXAlgorithm.h"

#define KeyDown(key) (GetAsyncKeyState(key) & 0x08000)

NX::NXEngineDemo::NXEngineDemo() {
	m_pTerrain        = nullptr;
	m_pCamera         = nullptr;
}

NX::NXEngineDemo::~NXEngineDemo() {
	/**empty*/
}

void NX::NXEngineDemo::PostRender() {
	GetD3D9Device()->EndScene();
	GetD3D9Device()->Present(NULL, NULL, NULL, NULL);
}

void NX::NXEngineDemo::PreRender() {
	GetD3D9Device()->BeginScene();
	GetD3D9Device()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.f, 0);
}

void NX::NXEngineDemo::Render() {
	if (m_pTerrain) {
		m_pTerrain->Render();
	}
}

void NX::NXEngineDemo::OnInitDX3Succeed() {
	m_pTerrain = new NX::Terrain(1000, 1000, 0.5, 0.5, "");

	{//create camera
		float3 Eye(200.f, m_pTerrain->GetHeight(200.f, 200.f) + 1.6f, 200.f);
		float3  at(Eye + float3(1.f, -1.f, 1.f));
		float3 up(0.f, 1.f, 0.f);
		m_pCamera = new PerspectCamera(Eye, at, up, 75.f, MAINFRAME_WIDTH * 1.f / MAINFRAME_HEIGHT, 0.001f, 1000.f);
	}
	GetCursorPos(&m_CurPos);
}

void NX::NXEngineDemo::OnTick(NXUInt32 uDelta) {
	const float Dist = uDelta * 0.01;
	bool bPressed = false;
	if (KeyDown('W') || KeyDown(VK_UP) || KeyDown('w')) {
		m_pCamera->MoveFront(Dist);
		bPressed = true;
	}
	if (KeyDown('S') || KeyDown(VK_DOWN) || KeyDown('s')) {
		m_pCamera->MoveBack(Dist);
		bPressed = true;
	}
	if (KeyDown('A') || KeyDown(VK_LEFT) || KeyDown('a')) {
		m_pCamera->MoveLeft(Dist);
		bPressed = true;
	}
	if (KeyDown('D') || KeyDown(VK_RIGHT) || KeyDown('d')) {
		m_pCamera->MoveRight(Dist);
		bPressed = true;
	}

	if (KeyDown(VK_CONTROL)) {
		POINT CurPos ;
		GetCursorPos(&CurPos);
		m_pCamera->RotateByUpDownAxis(CurPos.x - m_CurPos.x);
		m_pCamera->RotateByLeftRightAxis(CurPos.y - m_CurPos.y);
	}
	if (bPressed) {
		NX::float3 _pos = m_pCamera->GetEyePosition();
		NX::float3 _dir = m_pCamera->GetEyeDirection();
		printf("{pos [x: %f] [y: %f] [z: %f]} \n", _pos.x, _pos.y, _pos.z);
		printf("{dir [x: %f] [y: %f] [z: %f]} \n", _dir.x, _dir.y, _dir.z);
	}
}

void NX::NXEngineDemo::InitMessageHandler() {
	DX9Window::InitMessageHandler();
	m_mpMessageChain[WM_KEYDOWN] = static_cast<MsgHandler>(&NXEngineDemo::OnKeyDown);
}

LRESULT NX::NXEngineDemo::OnKeyDown(WPARAM wPparam, LPARAM lParam) {
	if (wPparam == VK_ESCAPE) {
		::PostQuitMessage(0);
	}
	return wPparam;
}