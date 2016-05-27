#ifndef __ZX_OPENGL_SKY_BOX_H__
#define __ZX_OPENGL_SKY_BOX_H__


#include "../engine/render/NXApplication.h"
#include "../engine/common/NXLog.h"
#include "../engine/render/NXProgram.h"
#include "../engine/math/NXVector.h"
#include "../engine/math/NXAlgorithm.h"
#include "../engine/math/NXMatrix.h"
#include "../engine/render/NXTexture.h"
#include "../engine/render/NXImagePixelLoader.h"

class SkyBox: public NX::Application{
public:
    typedef struct vertex{
        NX::float3  Position;
    }vertex;
public:
    SkyBox(){}
    virtual ~SkyBox(){}
public:
    virtual bool Init(__in const char* vCmdLine[], __in const int iCmdCount, __in const int iWidth,       __in const int iHeight);
    virtual void Render();
    virtual void Tick(const double DeltaTime);
private:
    GLuint CreateSkyBox(__in const std::vector<std::string>& strFilePathSet);
private:
    GLuint          m_CubeTexLocation;
    GLuint          m_MVPLocation;
    GLuint          m_vao;
    GLuint          m_vbo;
    GLuint          m_ibo;
    vertex          v[8];
    NX::Program     *m_pg;
};



#endif