#ifndef __ZX_OPENGL_APPLICATION_CHAP1_5_H__
#define __ZX_OPENGL_APPLICATION_CHAP1_5_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../engine/render/NXApplication.h"
#include "../engine/common/NXLog.h"
#include "../engine/render/NXProgram.h"
#include "../engine/math/NXVector.h"
#include "../engine/math/NXMatrix.h"

class AppChap1_5: public NX::Application{
public:
    typedef struct vertex{
        NX::float3 Position;
        NX::float4 Color;
    }vertex;
public:
    AppChap1_5();
    virtual ~AppChap1_5();
public:
    virtual bool Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight);
    virtual void Tick(const double DeltaTime);
    virtual void Render();
    virtual void OnKeyEvent(int key, int scancode, int action, int mods);
private:
    vertex        v[8];
    GLuint        vao;
    GLuint        vbo;
    GLuint        ibo;
    GLuint        MVPLocation;
    NX::Program * m_pg;
    NX::float4X4 MVP;
};

#endif