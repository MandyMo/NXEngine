
/**
 *  File:      NXDX9Window.cpp
 *
 *  Author:    张雄(zhangxiong 1025679612@qq.com)
 *  Date:	   2017_03_02
 *  Purpose:   封装DX window
 */

#include "NXDX9Window.h"
#include "common\NXLog.h"
#include "System\NXSystem.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")

static NX::DX9Window* pD3DWindow = NULL;

NX::DX9Window::DX9Window() {
	m_pD3D9				= NULL;
	m_pDevice			= NULL;
	memset(&m_D3dParameter, 0, sizeof(m_D3dParameter));
	NX::NXZeroMemory(&m_D3dParameter);
	NX::NXZeroMemory(&m_D3dCaps);
	pD3DWindow = this;
}

NX::DX9Window::~DX9Window() {
	if (m_pDevice) {
		m_pDevice->Release();
	}

	if (m_pD3D9) {
		m_pD3D9->Release();
	}
}

bool NX::DX9Window::Create(DWORD dwExStyle, DWORD dwStyle, LPTSTR lpszClassName, LPTSTR lpszWindowName, RECT rtWndArea, HWND hWndParent, HMENU hMenu, LPVOID lpParam) {
	do{
		{//create windows window
			bool bRet = NX::Window::Create(dwExStyle, dwStyle, lpszClassName, lpszWindowName, rtWndArea, hWndParent, hMenu, lpParam);
			glb_GetLog().logToConsole("Create win32 window %s", bRet ? "Succeed" : "failed");
			if (!bRet) {
				break;
			}
		}

		{//init D3D9
			m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
			glb_GetLog().logToConsole("CreateD3D9 %s" , m_pD3D9 != NULL ? "Succeed" :"failed");
			if (!m_pD3D9) {
				break;
			}

			m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3dCaps);

			glb_GetLog().logToConsole("Hardware T&L supported: %s", m_D3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ? "yes" : "no");

			if (!(m_D3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)) {
				break;
			}

			glb_GetLog().logToConsole("You have %d monitors.", m_pD3D9->GetAdapterCount());

			m_D3dParameter.BackBufferWidth				= MAINFRAME_WIDTH;
			m_D3dParameter.BackBufferHeight				= MAINFRAME_HEIGHT;
			m_D3dParameter.BackBufferFormat				= D3DFMT_A8R8G8B8;
			m_D3dParameter.BackBufferCount				= 1;
			m_D3dParameter.MultiSampleQuality			= 0;
			m_D3dParameter.SwapEffect					= D3DSWAPEFFECT_DISCARD;
			m_D3dParameter.hDeviceWindow				= GetHwnd();
			m_D3dParameter.Windowed						= true;
			m_D3dParameter.EnableAutoDepthStencil		= true;
			m_D3dParameter.AutoDepthStencilFormat		= D3DFMT_D24S8;
			m_D3dParameter.Flags						= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
			m_D3dParameter.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
			m_D3dParameter.PresentationInterval			= D3DPRESENT_INTERVAL_IMMEDIATE;

			HRESULT hr = m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT,  D3DDEVTYPE_HAL, GetHwnd(), D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_D3dParameter, &m_pDevice);
			glb_GetLog().logToConsole("Create D3DDevice %s", FAILED(hr) ? "failed" : "succeed");
			if (FAILED(hr)) {
				break;
			}

			OnInitDX3Succeed();

			return true;
		}
	}while(false);
	return false;
}

void NX::DX9Window::PreRender() {
	/**empty*/
}

void NX::DX9Window::PostRender() {
	/**empty*/
}

void NX::DX9Window::Render() {
	do{
		m_pDevice->BeginScene();
		D3DSURFACE_DESC surfacedesc;
		IDirect3DSurface9 *_surface = NULL;
		m_pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &_surface);
		_surface->GetDesc(&surfacedesc);
		if (_surface == NULL) {
			break;
		}

		D3DLOCKED_RECT lockedrect;
		_surface->LockRect(&lockedrect, 0, 0);
		DWORD *pImageData = (DWORD *)lockedrect.pBits;
		for (int i = 0; i < surfacedesc.Height; i++) {
			for (int j = 0; j < surfacedesc.Width; j++) {
				int index = i * lockedrect.Pitch / 4 + j;
				pImageData[index] = 0xFF808080; 
			}
		}

		_surface->UnlockRect();
	}while(false);
	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, NULL, NULL);
}

WPARAM NX::DX9Window::MessageLoop() {
	MSG msg = {0};
	while (msg.message != WM_QUIT) {
		if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		} else {
			static NXUInt64	uPreTickedTime = NX::System::Instance().GetMillSecondsFromSystemStart();
			NXUInt64 uNowTickedTime = NX::System::Instance().GetMillSecondsFromSystemStart();
			OnTick(uNowTickedTime - uPreTickedTime);
			uPreTickedTime = uNowTickedTime;
			PreRender();
			Render();
			PostRender();
		}
	}
	return msg.wParam;
}

void NX::DX9Window::OnInitDX3Succeed() {
	/**empty*/
}

void NX::DX9Window::OnTick(NXUInt32	uDelta) {

}

NX::DX9Window* NX::glb_GetD3DWindow() {
	return pD3DWindow;
}

IDirect3DDevice9 * NX::glb_GetD3DDevice() {
	return NX::glb_GetD3DWindow()->GetD3D9Device();
}