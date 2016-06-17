#include "PointSize.h"

PointSize::PointSize(){
    
}

PointSize::~PointSize(){
    
}

bool PointSize::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    
    {//shader
        m_pg = new NX::Program();
        m_pg->AddShader("./RedBook/Chap3/PointSizeVS.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./RedBook/Chap3/PointSizeFS.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
    }
    
    {//vertex
        v[0] = {NX::float3(-0.8, -0.8, 0.0f), NX::float3(1.0f, 0.0f, 0.0f)};
        v[1] = {NX::float3(0.8, 0.8, 0.0f),   NX::float3(0.0f, 1.0f, 0.0f)};
        v[2] = {NX::float3(-0.8, 0.8, 0.0f),  NX::float3(0.0f, 0.0f, 1.0f)};
        v[3] = {NX::float3(0.8, -0.8, 0.0f),  NX::float3(0.0f, 0.0f, 0.0f)};
    }
    
    {//vao
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, Position));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, Color));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }
    
    {//ibo
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        GLbyte idx[] = {1, 2, 3, 0};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
    }
    
    {//clear
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glUseProgram(0);
    }
    return true;
}

void PointSize::Tick(const double DeltaTime){
    
}

void PointSize::Render(){
    glClearColor(0.0f, 0.25f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    //glPointSize(15.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vao);
    m_pg->UseProgram();
    //glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(500);
    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CCW);
    //glCullFace(GL_BACK);
    glDrawElements(GL_POINTS, 4, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
}

void PointSize::OnKeyEvent(int key, int scancode, int action, int mods){
    Application::OnKeyEvent(key, scancode, action, mods);
    if(action == GLFW_PRESS){
        return;
    }
}