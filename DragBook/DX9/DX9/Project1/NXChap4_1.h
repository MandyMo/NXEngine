
/**
 *  File:      NXChap4_1.h
 *
 *  Author:    张雄(zhangxiong 1025679612@qq.com)
 *  Date:	   2017_03_08
 *  Purpose:   DX9 X File test
 */

#pragma once

#include "..\..\NXDX9Window.h"
#include <vector>
#include <string>

namespace NX {
	class NXChap4_1 : public NX::DX9Window {
	public:
		class Animation;

	public:
		NXChap4_1();
		virtual ~NXChap4_1();

	public:
		virtual void PostRender();
		virtual void PreRender();
		virtual void Render();

	private:
		virtual void OnInitDX3Succeed();
		virtual void OnTick(NXUInt32 uDelta);

	private:
		Animation		*m_pAnimation;
	};
}