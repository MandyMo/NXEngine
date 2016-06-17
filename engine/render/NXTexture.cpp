
#include "NXTexture.h"
#include "FreeImage.h"

NX::Texture::Texture(){
    m_uTextureId = 0;
}

NX::Texture::~Texture(){
    if(m_uTextureId){
        glDeleteTextures(1, &m_uTextureId);
    }
}

GLuint NX::Texture::Load(const std::string strTextureFilePath){
    unsigned    textureId   =   0;
    FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(strTextureFilePath.c_str(), 0);
    FIBITMAP          *dib  = FreeImage_Load(fifmt, strTextureFilePath.c_str(),0);
    dib                     =   FreeImage_ConvertTo32Bits(dib);
    BYTE *pixels            =   (BYTE*)FreeImage_GetBits(dib);
    m_iWidth                =   FreeImage_GetWidth(dib);
    m_iHeight               =   FreeImage_GetHeight(dib);
    glGenTextures( 1, &textureId );
    glBindTexture( GL_TEXTURE_2D, textureId );
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(
                 GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 m_iWidth,
                 m_iHeight,
                 0,
                 GL_BGRA,
                 GL_UNSIGNED_BYTE,
                 pixels
                 );
    FreeImage_Unload(dib);
    m_uTextureId = textureId;
    return  m_uTextureId;
}
