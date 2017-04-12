
/**
 *  File:      NXDX9Window.h
 *
 *  Author:    张雄(zhangxiong 1025679612@qq.com)
 *  Date:	   2017_03_02
 *  Purpose:   封装DX window
 */

#pragma once

#include "NXWindow.h"
#include <D3DX9.h>
#include "..\..\engine\common\nxtype.h"
#include "..\..\engine\common\nxcore.h"
#include "..\..\engine\common\NXLog.h"

#pragma comment(lib, "libcpmt.lib")

namespace NX {
	class DX9Window : public NX::Window{
	public:
		DX9Window();
		virtual ~DX9Window();

	public:
		virtual bool Create( DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hWndParent, HMENU hMenu, LPVOID lpParam );
		virtual		WPARAM	MessageLoop();

	public:
		virtual void PostRender();
		virtual void PreRender();
		virtual void Render();

	private:
		virtual void OnInitDX3Succeed();
		virtual void OnTick(NXUInt32	uDelta);

	public:
		inline IDirect3D9*				GetD3D9(){return m_pD3D9;}
		inline IDirect3DDevice9*		GetD3D9Device(){return m_pDevice;}

	public:
		IDirect3D9					*m_pD3D9;
		IDirect3DDevice9			*m_pDevice;
		D3DCAPS9					m_D3dCaps;
		D3DPRESENT_PARAMETERS		m_D3dParameter;
	};

	DX9Window* glb_GetD3DWindow();
	IDirect3DDevice9 *glb_GetD3DDevice();
}