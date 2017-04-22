
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
#include "../../../../engine/entity/NXTerrain.h"
#include "../../../../engine/entity/NXCube.h"
#include "../../../../engine/render/NXCamera.h"
#include "../../../../engine/render/NXEngine.h"
#include "../../../../engine/Particle/NXSnowParticleSystem.h"
#include "../../../../engine/entity/NXSky.h"
#include "../../../../engine/entity/NXSphere.h"

#define KeyDown(key) (GetAsyncKeyState(key) & 0x08000)

NX::NXEngineDemo::NXEngineDemo() {
	m_pTerrain        = nullptr;
	m_pCamera         = nullptr;
	m_pSky            = nullptr;
	m_pShere          = nullptr;
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
	GetD3D9Device()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.f, 0);
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

	if (m_pBack) {
		m_pBack->Render(renderer);
	}


	if (m_pFront) {
		m_pFront->Render(renderer);
	}

	if (m_pLeft) {
		m_pLeft->Render(renderer);
	}

	if (m_pRight) {
		m_pRight->Render(renderer);
	}

	if (m_pSky) {
		m_pSky->Render(renderer);
	}

	if (m_pShere) {
		m_pShere->Render(renderer);
	}

	for (int i = 0; i < NX::ArrayLength(m_pKity); ++i) {
		if (m_pKity[i]) {
			m_pKity[i]->Render(renderer);
		}
	}

	if (m_pSnowParticleSystem) {
		m_pSnowParticleSystem->Render(renderer);
	}
}

void NX::NXEngineDemo::OnInitDX3Succeed() {
	//create terrain
	m_pTerrain = new NX::Terrain(200, 200, 0.1f, 0.1f, "");

	{//create camera
		float3  Eye(0, 0, 0);
		Eye.y = m_pTerrain->GetHeight(Eye.x, Eye.z) + 1.6;
		float3  at(Eye + float3(1.f, -1.f, 1.f));
		float3  up(.0f, 1.f, .0f);
		m_pCamera = new PerspectCamera(Eye, at, up, 75.f, MAINFRAME_WIDTH * 1.f / MAINFRAME_HEIGHT, 0.01f, 40000.f);
	}

	{//create cube
		m_pCube = new NX::Cube();
		m_pCube->GetTransform().SetRotation(0, 1, 0);
		m_pCube->GetTransform().SetTranslation(0, 3, 0);
	}


	{
		for (int i = 0; i < NX::ArrayLength(m_pKity); ++i) {
			m_pKity[i] = new NX::Sphere("EngineResouces/pics/sb.jpg", 50, 50, NX::RandFloatInRange(0.2, 1.5) + 0.1);
			m_pKity[i]->GetTransform().SetTranslation(NX::RandFloatInRange(0.f, m_pTerrain->GetMaxRangeByXAxis()), 3 + NX::RandFloatInRange(3, 5), NX::RandFloatInRange(0, m_pTerrain->GetMaxRangeByZAxis()));
		}
	}

	{//create sphere
		m_pShere = new NX::Sphere("EngineResouces/Pics/sun.bmp", 100, 100, 100.f);
		m_pShere->GetTransform().SetTranslation(4000, 1000, 1000);
	}

	{
		m_pLeft = new NX::Cube();
		m_pLeft->GetTransform().SetScale(0.25, 2, m_pTerrain->GetMaxRangeByZAxis()).SetTranslation(-0.125, 1, m_pTerrain->GetMaxRangeByZAxis() * 0.5f);
		m_pLeft->SetTextureFilePath("EngineResouces/bricks/brick1.jpg");

		m_pRight = new NX::Cube();
		m_pRight->GetTransform().SetScale(0.25, 2, m_pTerrain->GetMaxRangeByZAxis()).SetTranslation(0.125f + m_pTerrain->GetMaxRangeByXAxis(), 1, m_pTerrain->GetMaxRangeByZAxis() * 0.5f);
		m_pRight->SetTextureFilePath("EngineResouces/bricks/brick1.jpg");
	}

	{
		m_pFront = new NX::Cube();
		m_pFront->GetTransform().SetScale(m_pTerrain->GetMaxRangeByXAxis(), 2, 0.25).SetTranslation(m_pTerrain->GetMaxRangeByXAxis() * 0.5, 1, -0.125f);
		m_pFront->SetTextureFilePath("EngineResouces/bricks/brick1.jpg");

		m_pBack = new NX::Cube();
		m_pBack->GetTransform().SetScale(m_pTerrain->GetMaxRangeByXAxis(), 2, 0.25).SetTranslation(m_pTerrain->GetMaxRangeByXAxis() * 0.5, 1, 0.125f + m_pTerrain->GetMaxRangeByZAxis());
		m_pBack->SetTextureFilePath("EngineResouces/bricks/brick1.jpg");
	}

	GetCursorPos(&m_CurPos);

	{//create snow system
		std::vector<std::string> TextureSet;
		TextureSet.push_back("EngineResouces/Particle/Snow/particle-snow.png");
		m_pSnowParticleSystem  = new SnowParticleSystem(m_pCamera, 1.5f, 0.35f, 5000, TextureSet);
	}

	{
		std::vector<std::string> v;
		v.push_back("EngineResouces/SkyBox/snowsky/front.jpg");
		v.push_back("EngineResouces/SkyBox/snowsky/back.jpg");
		v.push_back("EngineResouces/SkyBox/snowsky/left.jpg");
		v.push_back("EngineResouces/SkyBox/snowsky/right.jpg");
		v.push_back("EngineResouces/SkyBox/snowsky/top.jpg");
		m_pSky = new SkyBox(v, 20000.f);
	}
}

void NX::NXEngineDemo::OnTick(const float fDelta) {
	{//update camera position
		const float Dist = fDelta * 2;
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
		const float delta = 0.1f;
		NX::Clamp(Pos.x, delta, m_pTerrain->GetMaxRangeByXAxis() - delta);
		NX::Clamp(Pos.z, delta, m_pTerrain->GetMaxRangeByZAxis() - delta);
		Pos.y = m_pTerrain->GetHeight(Pos.x, Pos.z) + 1.6f;
		m_pCamera->SetCameraPosition(Pos);
	}

	{
		m_pCube->OnTick(fDelta);
	}

	{
		m_pSnowParticleSystem->OnTick(fDelta);
	}
}