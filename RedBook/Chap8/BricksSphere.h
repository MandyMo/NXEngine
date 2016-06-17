#ifndef __ZX_OPENGL_BRICKS_SPHERE_H__
#define __ZX_OPENGL_BRICKS_SPHERE_H__

#include "../../engine/render/NXApplication.h"
#include "../../engine/render/NXProgram.h"
#include "../../engine/render/NXCamera.h"
#include "../../engine/math/NXVector.h"
#include "../../engine/math/NXMatrix.h"
#include "../../engine/math/NXMath.h"

class BricksSphere: public NX::Application{
public:
    typedef struct vertex{
        NX::float3 vPosition;
    }vertex;
public:
    BricksSphere();
    virtual ~BricksSphere();
public:
    virtual bool Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight);
    virtual void Tick(const double DeltaTime);
    virtual void Render();
    virtual void OnKeyEvent(int key, int scancode, int action, int mods);
    virtual void OnCursorPositionEvent(double xByScreen, double yByScreen);
    virtual void OnMouseButtonEvent(int btn,int action,int mods);
private:
    GLuint           vao;
    GLuint           ibo;
    GLuint           vbo;
    NX::Program      *m_pg;
    vertex           v[362];
    GLuint           MVPLocation;
    NX::PerspectCamera camera;
};





#endif