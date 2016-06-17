#include "MultiTexture.h"


MultiTexture::MultiTexture(){
    NX::glb_GetLog().logToConsole(typeid(*this).name());
}

MultiTexture::~MultiTexture(){
    NX::glb_GetLog().logToConsole(typeid(*this).name());
}

bool MultiTexture::Init(__in const char* vCmdLine[], __in const int iCmdCount,
                        __in const int iWidth,       __in const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    const char *  extensions = (const char*)glGetString(GL_RENDERER);
    std::cout << extensions << std::endl;
    {//shader
        m_pg = new NX::Program();
        m_pg->AddShader("./redbook/Chap6/MultiTextureVS.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./redbook/Chap6/MultiTextureFS.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
    }
    
    {//vertex data
        v[0] = {NX::float2(-1.0, -1.0),     NX::float2(0, 0)};
        v[1] = {NX::float2(-1.0,  1.0),     NX::float2(0, 1)};
        v[2] = {NX::float2(1.0,  -1.0),     NX::float2(1, 0)};
        v[3] = {NX::float2(1.f,   1.0),     NX::float2(1, 1)};
    }
    
    {//vbo
        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
    }
    
    {//vao
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, Position));
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, uv));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }
    {
        textureALocation = glGetUniformLocation(m_pg->GetId(), "TexA");
        textureBLocation = glGetUniformLocation(m_pg->GetId(), "TexB");
    }
    {//texture
        m_pg->UseProgram();
        m_pt = new NX::Texture();
        GLuint tex = 0;
        glActiveTexture(GL_TEXTURE0);
        tex = m_pt->Load("image/tga/background_ddn.tga");
        glBindTexture(GL_TEXTURE_2D, tex);
        glUniform1i(textureALocation, 0);
        
        glActiveTexture(GL_TEXTURE1);
        tex = m_pt->Load("./image/fog.bmp");
        glBindTexture(GL_TEXTURE_2D, tex);
        glUniform1i(textureBLocation, 1);
        
        m_iDif = glGetUniformLocation(m_pg->GetId(), "Dif");
    }
    
    return true;
}

void MultiTexture::Render(){
    glClearColor(0, 0, 0, 1);
    glClearDepth(2.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    m_pg->UseProgram();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void MultiTexture::Tick(const double DeltaTime){
    static float Sum = 0;
    Sum += DeltaTime;
    glUniform1f(m_iDif, Sum);
}
