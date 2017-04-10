
/**
 *  File:      NXEngineDemo.h
 *
 *  Author:    张雄(zhang xiong, 1025679612@qq.com)
 *  Date:	   2017_04_10
 *  Purpose:   DX Demo1
 */

#include "..\..\NXDX9Window.h"
#include "../../engine/entity/NXTerrain.h"
#include "../../engine/render/NXCamera.h"

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
		virtual void OnTick(NXUInt32 uDelta) override;
		virtual void InitMessageHandler() override;
		virtual LRESULT OnKeyDown(WPARAM wPparam, LPARAM lParam);

	public:
		NX::Terrain				*m_pTerrain;
		NX::PerspectCamera		*m_pCamera;
		POINT					m_CurPos;
	};
}