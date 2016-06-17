#ifndef __ZX_OPENGL_TRANSFORM_FEED_BACK_H__
#define __ZX_OPENGL_TRANSFORM_FEED_BACK_H__


#include "../../engine/render/NXApplication.h"
#include "../../engine/render/NXProgram.h"
#include "../../engine/render/NXCamera.h"
#include "../../engine/math/NXVector.h"
#include "../../engine/math/NXMatrix.h"
#include "../../engine/math/NXMath.h"


class TFBDemo: public NX::Application{
public:
    typedef struct Vertex{
        NX::float3 Position;
    }Vertex;
public:
    TFBDemo();
    virtual ~TFBDemo();
public:
    virtual bool Init(__in const char* vCmdLine[], __in const int iCmdCount,
                      __in const int iWidth, __in const int iHeight);
    virtual void Render();
    virtual void OnKeyEvent(int key, int scancode, int action, int mods);
    virtual void OnCursorPositionEvent(double xByScreen, double yByScreen);
private:
    Vertex v[4];
    NX::PerspectCamera      m_Camera;
    GLuint              m_vao;
    GLuint              m_vbo;
    GLuint              m_ibo;
    NX::Program         *m_pg;
    NX::Program         *m_pfb;
    GLuint              m_MVPLocation;
    
    GLuint              m_TFBO;
    GLuint              m_TFB;
};


#endif  //!__ZX_OPENGL_TRANSFORM_FEED_BACK_H__