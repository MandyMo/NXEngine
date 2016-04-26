#ifndef __ZX_OPENGL_GEOMETRY_DEMO_H__
#define __ZX_OPENGL_GEOMETRY_DEMO_H__

#include "../engine/render/NXApplication.h"
#include "../engine/render/NXProgram.h"
#include "../engine/render/NXCamera.h"
#include "../engine/math/NXVector.h"
#include "../engine/math/NXMatrix.h"
#include "../engine/math/NXMath.h"
class GSDemo: public NX::Application{
public:
    typedef struct vertex{
        NX::float3 vPosition;
    }vertex;
public:
    GSDemo();
    virtual ~GSDemo();
public:
    virtual bool Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight);
    virtual void Tick(const double DeltaTime);
    virtual void Render();
    virtual void OnKeyEvent(int key, int scancode, int action, int mods);
    virtual void OnCursorPositionEvent(double xByScreen, double yByScreen);
private:
    GLuint           vao;
    GLuint           ibo;
    GLuint           vbo;
    NX::Program      *m_pg;
    vertex           v[4];
    GLuint           MVPLocation;
    GLuint           OutLocation;
    GLuint           OutValue;
    NX::PerspectCamera camera;
    NX::Program      *m_Cull;
};





#endif  //!__ZX_OPENGL_GEOMETRY_DEMO_H__