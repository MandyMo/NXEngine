#ifndef __ZX_BUFFER_OBJECT_H__
#define __ZX_BUFFER_OBJECT_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../engine/render/NXApplication.h"
#include "../engine/render/NXProgram.h"
#include "../engine/math/NXVector.h"

class BufferObject: public NX::Application{
public:
    typedef struct vertex{
        NX::float3 Position;
        NX::float3 Color;
    }vertex;
public:
    BufferObject();
    virtual ~BufferObject();
public:
    virtual bool Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight);
    virtual void Tick(const double DeltaTime);
    virtual void Render();
    virtual void OnKeyEvent(int key, int scancode, int action, int mods);
private:
    GLuint   vao;
    GLuint   ibo;
    GLuint   vbo;
    GLuint   bbo;
    NX::Program     *m_pg;
};

#endif