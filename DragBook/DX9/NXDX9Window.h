
/**
 *  File:      NXDX9Window.h
 *
 *  Author:    张雄(zhangxiong 1025679612@qq.com)
 *  Date:	   2017_03_02
 *  Purpose:   封装DX window
 */

#include "NXWindow.h"
#include "D3DX9.h"


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
		IDirect3D9					*m_pD3D9;
		IDirect3DDevice9			*m_pDevice;
		D3DCAPS9					m_D3dCaps;
		D3DPRESENT_PARAMETERS		m_D3dParameter;
	};
}