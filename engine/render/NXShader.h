/*
 *  File:    Shader.h
 *  author:  张雄
 *  date:    2016_02_21
 *  purpose: 用于定义OpenGL shader操作的接口
 */


#ifndef __ZX_NXENGINE_SHADER_H__
#define __ZX_NXENGINE_SHADER_H__

#include "../common/NXCore.h"

namespace NX {
    class Shader{
    public:
        /*
         *  <函数功能>
         *  构造函数
         *
         *  <函数参数>
         *  szFilePath:    要使用的shader代码的路径，需要保证的是，仅使用szFilePath，在
         *                 程序中即可找到shader文件。
         
         *  uShaerType:    要使用的shader 代码的shader类型，此类型有GL_VERTEX_SHADER等
         *                 与OpenGL中使用的值完全相同。
         */
        Shader(const char* szFilePath, GLenum uShaderType);
        virtual ~Shader();
    public:
        
        /*
         *  <函数功能>
         *  编译shader,shader文件和类型由构造函数给出
         */
        virtual std::string Compile();
        std::string ReadShaderSource();
        const char* GetSaderTypeDescription() const;
        operator GLuint(){
            return m_uShaderId;
        }
        GLuint   GetId(){
            return m_uShaderId;
        }
    private:
        GLuint         m_uShaderId;
        GLenum         m_uShaderType;
        std::string    m_strShaderSourceFilePath;
    };
}


#endif