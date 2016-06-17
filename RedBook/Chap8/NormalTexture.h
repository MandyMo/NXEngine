#ifndef __ZX_OPENGL_NORMAL_TEXTURE_H__
#define __ZX_OPENGL_NORMAL_TEXTURE_H__

#include "../../engine/render/NXApplication.h"
#include "../../engine/render/NXProgram.h"
#include "../../engine/render/NXImagePixelLoader.h"
#include "../../engine/render/NXTexture.h"
#include "../../engine/render/NXCamera.h"
#include "../../engine/math/NXVector.h"
#include "../../engine/math/NXMatrix.h"


class NormalTexture: public NX::Application{
public:
    typedef struct vertex{
        NX::float3 vPosition;
        NX::float2 vUV;
    }vertex;
public:
    NormalTexture();
    virtual ~NormalTexture();
public:
    virtual bool Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight);
    virtual void Tick(const double DeltaTime);
    virtual void Render();
    virtual void OnKeyEvent(int key, int scancode, int action, int mods);
    virtual void OnCursorPositionEvent(double xByScreen, double yByScreen);
    virtual void OnMouseButtonEvent(int btn,int action,int mods);
private:
    GLuint              vao;
    GLuint              ibo;
    GLuint              vbo;
    NX::Program         *m_pg;
    vertex              v[4];
    GLuint              MVPLocation;
    GLuint              MVLocation;
    GLuint              LightLocation;
    GLuint              TextureLocation;//纹理
    GLuint              NormalLocation; //法线
    NX::PerspectCamera  camera;
};


#endif