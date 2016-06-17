#include "TextureMip.h"
#include "../../engine/render/NXMipMapTexture.h"
#include "../../engine/math/NXAlgorithm.h"
bool TextureMip::Init(__in const char* vCmdLine[], __in const int iCmdCount, __in const int iWidth, __in const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    
    {//shader
        m_pg  =  new NX::Program();
        m_pg->AddShader("./redBook/Chap6/TextureMipVS.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./redBook/Chap6/TextureMipFS.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
        m_MVPLocation  = glGetUniformLocation(m_pg->GetId(), "MVP");
        m_TexLocation  = glGetUniformLocation(m_pg->GetId(), "Tex");
    }
    
    {//vertex
        //memset(v, 0, sizeof(v));
        v[0] = {NX::float3(-500, 500, 100),  NX::float2(0, 20)};
        v[1] = {NX::float3(-500, -500, 100), NX::float2(0, 0)};
        v[2] = {NX::float3(500, 500, 100),   NX::float2(20, 20)};
        v[3] = {NX::float3(500, -500, 100),  NX::float2(20, 0)};
    }
//
    {//vao
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
    }
//
//    
    {//vbo
        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, Position));
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, UV));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }
    
    {//ibo
        GLubyte idx[] = {0, 1, 2, 1, 2, 3};
        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
    }
    
    {//mvp
        NX::float4X4 MVP = NX::GetPerspectiveMatrix(75.f, 1.f, 1.f, 1000.f) * NX::GetLookAtMatrix(NX::float3(0, -600, 0), NX::float3(0, 100, 1), NX::float3(0, 1, 0));
        glUniformMatrix4fv(m_MVPLocation, 1, GL_TRUE, &MVP[0][0]);
    }
    
    {//texture
        glActiveTexture(GL_TEXTURE1);
        std::vector<std::string> strFileSet;
        strFileSet.push_back("image/tex33X32.bmp");
        strFileSet.push_back("image/tex16X16.bmp");
        strFileSet.push_back("image/tex8X8.bmp");
        strFileSet.push_back("image/tex4X4.bmp");
        strFileSet.push_back("image/tex2X2.bmp");
        strFileSet.push_back("image/tex1X1.bmp");
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
        NX::MipMapTexture miploader;
        glBindTexture(GL_TEXTURE_2D, miploader.Load(strFileSet));
        glUniform1i(m_TexLocation, 1);
    }
    return true;
}

void TextureMip::Render(){
    glClearColor(0.3, 0.3, 0.3, 1);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glBindVertexArray(m_vao);
    m_pg->UseProgram();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
}

void TextureMip::Tick(const double DeltaTime){
    return NX::Application::Tick(DeltaTime);
}

GLuint TextureMip::CreateMipmap(__in const std::vector<std::string>& strFileSet){
    GLuint  TexId;
    glGenTextures(1, &TexId);
    glBindTexture(GL_TEXTURE_2D, TexId);
    NX::ImagePixelLoader *loader = new NX::ImagePixelLoader[strFileSet.size()];
    for(int i = 0; i < strFileSet.size(); ++i){
        loader[i].Load(strFileSet[i]);
    }
    for(int i = 0; i < strFileSet.size(); ++i){
        glTexImage2D(GL_TEXTURE_2D, i, GL_RGBA, loader[i].Width(), loader[i].Height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, loader[i].Pixels());
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    return TexId;
}
