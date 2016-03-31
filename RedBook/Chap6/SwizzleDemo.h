#ifndef __ZX_OPENGL_SWIZZLE_H__
#define __ZX_OPENGL_SWIZZLE_H__

#include "../engine/render/NXApplication.h"
#include "../engine/common/NXLog.h"
#include "../engine/render/NXProgram.h"
#include "../engine/math/NXVector.h"
#include "../engine/math/NXMatrix.h"
#include "../engine/render/NXTexture.h"


class SwizzleDemo: public NX::Application{
public:
    typedef struct vertex{
        NX::float2  Position;
        NX::float2  uv;
    }vertex;
public:
    SwizzleDemo();
    virtual ~SwizzleDemo();
public:
    virtual bool Init(__in const char* vCmdLine[], __in const int iCmdCount,
                      __in const int iWidth,       __in const int iHeight);
    virtual void Render();
private:
    GLuint          m_Texture;
    GLuint          m_vao;
    GLuint          m_vbo;
    GLuint          m_ibo;
    vertex          v[4];
    NX::Program     *m_pg;
};

#endif