

#include "SamplerDemo.h"

SamplerDemo::SamplerDemo(){
    NX::glb_GetLog().logToConsole(typeid(*this).name());
}

SamplerDemo::~SamplerDemo(){
    NX::glb_GetLog().logToConsole(typeid(*this).name());
}

bool SamplerDemo::Init(__in const char* vCmdLine[], __in const int iCmdCount,
                      __in const int iWidth,       __in const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    
    {//vertex
        memset(v, 0, sizeof(v));
        v[0] = {NX::float2(-1.0f, -1.0f), NX::float2(0, 0)};
        v[1] = {NX::float2(-1.0f,  1.0f), NX::float2(0, 4)};
        v[2] = {NX::float2(1.0f,  -1.0f), NX::float2(4, 0)};
        v[3] = {NX::float2(1.0f,   1.0f), NX::float2(4, 4)};
    }
    
    {//vao
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
    }
    
    {//vbo
        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
    }
    
    {//ibo
        GLubyte idx[] = {0, 1, 2, 3};
        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
    }
    
    {//vertex attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, Position));
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, uv));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }
    
    {//shader
        m_pg = new NX::Program();
        m_pg->AddShader("./RedBook/Chap6/ChessBoardVS.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./RedBook/Chap6/ChessBoardFS.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
    }
    
    {//texture
        GLuint pbo;
        glGenBuffers(1, &pbo);
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo);
        NX::byte4 color[] = {
            NX::byte4(0, 0, 0, 255), NX::byte4(255, 255, 255, 255),
            NX::byte4(255, 255, 255, 255), NX::byte4(0, 0, 0, 255),
        };
        glBufferData(GL_PIXEL_UNPACK_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
        glGenTextures(1, &m_Texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_Texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
        GLuint TexA = glGetUniformLocation(m_pg->GetId(), "TexA");
        glUniform1i(TexA, 0);
        
        GLuint SamplerId;
        glGenSamplers(1, &SamplerId);
        glSamplerParameteri(SamplerId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glSamplerParameteri(SamplerId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glSamplerParameteri(SamplerId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glSamplerParameteri(SamplerId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindSampler(0, SamplerId);
    }
    return true;
}

void SamplerDemo::Render(){
    glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    m_pg->UseProgram();
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
}
