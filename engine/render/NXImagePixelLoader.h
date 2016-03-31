/*
 *  File:    NXImagePixelLoader.h
 *  author:  张雄
 *  date:    2016_03_29
 *  purpose: get the pixels of a a common type image such as jpg, bmp, dds and so on
 */


#ifndef __ZX_NXENGINE_PICTURE_PIXEL_LOADER_H__
#define __ZX_NXENGINE_PICTURE_PIXEL_LOADER_H__

#include "../common/NXCore.h"

#include "FreeImage.h"

namespace NX{
    class ImagePixelLoader{
    public:
        ImagePixelLoader();
        virtual ~ImagePixelLoader();
    public:
        void   Load(__in const std::string& strFilePath);
        void*  Pixels();
        int    Height();
        int    Width();
    private:
        FREE_IMAGE_FORMAT       m_ImageFormat;
        FIBITMAP                *m_pImageData;
    };
};

#endif //!__ZX_NXENGINE_PICTURE_PIXEL_LOADER_H__