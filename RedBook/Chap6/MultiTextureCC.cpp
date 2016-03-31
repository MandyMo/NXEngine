#include "MultiTextureCC.h"

MultiTextureCC::MultiTextureCC(){
    Radius = 0;
}

MultiTextureCC::~MultiTextureCC(){
}

bool MultiTextureCC::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    {//vao
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }
    
    {//program
        m_pg = new NX::Program();
        m_pg->AddShader("./redbook/Chap6/MultiTextureCCVS.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./redbook/Chap6/MultiTextureCCFS.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
    }
    {//vertex
        memset(v, 0, sizeof(v));
        v[0] = {NX::float3(0, 600, 400),  NX::float2(0, 1)};
        v[1] = {NX::float3(0, 0, 400),    NX::float2(0, 0)};
        v[2] = {NX::float3(600, 600, 400),NX::float2(1, 1)};
        v[3] = {NX::float3(600, 0, 400),  NX::float2(1, 0)};
    }
    
    {//vbo
        m_pg->UseProgram();
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
        GLuint location;
        location = glGetAttribLocation(m_pg->GetId(), "Position");
        glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), CLS_MEM_OFFSET(Vertex, Position));
        glEnableVertexAttribArray(location);
        location = glGetAttribLocation(m_pg->GetId(), "UV");
        glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), CLS_MEM_OFFSET(Vertex, UV));
        glEnableVertexAttribArray(location);
    }
    
    {//ibo
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        GLuint idx[] = {0, 1, 2, 3};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
    }
    
    {
        MVPLocaiton      = glGetUniformLocation(m_pg->GetId(), "MVP");
        textureALocation = glGetUniformLocation(m_pg->GetId(), "TexA");
        textureBLocation = glGetUniformLocation(m_pg->GetId(), "TexB");
    }
    
    {//texture
        m_pt = new NX::Texture();
        GLuint tex = 0;
        glActiveTexture(GL_TEXTURE0);
        tex = m_pt->Load("image/desktop.jpg");
        //glBindTexture(GL_TEXTURE_2D, tex);
        glUniform1i(textureALocation, 0);
        
        glActiveTexture(GL_TEXTURE1);
        tex = m_pt->Load("image/fog.bmp");
        //glBindTexture(GL_TEXTURE_2D, tex);
        glUniform1i(textureBLocation, 1);
    }
    return true;
}

void MultiTextureCC::Tick(const double DeltaTime){
    Application::Tick(DeltaTime);
    Radius += DeltaTime / 5;
}

void MultiTextureCC::Render(){
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vao);
    
    
    {
        auto P = NX::Perspective<float>(90, 1, 1, 1000);
        auto V = NX::LookAt(NX::float3(300, 300, 0), NX::float3(300, 300, 1), NX::float3(0, 1, 0));
        auto R = NX::RotateZ(Radius);
        auto MVP = P * R * V;
        glUniformMatrix4fv(MVPLocaiton, 1, GL_TRUE, &MVP[0][0]);
    }
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
}

void MultiTextureCC::OnKeyEvent(int key, int scancode, int action, int mods){
    Application::OnKeyEvent(key, scancode, action, mods);
    
    if(action == GLFW_PRESS){
        return;
    }else{
        std::cout << "key press" << std::endl;
    }
}
