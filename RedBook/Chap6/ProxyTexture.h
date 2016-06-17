#ifndef __ZX_OPENGL_PROXY_TEXTURE_H__
#define __ZX_OPENGL_PROXY_TEXTURE_H__

#include "../../engine/render/NXApplication.h"
#include "../../engine/common/NXLog.h"
#include "../../engine/render/NXProgram.h"
#include "../../engine/math/NXVector.h"
#include "../../engine/math/NXMatrix.h"
#include "../../engine/render/NXTexture.h"

class ProxyTexture: public NX::Application{
public:
    ProxyTexture();
    virtual ~ProxyTexture();
public:
    virtual bool Init(__in const char* vCmdLine[], __in const int iCmdCount,
                      __in const int iWidth, __in const int iHeight);
};

#endif