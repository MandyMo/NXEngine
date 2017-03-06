
/**
 *  File:      NXChap17_2.h
 *
 *  Author:    张雄(zhangxiong 1025679612@qq.com)
 *  Date:	   2017_03_06
 *  Purpose:   DX Demo3
 */

#pragma once

#include "..\..\NXDX9Window.h"

namespace NX {
	class NXChap17_2 : public NX::DX9Window {
	public:
		NXChap17_2();
		virtual ~NXChap17_2();

	public:
		virtual void PostRender();
		virtual void PreRender();
		virtual void Render();

	private:
		virtual void OnInitDX3Succeed();
		virtual void OnTick(NXUInt32 uDelta);

	public:
		struct Vertex {
			Vertex(float _x, float _y, float _z, float _u1, float _v1, float _u2, float _v2) :
				x(_x), y(_y), z(_z), u1(_u1), v1(_v1), u2(_u2), v2(_v2){
			}
			Vertex() {
				/**trival*/
			}
			float x, y, z;
			float u1, v1;
			float u2, v2;

			static DWORD	FVF;
		};

	private:
		D3DXHANDLE						ViewProjHandle;
		IDirect3DVertexShader9			*m_pVertexShader;
		IDirect3DPixelShader9			*m_pPixelShader;
		D3DXHANDLE						TexAHandle;
		D3DXHANDLE						TexBHandle;
		ID3DXConstantTable				*m_pVertexConstant;
		ID3DXConstantTable				*m_pPixelConstant;
		IDirect3DTexture9				*m_pTexA;
		IDirect3DTexture9				*m_pTexB;
		Vertex							m_v[4];
		IDirect3DVertexBuffer9			*m_pVB;
		IDirect3DIndexBuffer9			*m_pIB;
	};
}