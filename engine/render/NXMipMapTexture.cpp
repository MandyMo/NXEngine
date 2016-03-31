#include "NXMipMapTexture.h"


NX::MipMapTexture::MipMapTexture(){
    m_strFilePathSet.clear();
    m_pTextureData = NULL;
}

NX::MipMapTexture::~MipMapTexture(){
    if(m_pTextureData != NULL){
        delete[] m_pTextureData;
    }
    m_strFilePathSet.clear();
}

GLuint NX::MipMapTexture::Load(__in const std::vector<std::string>& strFileSet){
    GLuint  TexId;
    m_strFilePathSet = strFileSet;
    glGenTextures(1, &TexId);
    glBindTexture(GL_TEXTURE_2D, TexId);
    NX::ImagePixelLoader *loader = new NX::ImagePixelLoader[strFileSet.size()];
    for(int i = 0, len = (int)strFileSet.size(); i < len; ++i){
        loader[i].Load(strFileSet[i]);
    }
    for(int i = 0, len = (int)strFileSet.size(); i < len; ++i){
        glTexImage2D(GL_TEXTURE_2D, i, GL_RGBA, loader[i].Width(), loader[i].Height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, loader[i].Pixels());
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    delete[] loader;
    return TexId;
}

NX::ImagePixelLoader* NX::MipMapTexture::GetImageDataByIndex(__in unsigned int index){
    assert(index < m_strFilePathSet.size() && m_pTextureData!= NULL);
    return m_pTextureData + index;
}
