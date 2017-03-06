
/**
 *  File:      NXChap1.cpp
 *
 *  Author:    张雄(zhangxiong 1025679612@qq.com)
 *  Date:	   2017_03_02
 *  Purpose:   DX Demo1
 */

#include "NXChap17_1.h"

#include "..\..\..\..\engine\common\nxcore.h"
#include "..\..\..\..\engine\common\NXLog.h"
#include "..\..\..\..\engine\math\NXAlgorithm.h"

NX::NXChap17_1::NXChap17_1() {
	DiffuseShader = NULL;
	DiffuseConstTable = NULL;
	Teapot = NULL;;
	ViewMatrixHandle = NULL;
	ViewProjMatirxHandle = NULL;
	AmbientMtrlHandle = NULL;
	DiffuseMtrlHandle = NULL;
	LightDirHandle = NULL;
}

NX::NXChap17_1::~NXChap17_1() {
	
}

void NX::NXChap17_1::PostRender() {
	GetD3D9Device()->EndScene();
	GetD3D9Device()->Present(NULL, NULL, NULL, NULL);
}

void NX::NXChap17_1::PreRender() {
	GetD3D9Device()->BeginScene();
	GetD3D9Device()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.f, 0);
}

void NX::NXChap17_1::Render() {
	GetD3D9Device()->SetVertexShader(DiffuseShader);
	Teapot->DrawSubset(0);
}


void NX::NXChap17_1::OnInitDX3Succeed() {
	ID3DXBuffer *shader = NULL;
	ID3DXBuffer *errorBuffer = NULL;
	do {
		HRESULT hr;

		{//create teapot
			D3DXCreateTeapot(GetD3D9Device(), &Teapot, NULL);
			glb_GetLog().logToConsole("create teapot %s", Teapot != NULL ? "succeed" : "failed");
			if (Teapot == NULL) {
				break;
			}
		}

		{//compile shader
			hr = D3DXCompileShaderFromFile("NXChap17_1_vs.hlsl", NULL, NULL, "Main", "vs_1_1", D3DXSHADER_DEBUG, &shader, &errorBuffer, &DiffuseConstTable);
			if (errorBuffer) {
				glb_GetLog().logToConsole("compile shader %s error with ", "vs_1_1", errorBuffer->GetBufferPointer());
				break;
			}

			hr = GetD3D9Device()->CreateVertexShader((DWORD*)shader->GetBufferPointer(), &DiffuseShader);
			if (FAILED(hr)) {
				glb_GetLog().logToConsole("create vertex shader failed.");
				break;
			}
		}

		{//set shader values
			ViewMatrixHandle = DiffuseConstTable->GetConstantByName(0, "ViewMatrix");
			ViewProjMatirxHandle = DiffuseConstTable->GetConstantByName(0, "ViewProjMatrix");
			AmbientMtrlHandle = DiffuseConstTable->GetConstantByName(0, "AmbientMtrl");
			DiffuseMtrlHandle = DiffuseConstTable->GetConstantByName(0, "DiffuseMtrl");
			LightDirHandle = DiffuseConstTable->GetConstantByName(0, "LightDirection");

			D3DXVECTOR4 directionToLight = { -0.57f, 0.f, 1.f, 1.f };
			DiffuseConstTable->SetVector(GetD3D9Device(), LightDirHandle, &directionToLight);

			D3DXVECTOR4 ambientMtrl(1.f, 1.0, 0.7, 0.2);
			D3DXVECTOR4 diffuseMtrl(0.f, 1.0, 0.7, 0.2);
			DiffuseConstTable->SetVector(GetD3D9Device(), AmbientMtrlHandle, &ambientMtrl);
			//DiffuseConstTable->SetVector(GetD3D9Device(), DiffuseMtrlHandle, &diffuseMtrl);

			DiffuseConstTable->SetDefaults(GetD3D9Device());

			D3DXMatrixPerspectiveFovLH(&Proj, D3DX_PI * 0.25f, MAINFRAME_WIDTH * 1.f / MAINFRAME_HEIGHT, 1.f, 1000.f);
		}
	}while(false);

	NX::NXSafeRelease(shader);
	NX::NXSafeRelease(errorBuffer);
}


void NX::NXChap17_1::OnTick(NXUInt32 uDelta) {
	static float angle = 3.f * D3DX_PI / 2.f;
	static float height = 3.f;

	if (::GetAsyncKeyState(VK_LEFT) & 0x8000f) {
		angle -= 0.5f * uDelta / 1000.f;
	}

	if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f) {
		angle += 0.5f * uDelta / 1000.f;
	}

	if (::GetAsyncKeyState(VK_UP) & 0x8000f) {
		height += 0.5f * uDelta / 1000.f;
	}

	if (::GetAsyncKeyState(VK_DOWN) & 0x8000f) {
		height -= 0.5f * uDelta / 1000.f;
	}

	D3DXVECTOR3 position(cosf(angle) * 7.f, height, sinf(angle) * 7.f);

	D3DXVECTOR3 target(0.f, 0.f, 0.f);

	D3DXVECTOR3 up(0.f, 1.f, 0.f);

	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);

	DiffuseConstTable->SetMatrix(GetD3D9Device(), ViewMatrixHandle, &V);

	D3DXMATRIX ViewProj =  V * Proj;
	DiffuseConstTable->SetMatrix(GetD3D9Device(), ViewProjMatirxHandle, &ViewProj);
}