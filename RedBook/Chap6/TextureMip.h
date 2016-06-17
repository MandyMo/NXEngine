#ifndef __ZX_OPENGL_TEXTURE_MIP_H__
#define __ZX_OPENGL_TEXTURE_MIP_H__

#include "../../engine/render/NXApplication.h"
#include "../../engine/common/NXLog.h"
#include "../../engine/render/NXProgram.h"
#include "../../engine/math/NXVector.h"
#include "../../engine/math/NXMatrix.h"
#include "../../engine/render/NXTexture.h"
#include "../../engine/render/NXImagePixelLoader.h"


class TextureMip: public NX::Application{
public:
    typedef struct vertex{
        NX::float3  Position;
        NX::float2  UV;
    }vertex;
public:
    TextureMip(){}
    virtual ~TextureMip(){}
public:
    virtual bool Init(__in const char* vCmdLine[], __in const int iCmdCount, __in const int iWidth,       __in const int iHeight);
    virtual void Render();
    virtual void Tick(const double DeltaTime);
private:
    GLuint CreateMipmap(__in const std::vector<std::string>& strFileSet);
private:
    GLuint          m_MVPLocation;
    GLuint          m_TexLocation;
    GLuint          m_vao;
    GLuint          m_vbo;
    GLuint          m_ibo;
    vertex          v[4];
    NX::Program     *m_pg;
};

#endif