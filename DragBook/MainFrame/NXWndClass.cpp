
/**
 *  File:      NXWndClass.cpp
 *
 *  Author:    ÕÅÐÛ(zhangxiong 1025679612@qq.com)
 *  Date:	   2017_03_02
 *  Purpose:   ×¢²áWindows´°¿ÚÀà
 */

#include "NXWndClass.h"

namespace NX {
	WndClass::WndClass(LPTSTR	lpszClassName) {
		m_wndclass.cbSize = sizeof(m_wndclass);
		m_wndclass.cbClsExtra = 0;
		m_wndclass.cbWndExtra = 0;
		m_wndclass.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
		m_wndclass.hCursor = (HCURSOR)::LoadCursor((HINSTANCE)::GetModuleHandle(NULL), IDC_ARROW);
		m_wndclass.hIcon = (HICON)::LoadIcon((HINSTANCE)::GetModuleHandle(NULL), IDI_APPLICATION);
		m_wndclass.hIconSm = m_wndclass.hIcon;
		m_wndclass.hInstance = (HINSTANCE)::GetModuleHandle(NULL);
		m_wndclass.lpfnWndProc = ::DefWindowProc;
		m_wndclass.lpszClassName = lpszClassName;
		m_wndclass.lpszMenuName = NULL;
		m_wndclass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	}

	WndClass::~WndClass() {}

	WNDCLASSEX&		WndClass::GetWndClass() {
		return	m_wndclass;
	}

	ATOM		WndClass::Register() {
		return	::RegisterClassEx(&m_wndclass);
	}
}