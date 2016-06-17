#ifndef __ZX_OPENGL_APPLICATION_CHAP1_3_H__
#define __ZX_OPENGL_APPLICATION_CHAP1_3_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../engine/render/NXApplication.h"
#include "../../engine/common/NXLog.h"
#include "../../engine/math/NXMath.h"
#include "../../engine/render/NXProgram.h"

class AppChap1_3: public NX::Application{
public:
    typedef struct vertex{
        GLfloat x;
        GLfloat y;
    }vertex;
public:
    AppChap1_3();
    virtual ~AppChap1_3();
public:
    virtual bool Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight);
    virtual void Tick(const double DeltaTime);
    virtual void Render();
    virtual void OnKeyEvent(int key, int scancode, int action, int mods);
private:
    vertex        v[362];
    GLuint        vao;
    GLuint        vbo;
    NX::Program *m_pg;
};

#endif