#ifndef __ZX_OPENGL_BRICKS_H__
#define __ZX_OPENGL_BRICKS_H__

#include "../engine/render/NXApplication.h"
#include "../engine/render/NXProgram.h"
#include "../engine/render/NXCamera.h"
#include "../engine/math/NXVector.h"
#include "../engine/math/NXMatrix.h"

class Bricks: public NX::Application{
public:
    typedef struct vertex{
        NX::float3 vPosition;
    }vertex;
public:
    Bricks();
    virtual ~Bricks();
public:
    virtual bool Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight);
    virtual void Tick(const double DeltaTime);
    virtual void Render();
    virtual void OnKeyEvent(int key, int scancode, int action, int mods);
private:
    GLuint           vao;
    GLuint           ibo;
    GLuint           vbo;
    NX::Program      *m_pg;
    vertex           v[4];
    GLuint           MVPLocation;
    NX::PerspectCamera camera;
};





#endif