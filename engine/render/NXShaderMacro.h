
/**
 *  File:      NXShaderMacro.h
 *
 *  Author:    张雄(zhangxiong 1025679612@qq.com)
 *  Date:	   2017_04_24
 *  Purpose:   shader macros
 */

#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include <d3dx9.h>
#include <d3d9.h>


namespace NX {
	class ShaderMacros {
	public:
		ShaderMacros();

	public:
		ShaderMacros& SetMacro(const std::string &strKey, const std::string &strValue);
		ShaderMacros& RemoveMacro(const std::string &strKey);
	
	public:
		bool HaveMacro(const std::string& strKey);
		const D3DXMACRO* operator() () const;
		std::string GetMacrosDescription() const;

	private:
		std::unordered_map<std::string, std::string> m_Macro2Value;
		mutable std::vector<D3DXMACRO>               m_Macros;
	};
}