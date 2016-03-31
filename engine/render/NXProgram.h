/*
 *  File:    Program.h
 *  author:  张雄
 *  date:    2016_02_21
 *  purpose: 用于定义OpenGL program的接口
 */

#ifndef __ZX_NXENGINE_PROGRAM_H__
#define __ZX_NXENGINE_PROGRAM_H__

#include "NXShader.h"

namespace  NX {
    class Program{
    public:
        Program();
        virtual ~Program();
    public:
        /*
         *  <函数功能>
         *  给当前program添加shader,注意，创建program需要在application init成功之后
         *  
         *  <函数参数>
         *  shader:   要添加的shader指针，shader必须是正确的，可用的以及已经编译好的
         */
        void AddShader(__in Shader * shader);
        
        /*
         *  <函数功能>
         *  给当前Program添加shader
         * 
         *  <函数参数>
         *  strShaderFilePath: 要添加的shader文件路径(要保证通过此路径可找到shader)
         *  ShaderType:        要添加的shader类型
         */
        void AddShader(__in const std::string& strShaderFilePath, __in GLenum ShaderType);
        
        /*
         *  <函数功能>
         *  链接程序，调用glLinkProgram实现
         */
        std::string LinkProgram();
        
        /*
         *  <函数功能>
         *  使用当前程序，调用glUseProgram实现。
         */
        void UseProgram();
        
        /*
         *  <函数功能>
         *  返回程序id
         *
         *  <返回值>
         *  程序id，如果当前程序不可用，则返回0
         */
        GLuint GetId(){
            return m_uProgramId;
        }
    private:
        std::vector<Shader*> m_vShaderSet;
        GLuint               m_uProgramId;
    };
}

#endif