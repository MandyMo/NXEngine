#ifndef __ZX_OPENGL_POINT_SPRITE_H__
#define __ZX_OPENGL_POINT_SPRITE_H__


#include "../../engine/render/NXApplication.h"
#include "../../engine/common/NXLog.h"
#include "../../engine/render/NXProgram.h"
#include "../../engine/math/NXVector.h"
#include "../../engine/math/NXMatrix.h"
#include "../../engine/math/NXMath.h"
#include "../../engine/render/NXTexture.h"
#include "../../engine/render/NXImagePixelLoader.h"


class PointSprite: public NX::Application{
public:
    typedef struct vertex{
        NX::float3  Position;
        NX::float1  PointSize;
    }vertex;
public:
    PointSprite(){}
    virtual ~PointSprite(){}
public:
    virtual bool Init(__in const char* vCmdLine[], __in const int iCmdCount, __in const int iWidth,       __in const int iHeight);
    virtual void Render();
    virtual void Tick(const double DeltaTime);
private:
    GLuint          m_MVPLocation;
    GLuint          m_TexLocation;
    GLuint          m_vao;
    GLuint          m_vbo;
    GLuint          m_ibo;
    vertex          v[100];
    NX::Program     *m_pg;
};

#endif