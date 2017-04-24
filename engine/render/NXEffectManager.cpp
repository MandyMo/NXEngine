/*
*  File:    NXEffectManager.cpp
*  author:  张雄(zhang xiong, 1025679612@qq.com)
*  date:    2016_04_26
*  purpose: a class used for manage shader resource
*/

#include <d3d9.h>
#include <d3dx9.h>

#include "NXEffectManager.h"
#include "../common/NXLog.h"

namespace NX {
	extern IDirect3DDevice9* glb_GetD3DDevice();
}

NX::EffectManager::EffectManager() {
	m_Effects.clear();
}
NX::EffectManager& NX::EffectManager::Instance() {
	static EffectManager SharedObject;
	return SharedObject;
}

NX::EffectManager::~EffectManager() {
	for (auto it : m_Effects) {
		NX::NXSafeRelease(it.second);;
	}
	m_Effects.clear();
}


ID3DXEffect*  NX::EffectManager::GetEffect(const std::string &strEffectFilePath, const ShaderMacros &shaderMacros) {
	std::string strShaderKey = strEffectFilePath + shaderMacros.GetMacrosDescription();
	if (m_Effects.count(strShaderKey)) {
		return m_Effects[strShaderKey];
	}
	
	ID3DXBuffer *pError = nullptr;
	ID3DXEffect *pEffect = nullptr;
	HRESULT hr = D3DXCreateEffectFromFile(glb_GetD3DDevice(), strEffectFilePath.c_str(), (D3DXMACRO*)shaderMacros(), NULL, D3DXSHADER_DEBUG, NULL, &pEffect, &pError);
	if (pError) {
		glb_GetLog().logToConsole("Compile effect [file: %s] with [error:%s]", strEffectFilePath.c_str(), pError->GetBufferPointer());
	} else if (FAILED(hr)) {
		glb_GetLog().logToConsole("Compile effect [file: %s] failed", strEffectFilePath.c_str());
		NX::NXSafeRelease(pEffect);
	} else {
		glb_GetLog().logToConsole("Compile effect [file: %s] succeed", strEffectFilePath.c_str());
		m_Effects[strShaderKey] = pEffect;
		return pEffect;
	}

	NX::NXSafeRelease(pError);
	return nullptr;
}

ID3DXEffect* NX::EffectManager::GetEffect(const std::string &strEffectFilePath) {
	ShaderMacros shaderMacros;
	return GetEffect(strEffectFilePath, shaderMacros);
}

void NX::EffectManager::DeleteEffect(const std::string &strEffectFilePath) {
	ShaderMacros shaderMacros;
	DeleteEffect(strEffectFilePath, shaderMacros);
}

void NX::EffectManager::DeleteEffect(const std::string &strEffectFilePath, const ShaderMacros &shaderMacros) {
	std::string strKey = strEffectFilePath + shaderMacros.GetMacrosDescription();
	m_Effects.erase(strKey);
}

void NX::EffectManager::DeleteEffect(const ID3DXEffect *pEffect) {
	std::string strEffectFilePath;
	for (auto it : m_Effects) {
		if (it.second == pEffect) {
			strEffectFilePath = it.first;
			break;
		}
	}
	DeleteEffect(strEffectFilePath);
}