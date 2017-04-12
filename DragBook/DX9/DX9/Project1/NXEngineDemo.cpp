
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
#include "../../engine/entity/NXTerrain.h"
#include "../../engine/entity/NXCube.h"
#include "../../engine/render/NXCamera.h"
#include "../../engine/render/NXEngine.h"

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
	RenderParameter renderer;
	{
		renderer.pMVController        = m_pCamera;
		renderer.pProjectController   = m_pCamera;
		renderer.pDirectX             = GetD3D9();
		renderer.pDXDevice            = GetD3D9Device();
	}

	if (m_pTerrain) {
		m_pTerrain->Render(renderer);
	}

	if (m_pCube) {
		m_pCube->Render(renderer);
	}
}

void NX::NXEngineDemo::OnInitDX3Succeed() {
	//create terrain
	m_pTerrain = new NX::Terrain(1000, 1000, 1.0, 1.0, "");

	{//create camera
		float3  Eye(0, 0, 0);
		Eye.y = m_pTerrain->GetHeight(Eye.x, Eye.z) + 1.6;
		float3  at(Eye + float3(1.f, -1.f, 1.f));
		float3  up(.0f, 1.f, .0f);
		m_pCamera = new PerspectCamera(Eye, at, up, 75.f, MAINFRAME_WIDTH * 1.f / MAINFRAME_HEIGHT, 0.01f, 1000.f);
	}

	{//create cube
		m_pCube = new NX::Cube(float3(1, 1, 1));
		m_pCube->GetTransform().SetRotation(0, 1, 0);
		m_pCube->GetTransform().SetTranslation(0, 3, 0);
	}
	GetCursorPos(&m_CurPos);
}

void NX::NXEngineDemo::OnTick(NXUInt32 uDelta) {
	{//update camera position
		const float Dist = uDelta * 0.002;
		if (KeyDown('W') || KeyDown(VK_UP) || KeyDown('w')) {
			m_pCamera->MoveFront(Dist);
		}

		if (KeyDown('S') || KeyDown(VK_DOWN) || KeyDown('s')) {
			m_pCamera->MoveBack(Dist);
		}

		if (KeyDown('A') || KeyDown(VK_LEFT) || KeyDown('a')) {
			m_pCamera->MoveLeft(Dist);
		}

		if (KeyDown('D') || KeyDown(VK_RIGHT) || KeyDown('d')) {
			m_pCamera->MoveRight(Dist);
		}
	}

	{//update camera angle
		POINT CurPos;
		GetCursorPos(&CurPos);
		if (KeyDown(VK_LBUTTON)) {
			float dx = CurPos.x - m_CurPos.x;
			float dy = CurPos.y - m_CurPos.y;
			dx *= 0.002f;
			dy *= 0.002f;
			m_pCamera->RotateByUpDownAxis(dx);
			m_pCamera->RotateByAxis(m_pCamera->GetRightAxis(), dy);
		}
		m_CurPos = CurPos;
	}

	{//update camera position
		NX::float3 Pos = m_pCamera->GetEyePosition();
		NX::Clamp(Pos.x, 0, m_pTerrain->GetMaxRangeByXAxis());
		NX::Clamp(Pos.z, 0, m_pTerrain->GetMaxRangeByZAxis());
		Pos.y = m_pTerrain->GetHeight(Pos.x, Pos.z) + 1.6f;
		m_pCamera->SetCameraPosition(Pos);
	}

	{
		m_pCube->OnTick(uDelta);
	}
}