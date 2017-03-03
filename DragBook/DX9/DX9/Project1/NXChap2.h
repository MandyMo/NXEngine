
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
	class NXChap2 : public NX::DX9Window {
	public:
		NXChap2();
		virtual ~NXChap2();

	public:
		virtual void PostRender();
		virtual void PreRender();
		virtual void Render();

	private:
		virtual void OnInitDX3Succeed();
		virtual void OnTick(NXUInt32 uDelta);

	public:
		struct Vertex {
			Vertex(D3DCOLOR _color = 0,float _x = 0.f, float _y = 0.f, float _z = 0.f):x(_x), y(_y), z(_z), color(_color){}
			float x, y, z;
			D3DCOLOR color;
		};
	private:
		IDirect3DVertexBuffer9		*m_pVB;
		IDirect3DIndexBuffer9		*m_pIB;
		Vertex						m_v[3];
	};
}