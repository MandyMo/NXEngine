#ifndef __ZX_OPENGL_APPLICATION_CHAP1_7_H__
#define __ZX_OPENGL_APPLICATION_CHAP1_7_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../engine/render/NXApplication.h"
#include "../../engine/common/NXLog.h"
#include "../../engine/render/NXProgram.h"
#include "../../engine/math/NXVector.h"
#include "../../engine/math/NXMatrix.h"
#include "../../engine/render/NXTexture.h"
#include "../../engine/math/NXAlgorithm.h"
class AppChap1_7: public NX::Application{
public:
    typedef struct Vertex{
        NX::float3      Position;
        NX::float2      UV;
    }Vertex;
public:
    AppChap1_7();
    virtual ~AppChap1_7();
public:
    virtual bool Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight);
    virtual void Tick(const double DeltaTime);
    virtual void Render();
    virtual void OnKeyEvent(int key, int scancode, int action, int mods);
private:
    GLuint   vao;
    GLuint   vbo;
    GLuint   ibo;
    GLuint   MVPLocaiton;
    GLuint   textureALocation;
    GLuint   textureBLocation;
    NX::Program     *m_pg;
    NX::Texture     *m_pt;
    Vertex          v[4];
    double   Radius;
};

#endif