#include "BrickShader.h"


BricksShader::BricksShader(){
}

BricksShader::~BricksShader(){
}

bool BricksShader::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    {//vertex data
        v[0] = {NX::float3(-1, 1, 0),  NX::float2(0, 10)};
        v[1] = {NX::float3(-1, -1, 0), NX::float2(0, 0)};
        v[2] = {NX::float3(1, 1, 0),   NX::float2(10, 10)};
        v[3] = {NX::float3(1, -1, 0),   NX::float2(10, 0)};
    }

    {//vbo
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
    }
    
    {//vao
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, Position));
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, UV));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }
    
    {//ibo
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        ubyte idx[] = {0, 1, 2, 1, 2, 3};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
    }
    
    {//shader
        m_pg = new NX::Program();
        m_pg->AddShader("./redBook/Chap8/BricksShaderVS.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./redBook/Chap8/BricksShaderFS.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
        DeltaLocation  = glGetUniformLocation(m_pg->GetId(), "Deleta");
        glUniform1f(DeltaLocation, 0.025 / 2);
    }
    return true;
}

void BricksShader::Tick(const double DeltaTime){
    Application::Tick(DeltaTime);
}

void BricksShader::Render(){
    glClearColor(0.3, 0.3, 0.3, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
}

void BricksShader::OnKeyEvent(int key, int scancode, int action, int mods){
    return Application::OnKeyEvent(key, scancode, action, mods);
}
