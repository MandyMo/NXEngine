#include <iostream>


#include "AppChap1_2.h"
#include "NXShader.h"

AppChap1_2::AppChap1_2(){
    m_uVAO1     = 0;
    m_uVAO2     = 0;
    m_uVBO1     = 0;
    m_uVBO2     = 0;
    m_UsedVBO   = 0;
    m_pg        = NULL;
}

AppChap1_2::~AppChap1_2(){
    delete m_pg;
}

bool AppChap1_2::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
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
            {-.8f, 0.8f     ,1.0f, 0.0f, 0.0f, 1.0f},
            {0.8f , 0.8f    ,0.0f, 1.0f, 0.0f, 1.0f,},
            {-0.8f, -0.8f   ,0.0f, 0.0f, 1.0f, 1.0f},
            {0.8f , -0.8f   ,1.0f, 1.0f, 1.0f, 1.0f}
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    m_UsedVAO = m_uVAO1;
    m_UsedVBO = m_uVBO1;
    
    {//program
        m_pg = new NX::Program();
        m_pg->AddShader("/Users/zulong/Desktop/zxgl/Chap1/VS1_2.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("/Users/zulong/Desktop/zxgl/Chap1/FS1_2.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
    }
    return true;
}
void AppChap1_2::Tick(const double DeltaTime){
    
}

void AppChap1_2::Render(){
    static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
    glClearBufferfv(GL_COLOR, 0, green);
    glBindVertexArray(m_UsedVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_UsedVBO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)8);
    glEnableVertexAttribArray(1);
    m_pg->UseProgram();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void AppChap1_2::OnKeyEvent(int key, int scancode, int action, int mods){
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
