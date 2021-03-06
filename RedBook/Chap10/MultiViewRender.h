#ifndef __ZX_OPENGL_MULTIPLE_VIEWPORT_RENDER__
#define __ZX_OPENGL_MULTIPLE_VIEWPORT_RENDER__


#include "../../engine/render/NXApplication.h"
#include "../../engine/render/NXProgram.h"
#include "../../engine/render/NXCamera.h"
#include "../../engine/math/NXVector.h"
#include "../../engine/math/NXMatrix.h"
#include "../../engine/math/NXMath.h"


class MultiViewRender: public NX::Application{
public:
    typedef struct Vertex{
        NX::float3 Position;
    }Vertex;
public:
    MultiViewRender();
    virtual ~MultiViewRender();
public:
    virtual bool Init(__in const char* vCmdLine[], __in const int iCmdCount,
                      __in const int iWidth, __in const int iHeight);
    virtual void Render();
    virtual void OnKeyEvent(int key, int scancode, int action, int mods);
    virtual void OnCursorPositionEvent(double xByScreen, double yByScreen);
    virtual void Tick(const double DeltaTime);
private:
    Vertex v[4];
    NX::PerspectCamera  m_Camera;
    GLuint              m_vao;
    GLuint              m_vbo;
    GLuint              m_ibo;
    NX::Program         *m_pg;
    GLuint              m_MVPLocation;
    GLuint              m_ColorLocation;
    GLuint              m_OuterLocation;
};


#endif  //!__ZX_OPENGL_MULTIPLE_VIEWPORT_RENDER__