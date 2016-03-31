#include "Texture3D.h"

static  NX::ubyte4 Color[100][100][256];


Texture3D::Texture3D(){
    NX::glb_GetLog().logToConsole("Texture3D::Texture3D()");
}

Texture3D::~Texture3D(){
    NX::glb_GetLog().logToConsole("Texture3D::~Texture3D()");
}

bool Texture3D::Init(__in const char* vCmdLine[], __in const int iCmdCount,
                      __in const int iWidth,       __in const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    
    {//vertex
        memset(v, 0, sizeof(v));
        v[0] = {NX::float4(-400, -400, 10, 1)};
        v[1] = {NX::float4(-100, 360, 800, 1)};
        v[2] = {NX::float4(450, -100,  400, 1)};
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
        GLubyte idx[] = {0, 1, 2};
        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
    }
    
    {//vertex attribute
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, Position));
        glEnableVertexAttribArray(0);
    }
    
    {//shader
        m_pg = new NX::Program();
        m_pg->AddShader("./RedBook/Chap6/Texture3DVS.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./RedBook/Chap6/Texture3DFS.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
        m_TexLocation = glGetUniformLocation(m_pg->GetId(), "Tex");
        m_MVPLocation = glGetUniformLocation(m_pg->GetId(), "MVP");
    }
    
    {//texture
        for(int i = 0; i < 100; ++i){
            for(int j = 0; j < 100; ++j){
                for(int k = 0; k < 256; ++k){
                    Color[i][j][k] = NX::ubyte4(k, k, k, 255);
                }
            }
        }
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &m_Texture);
        glBindTexture(GL_TEXTURE_3D, m_Texture);
        glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, 100, 100, 256, 0, GL_BGRA, GL_UNSIGNED_BYTE, BUFFER_OFFSET(Color));
        glUniform1i(m_TexLocation, 0);
    }
    
    {//MVP
        NX::float4X4 MVP = NX::Perspective<float>(90, 1, 1, 1000) * NX::LookAt(NX::float3(0, 0, -500), NX::float3(0, 0, 1), NX::float3(0, 1, 0));
        glUniformMatrix4fv(m_MVPLocation, 1, GL_TRUE, &MVP[0][0]);
    }
    return true;
}

void Texture3D::Render(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_pg->UseProgram();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
}
