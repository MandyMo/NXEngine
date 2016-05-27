#ifndef __ZX_OPENGL_TEXTURE_3D_H__
#define __ZX_OPENGL_TEXTURE_3D_H__


#include "../engine/render/NXApplication.h"
#include "../engine/common/NXLog.h"
#include "../engine/render/NXProgram.h"
#include "../engine/math/NXVector.h"
#include "../engine/math/NXAlgorithm.h"
#include "../engine/math/NXMatrix.h"
#include "../engine/render/NXTexture.h"

class Texture3D: public NX::Application{
public:
    typedef struct vertex{
        NX::float4  Position;
    }vertex;
public:
    Texture3D();
    virtual ~Texture3D();
public:
    virtual bool Init(__in const char* vCmdLine[], __in const int iCmdCount, __in const int iWidth,       __in const int iHeight);
    virtual void Render();
private:
    GLuint          m_Texture;
    GLuint          m_TexLocation;
    GLuint          m_MVPLocation;
    GLuint          m_vao;
    GLuint          m_vbo;
    GLuint          m_ibo;
    vertex          v[3];
    NX::Program     *m_pg;
};



#endif