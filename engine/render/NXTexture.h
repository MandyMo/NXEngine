/*
 *  File:    NXTexture.h
 *  author:  张雄
 *  date:    2016_02_29
 *  purpose: 定义texture相关的图片资源
 */


#ifndef __ZX_NXENGINE_TEXTURE_H__
#define __ZX_NXENGINE_TEXTURE_H__

#include "../common/NXCore.h"

namespace NX {
    class Texture{
    public:
        Texture();
        virtual ~Texture();
    public:
        GLuint Load(const std::string strTextureFilePath);
        GLuint Width(){
            return m_iWidth;
        }
        
        GLuint Height(){
            return m_iHeight;
        }
    private:
        GLuint   m_uTextureId;
        GLuint   m_iHeight;
        GLuint   m_iWidth;
    };
}


#endif