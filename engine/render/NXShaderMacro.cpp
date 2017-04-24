
/**
*  File:      NXShaderMacro.cpp
*
*  Author:    张雄(zhangxiong 1025679612@qq.com)
*  Date:	  2017_04_24
*  Purpose:   shader macros
*/

#include "NXShaderMacro.h"

NX::ShaderMacros::ShaderMacros() {
	m_Macro2Value.clear();
	m_Macros.clear();
}

NX::ShaderMacros& NX::ShaderMacros::SetMacro(const std::string &strKey, const std::string &strValue) {
	if (HaveMacro(strKey)) {
		RemoveMacro(strKey);
	}

	m_Macro2Value[strKey] = strValue;

	return *this;
}

NX::ShaderMacros& NX::ShaderMacros::RemoveMacro(const std::string &strKey) {
	if (!m_Macro2Value.count(strKey)) {
		return *this;
	}

	m_Macro2Value.erase(strKey);
	return *this;
}


bool NX::ShaderMacros::HaveMacro(const std::string& strKey) {
	return m_Macro2Value.count(strKey);
}

const D3DXMACRO* NX::ShaderMacros::operator() () const{
	static D3DXMACRO macroEnd = {nullptr, nullptr};

	m_Macros.clear();

	for (auto& it = m_Macro2Value.begin(); it != m_Macro2Value.end(); ++it) {
		D3DXMACRO macro = {it->first.c_str(), it->second.c_str()};
		m_Macros.push_back(macro);
	}
	m_Macros.push_back(macroEnd);
	return &m_Macros[0];
}

std::string NX::ShaderMacros::GetMacrosDescription() const {
	std::string desc;
	for (auto& it = m_Macro2Value.begin(); it != m_Macro2Value.end(); ++it) {
		desc = it->first + " = " + it->second + "\n";
	}

	return desc;
}