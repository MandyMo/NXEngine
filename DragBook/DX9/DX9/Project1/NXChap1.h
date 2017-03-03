
/**
 *  File:      NXChap1.h
 *
 *  Author:    张雄(zhangxiong 1025679612@qq.com)
 *  Date:	   2017_03_02
 *  Purpose:   DX Demo1
 */

#include "..\..\NXDX9Window.h"

#pragma once

namespace NX {
	class NXChap1 : public NX::DX9Window {
	public:
		NXChap1();
		virtual ~NXChap1();

	public:
		virtual void PostRender();
		virtual void PreRender();
		virtual void Render();
	};
}