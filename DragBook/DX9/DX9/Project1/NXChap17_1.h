
/**
 *  File:      NXChap17_1.h
 *
 *  Author:    张雄(zhangxiong 1025679612@qq.com)
 *  Date:	   2017_03_06
 *  Purpose:   DX Demo1
 */

#include "..\..\NXDX9Window.h"

#pragma once

namespace NX {
	class NXChap17_1 : public NX::DX9Window {
	public:
		NXChap17_1();
		virtual ~NXChap17_1();

	public:
		virtual void PostRender();
		virtual void PreRender();
		virtual void Render();

	private:
		virtual void OnInitDX3Succeed();
		virtual void OnTick(NXUInt32 uDelta);

	private:
		IDirect3DVertexShader9				*DiffuseShader;
		ID3DXConstantTable					*DiffuseConstTable;
		ID3DXMesh							*Teapot;
		D3DXHANDLE							ViewMatrixHandle;
		D3DXHANDLE							ViewProjMatirxHandle;
		D3DXHANDLE							AmbientMtrlHandle;
		D3DXHANDLE							DiffuseMtrlHandle;
		D3DXHANDLE							LightDirHandle;
		D3DXMATRIX							Proj;
	};
}