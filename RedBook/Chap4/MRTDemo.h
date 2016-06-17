#ifndef __ZX_MRT_DEMO_H__
#define __ZX_MRT_DEMO_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../engine/render/NXApplication.h"
#include "../../engine/render/NXProgram.h"
#include "../../engine/math/NXVector.h"

class MRT: public NX::Application{
public:
    typedef struct vertex{
        NX::float3 Position;
        NX::float3 Color;
    }vertex;
public:
    MRT();
    virtual ~MRT();
public:
    virtual bool Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight);
    virtual void Tick(const double DeltaTime);
    virtual void Render();
    virtual void OnKeyEvent(int key, int scancode, int action, int mods);
private:
    NX::Program         *m_pg;
    GLuint              vao;
    GLuint              vbo;
    GLuint              ibo;
    vertex              v[4];
    GLuint              fbo;
    GLuint              cboa;
    GLuint              cbob;
    GLuint              sdbo;
};
#endif