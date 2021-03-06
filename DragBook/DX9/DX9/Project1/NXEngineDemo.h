﻿
/**
 *  File:      NXEngineDemo.h
 *
 *  Author:    张雄(zhang xiong, 1025679612@qq.com)
 *  Date:	   2017_04_10
 *  Purpose:   DX Demo1
 */

#include "../../../../engine/Window/NXDX9Window.h"
#include "../../../../engine/entity/NXTerrain.h"
#include "../../../../engine/render/NXCamera.h""

#pragma once

namespace NX {
	class NXEngineDemo : public NX::DX9Window {
	public:
		NXEngineDemo();
		virtual ~NXEngineDemo();

	public:
		virtual void PostRender();
		virtual void PreRender();
		virtual void Render();

	private:
		virtual void OnInitDX3Succeed() override;
		virtual void OnTick(float fDelta) override;

		inline class PerspectCamera*          GetCamera() { return m_pCamera; }
		inline class Terrain*                 GetTerrain() { return m_pTerrain; }

	public:
		class Terrain               *m_pTerrain;
		class Cube                  *m_pCube;
		class Cube                  *m_pLeft;
		class Cube                  *m_pRight;
		class Cube                  *m_pFront;
		class Cube                  *m_pBack;
		class PerspectCamera        *m_pCamera;
		class ParticleSystem        *m_pSnowParticleSystem;
		class Sky                   *m_pSky;
		class Sphere                *m_pShere;
		class Sphere                *m_pKity[4];
		POINT                        m_CurPos;
	};
}