#ifndef __ZX_OPENGL_APPLICATION_CHAP1_6_H__
#define __ZX_OPENGL_APPLICATION_CHAP1_6_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../engine/render/NXApplication.h"
#include "../engine/common/NXLog.h"
#include "../engine/render/NXProgram.h"
#include "../engine/math/NXVector.h"
#include "../engine/math/NXMatrix.h"
#include "../engine/render/NXTexture.h"
class AppChap1_6: public NX::Application{
public:
    typedef struct vertex{
        NX::float3 Position;
        NX::float4 Color;
        NX::float2 UV;
    }vertex;
    
    typedef struct Mirror{
        NX::float3 Position;
        NX::float2 UV;
    }Mirror;
public:
    AppChap1_6();
    virtual ~AppChap1_6();
public:
    virtual bool Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight);
    virtual void Tick(const double DeltaTime);
    virtual void Render();
    virtual void OnKeyEvent(int key, int scancode, int action, int mods);
private:
    Mirror        vm[4];
    vertex        v[4];
    GLuint        vao;
    GLuint        vbo;
    GLuint        ibo;
    GLuint        MVPLocation;
    GLuint        TexLocation;
    NX::Program * m_pg;
    NX::Texture * m_tex;
    NX::float4X4 MVP;
    GLuint       textureId;
    GLuint       vaom;
    GLuint       vbom;
    GLuint       ibom;
    GLuint       textureMirror;
};

#endif