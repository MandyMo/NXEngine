/*
 *  File:    NXShaderManager.cpp
 *  author:  张雄
 *  date:    2016_04_26
 *  purpose: implement ShaderManager class
 */

#include "NXShaderManager.h"
#include "../common/NXLog.h"

NX::ShaderManager::ShaderManager(){
    glb_GetLog().log("Construct ShaderManager");
    m_pMutex     = NX::Mutex::Create();
}

NX::ShaderManager::~ShaderManager(){
    glb_GetLog().log("Destruct ShaderManager");
}

NX::ShaderManager& NX::ShaderManager::Instance(){
    static ShaderManager RefObject;
    return RefObject;
}

NX::Shader* NX::ShaderManager::FetchShader(__in const std::string& strShaderFilePath, __in const GLenum ShaderType){
    NX::MutexWraper Lock(m_pMutex);
    if(m_vShaderCollection.find(strShaderFilePath) != m_vShaderCollection.end() && m_vShaderCollection[strShaderFilePath] != NULL){
        return m_vShaderCollection.find(strShaderFilePath)->second;
    }
    NX::Shader * shader = new NX::Shader(strShaderFilePath.c_str(), ShaderType);
    shader->Compile();
    m_vShaderCollection[strShaderFilePath] = shader;
    return shader;
}

void NX::ShaderManager::FreeAllShaderResource(){
    NX::MutexWraper Lock(m_pMutex);
    glb_GetLog().log("FreeAllShaderResource");
    for(auto it = m_vShaderCollection.begin(), end = m_vShaderCollection.end(); it != end; ++it){
        if(!it->second){
            continue;
        }
        glb_GetLog().log("Free Shader [Type: %s] [File: %s]", it->second->GetSaderTypeDescription(), it->first.c_str());
        delete it->second;
        it->second = NULL;
    }
    m_vShaderCollection.clear();
}