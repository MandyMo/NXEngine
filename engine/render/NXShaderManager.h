/*
 *  File:    NXShaderManager.h
 *  author:  张雄
 *  date:    2016_04_26
 *  purpose: a class used for manage shader resource
 */

#ifndef __ZX_SHADER_MANAGER_H__
#define __ZX_SHADER_MANAGER_H__

#include <map>
#include "NXShader.h"
#include "../System/NXMutex.h"
namespace NX{
    class ShaderManager{
    public:
        /**
         *  any code should not define a ShaderManager explicit, but use Instance to get a global unique ShaderManager
         */
        virtual ~ShaderManager();
        static ShaderManager& Instance();
    private:
        /**
         *  never try to construct a ShaderManager object in stack or heap memory.
         */
        ShaderManager();
    public:
        /**
         *  if shader exist,then just return, else create and compile it then return
         */
        Shader* FetchShader(__in const std::string& strShaderFilePath, __in const GLenum ShaderType);
        void    FreeAllShaderResource();
    private:
        std::map<std::string, Shader*>  m_vShaderCollection;
        Mutex                           *m_pMutex;
    };
}



#endif  //!__ZX_SHADER_MANAGER_H__