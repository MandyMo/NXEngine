#ifndef __ZX_OPENGL_APPLICATION_CHAP1_1_H__
#define __ZX_OPENGL_APPLICATION_CHAP1_1_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../engine/render/NXApplication.h"
#include "../../engine/common/NXLog.h"
#include "../../engine/render/NXProgram.h"

class AppChap1_1: public NX::Application{
public:
    typedef struct vertex{
        GLfloat x;
        GLfloat y;
        GLfloat r;
        GLfloat g;
        GLfloat b;
        GLfloat a;
    }vertex;
public:
    AppChap1_1();
    virtual ~AppChap1_1();
public:
    virtual bool Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight);
    virtual void Tick(const double DeltaTime);
    virtual void Render();
    virtual void OnKeyEvent(int key, int scancode, int action, int mods);
private:
    GLuint   m_uVBO1;
    GLuint   m_uVBO2;
    GLuint   m_uVAO1;
    GLuint   m_uVAO2;
    GLuint   m_UsedVBO;
    GLuint   m_UsedVAO;
    NX::Program*   m_pg;
};

#endif