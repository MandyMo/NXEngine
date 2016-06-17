/*
 *  File:    NXMipMapTexture.h
 *  author:  张雄
 *  date:    2016_03_29
 *  purpose: load mipmap texture
 */


#ifndef __ZX_NXENGINE_MIPMAP_TEXTURE_H__
#define __ZX_NXENGINE_MIPMAP_TEXTURE_H__



#include "NXImagePixelLoader.h"

namespace NX{
    class MipMapTexture{
    public:
        MipMapTexture();
        virtual ~MipMapTexture();
    public:
        GLuint Load(__in const std::vector<std::string>& strFileSet);
        ImagePixelLoader* GetImageDataByIndex(__in unsigned int index);
    private:
        ImagePixelLoader           *m_pTextureData;
        std::vector<std::string>    m_strFilePathSet;
    };
}


#endif  //!__ZX_NXENGINE_MIPMAP_TEXTURE_H__