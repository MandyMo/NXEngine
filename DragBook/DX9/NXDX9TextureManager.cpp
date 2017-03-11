
/**
*  File:      NXDX9Window.h
*
*  Author:    张雄(zhangxiong 1025679612@qq.com)
*  Date:	   2017_03_09
*  Purpose:   管理DX9 纹理
*/

#pragma once

#include "NXDX9TextureManager.h"
#include "NXDX9Window.h"
#include "../../engine/common/NXLog.h"

NX::NXDX9TextureManager& NX::NXDX9TextureManager::Instance() {
	static NXDX9TextureManager SharedObject;
	return SharedObject;
}

NX::NXDX9TextureManager::NXDX9TextureManager() {
	m_vTextures.clear();
}

NX::NXDX9TextureManager::~NXDX9TextureManager() {
	for (auto it = m_vTextures.begin(); it != m_vTextures.end(); ++it) {
		it->second->Release();
	}
	m_vTextures.clear();
}

IDirect3DTexture9*	NX::NXDX9TextureManager::GetTexture(const std::string &strFilePath) {
	IDirect3DTexture9 *pD3DTexture = NULL;
	if (m_vTextures.count(strFilePath)) {
		return m_vTextures[strFilePath];
	}
	::D3DXCreateTextureFromFile(glb_GetD3DWindow()->GetD3D9Device(), strFilePath.c_str(), &pD3DTexture);
	if (pD3DTexture == NULL) {
		glb_GetLog().logToConsole("Load texture %s failed", strFilePath.c_str());
		return pD3DTexture;
	}
	m_vTextures[strFilePath] = pD3DTexture;
	return pD3DTexture;
}

void	NX::NXDX9TextureManager::DeleteTexture(const std::string &strFilePath) {
	if (m_vTextures.count(strFilePath) && m_vTextures[strFilePath] != NULL) {
		m_vTextures[strFilePath]->Release();
	}
	m_vTextures.erase(strFilePath);
}

std::string			NX::NXDX9TextureManager::GetTextureName(IDirect3DTexture9* pD3DTexture) {
	for (auto it = m_vTextures.begin(); it != m_vTextures.end(); ++it) {
		if (it->second == pD3DTexture) {
			return it->first;
		}
	}
	return "";
}

void			NX::NXDX9TextureManager::DeleteTexture(IDirect3DTexture9 *pD3DTexture) {
	for (auto it = m_vTextures.begin(); it != m_vTextures.end(); ++it) {
		if (it->second == pD3DTexture) {
			m_vTextures.erase(it);
		}
	}
}
