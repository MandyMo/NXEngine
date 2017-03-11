
/**
 *  File:      NXChap2_1.h
 *
 *  Author:    张雄(zhangxiong 1025679612@qq.com)
 *  Date:	   2017_03_08
 *  Purpose:   DX9 X File test
 */

#pragma once

#include "..\..\NXDX9Window.h"
#include <vector>
#include <string>

namespace NX {
	class NXChap2_1 : public NX::DX9Window {
	public:
		NXChap2_1();
		virtual ~NXChap2_1();

	public:
		virtual void PostRender();
		virtual void PreRender();
		virtual void Render();

	private:
		virtual void OnInitDX3Succeed();
		virtual void OnTick(NXUInt32 uDelta);

	private:
		ID3DXEffect					*m_pEffect;
		D3DXHANDLE					BaseColorHandle;
		D3DXHANDLE					WorldMatrixHandle;
		D3DXHANDLE					ViewProjectHandle;
		D3DXHANDLE					LightPositionHandle;
		std::vector<std::string>	m_vTextures;
		ID3DXMesh					*m_pXMesh;
	};
}