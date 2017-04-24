/*
 *  File:    NXEffectManager.h
 *  author:  张雄(zhang xiong, 1025679612@qq.com)
 *  date:    2016_04_26
 *  purpose: a class used for manage shader resource
 */

#pragma once

#include <string>
#include <unordered_map>

#include "NXShaderMacro.h"

namespace NX {
	class EffectManager {
	public:
		EffectManager();
		static EffectManager& Instance();
		virtual ~EffectManager();

	public:
		class ID3DXEffect*  GetEffect(const std::string &strEffectFilePath);
		class ID3DXEffect*  GetEffect(const std::string &strEffectFilePath, const ShaderMacros &shaderMacros);
		void DeleteEffect(const std::string &strEffectFilePath, const ShaderMacros &shaderMacros);
		void DeleteEffect(const std::string &strEffectFilePath);
		void DeleteEffect(const ID3DXEffect *pEffect);

	private:
		std::unordered_map<std::string, ID3DXEffect*>     m_Effects;
	};
}