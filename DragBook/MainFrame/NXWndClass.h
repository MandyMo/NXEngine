
/**
 *  File:      NXWndClass.h
 *
 *  Author:    ÕÅÐÛ(zhangxiong 1025679612@qq.com)
 *  Date:	   2017_03_02
 *  Purpose:   ×¢²áWindows´°¿ÚÀà
 */

#ifndef		__ZX_WNDCLASS_H__
#define		__ZX_WNDCLASS_H__

#include "NXHeader.h"

namespace NX{
	class	WndClass {
	public:
		WndClass(LPTSTR	lpszClassName = _T("MyApplication"));
		~WndClass();
	public:
		WNDCLASSEX&	GetWndClass();
		ATOM		Register();
	public:
		WNDCLASSEX	m_wndclass;
	};
}

#endif