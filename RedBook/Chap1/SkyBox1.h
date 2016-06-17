#ifndef __ZX_OPENGL_APPLICATION_CHAP1_8_H__
#define __ZX_OPENGL_APPLICATION_CHAP1_8_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../engine/render/NXApplication.h"
#include "../../engine/common/NXLog.h"
#include "../../engine/render/NXProgram.h"
#include "../../engine/math/NXVector.h"
#include "../../engine/math/NXMatrix.h"
#include "../../engine/render/NXTexture.h"
class SkyBox1: public NX::Application{
public:
    typedef struct Vertex{
        NX::float3      Position;
        NX::float2      UV;
    }Vertex;
public:
    SkyBox1();
    virtual ~SkyBox1();
public:
    virtual bool Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight);
    virtual void Tick(const double DeltaTime);
    virtual void Render();
    virtual void OnKeyEvent(int key, int scancode, int action, int mods);
private:
    Vertex          m_v[24];
    GLuint          m_vao;
    GLuint          m_SKyBoxTextureId;
    GLuint          m_PositionLocation;
    GLuint          m_UVWLocation;
    GLuint          m_MVP;
    GLuint          m_SkyBoxTextureSamplerLocation;
};

#endif