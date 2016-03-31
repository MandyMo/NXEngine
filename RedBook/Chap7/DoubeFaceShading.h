#ifndef __ZX_OPENGL_DOUBLE_FACE_SHADING_H__
#define __ZX_OPENGL_DOUBLE_FACE_SHADING_H__

#include "../engine/render/NXApplication.h"
#include "../engine/render/NXProgram.h"
#include "../engine/math/NXVector.h"

class DoubleFaceShading: public NX::Application{
public:
    typedef struct vertex{
        NX::float3 Position;
        NX::float3 Color;
    }vertex;
public:
    DoubleFaceShading();
    virtual ~DoubleFaceShading();
public:
    virtual bool Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight);
    virtual void Tick(const double DeltaTime);
    virtual void Render();
    virtual void OnKeyEvent(int key, int scancode, int action, int mods);
private:
    GLuint   vao;
    GLuint   ibo;
    GLuint   vbo;
    NX::Program     *m_pg;
};

#endif //!__ZX_OPENGL_DOUBLE_FACE_SHADING_H__