#ifndef __ZX_OPENGL_APPLICATION_CHAP1_4_H__
#define __ZX_OPENGL_APPLICATION_CHAP1_4_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../engine/render/NXApplication.h"
#include "../../engine/common/NXLog.h"
#include "../../engine/render/NXProgram.h"
#include "../../engine/math/NXVector.h"
#include "../../engine/math/NXMatrix.h"
#include "../../engine/math/NXAlgorithm.h"

class AppChap1_4: public NX::Application{
public:
    typedef struct vertex{
        NX::uint3   Position;
        NX::ubyte4  Color;
    }vertex;
public:
    AppChap1_4();
    virtual ~AppChap1_4();
public:
    virtual bool Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight);
    virtual void Tick(const double DeltaTime);
    virtual void Render();
    virtual void OnKeyEvent(int key, int scancode, int action, int mods);
private:
    vertex        v[7];
    GLuint        vao;
    GLuint        vbo;
    GLuint        ibo;
    GLuint        MVPLocation;
    GLuint        fbo;
    GLuint        dbo;
    GLuint        cbo;
    GLuint        c1bo;
    NX::Program * m_pg;
    NX::float4X4  MVP;
};

#endif