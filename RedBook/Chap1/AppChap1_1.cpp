#include <iostream>


#include "AppChap1_1.h"
#include "NXShader.h"

AppChap1_1::AppChap1_1(){
    m_uVAO1     = 0;
    m_uVAO2     = 0;
    m_uVBO1     = 0;
    m_uVBO2     = 0;
    m_UsedVBO   = 0;
}

AppChap1_1::~AppChap1_1(){
    
}

bool AppChap1_1::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }

    {//vao1
        glGenVertexArrays(1, &m_uVAO1);
        glBindVertexArray(m_uVAO1);
    }
    {//vbo1
        glGenBuffers(1, &m_uVBO1);
        glBindBuffer(GL_ARRAY_BUFFER, m_uVBO1);
        vertex v[4] = {
            {-1.0f, 1.0f,   1.0f, 0.0f, 0.0f, 1.0f},
            {1.0f,  1.0f,   0.0f, 1.0f, 0.0f, 1.0f},
            {-1.0f, -1.0f,  0.0f, 0.0f, 1.0f, 1.0f},
            {1.0f,  -1.0f,  1.0f, 1.0f, 1.0f, 1.0f}
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    {//vao2
        glGenVertexArrays(1, &m_uVAO2);
        glBindVertexArray(m_uVAO2);
    }
    {//vbo2
        glGenBuffers(1, &m_uVBO2);
        glBindBuffer(GL_ARRAY_BUFFER, m_uVBO2);
        vertex v[4] = {
            {-0.8f, 0.8f,   0.0f, 1.0f, 1.0f, 1.0f},
            {0.8f,  0.8f,   1.0f, 0.0f, 1.0f, 1.0f},
            {-0.8f, -0.8f,  1.0f, 1.0f, 0.0f, 1.0f},
            {0.8f,  -0.8f,  0.0f, 0.0f, 0.0f, 1.0f}
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    m_UsedVAO = m_uVAO1;
    m_UsedVBO = m_uVBO1;
    
    {//program
        m_pg = new NX::Program();
        m_pg->AddShader("./redbook/Chap1/VS1_1.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./redbook/Chap1/FS1_1.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
    }
    return true;
}
void AppChap1_1::Tick(const double DeltaTime){
    
}

void AppChap1_1::Render(){
    m_pg->UseProgram();
    glClearColor(0.0f, 0.25f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(m_UsedVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_UsedVBO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)8);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    //glViewport(100, 100, 400, 100);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void AppChap1_1::OnKeyEvent(int key, int scancode, int action, int mods){
    Application::OnKeyEvent(key, scancode, action, mods);
    
    if(action == GLFW_PRESS){
        return;
    }
    std::cout << "change buffer..." << std::endl;
    if(m_UsedVBO == m_uVBO1){
        m_UsedVBO = m_uVBO2;
    }else{
        m_UsedVBO = m_uVBO1;
    }
    
    if(m_UsedVAO == m_uVAO1){
        m_UsedVAO = m_uVAO2;
    }else{
        m_UsedVAO = m_uVAO1;
    }
}
