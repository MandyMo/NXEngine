
/**
 *  File:      NXDX9Window.h
 *
 *  Author:    张雄(zhangxiong 1025679612@qq.com)
 *  Date:	   2017_03_09
 *  Purpose:   管理DX9 纹理
 */

#pragma once

#include <D3DX9.h>
#include <unordered_map>
#include <string>

namespace NX {
	class DX9TextureManager {
	public:
		static DX9TextureManager& Instance();
		DX9TextureManager();
		virtual ~DX9TextureManager();

	public:
		IDirect3DTexture9*	GetTexture(const std::string &strFilePath);
		std::string			GetTextureName(IDirect3DTexture9* pD3DTexture);
		void				DeleteTexture(IDirect3DTexture9 *pD3DTexture);
		void				DeleteTexture(const std::string &strFilePath);

	private:
		std::unordered_map<std::string, IDirect3DTexture9*>			m_vTextures;
	};
}