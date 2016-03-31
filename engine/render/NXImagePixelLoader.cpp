
#include "NXImagePixelLoader.h"

NX::ImagePixelLoader::ImagePixelLoader(){
    m_pImageData       =  NULL;
    m_ImageFormat      =  FIF_UNKNOWN;
}
NX::ImagePixelLoader::~ImagePixelLoader(){
    if(m_pImageData != NULL){
        FreeImage_Unload(m_pImageData);
    }
}

void   NX::ImagePixelLoader::Load(__in const std::string& strFilePath){
    m_ImageFormat = FreeImage_GetFileType(strFilePath.c_str(), 0);
    m_pImageData  = FreeImage_Load(m_ImageFormat, strFilePath.c_str(), 0);
    m_pImageData  = FreeImage_ConvertTo32Bits(m_pImageData);
    assert(m_pImageData != NULL);
}

void*  NX::ImagePixelLoader::Pixels(){
    assert(m_pImageData != NULL);
    return (void*)FreeImage_GetBits(m_pImageData);
}

int    NX::ImagePixelLoader::Height(){
    assert(m_pImageData != NULL);
    return FreeImage_GetHeight(m_pImageData);
}

int    NX::ImagePixelLoader::Width(){
    assert(m_pImageData != NULL);
    return FreeImage_GetWidth(m_pImageData);
}