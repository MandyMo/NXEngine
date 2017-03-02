
/**
 *  File:      NXDX9Window.cpp
 *
 *  Author:    张雄(zhangxiong 1025679612@qq.com)
 *  Date:	   2017_03_02
 *  Purpose:   封装DX window
 */

#include "NXDX9Window.h"
#include "common\NXLog.h"



NX::DX9Window::DX9Window() {
	/**empty here*/
}

NX::DX9Window::~DX9Window() {
	/**empty here*/
}

bool NX::DX9Window::Create(DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hWndParent, HMENU hMenu, LPVOID lpParam) {
	{//create windows window
		bool bRet = NX::Window::Create(dwExStyle, dwStyle, lpszClassName, lpszWindowName, rtWndArea, hWndParent, hMenu, lpParam);
		glb_GetLog().logToConsole("Create win32 window %s", bRet ? "Succed" : "failed");
	}
	return true;
}

void NX::DX9Window::PreRender() {
	/**empty*/
}

void NX::DX9Window::PostRender() {
	/**empty*/
}

void NX::DX9Window::Render() {
	/**empty*/
}

WPARAM NX::DX9Window::MessageLoop() {
	MSG msg = {0};
	while (msg.message != WM_QUIT) {
		if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		} else {
			PreRender();
			Render();
			PostRender();
		}
	}
	return msg.wParam;
}