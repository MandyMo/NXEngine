
#include "AppChap1_3.h"
#include "NXShader.h"

AppChap1_3::AppChap1_3(){
    vao   = 0;
    vbo   = 0;
    m_pg  = NULL;
}

AppChap1_3::~AppChap1_3(){
    if(vao){
        glDeleteBuffers(1, &vao);
        glDeleteBuffers(1, &vbo);
        delete m_pg;
    }
}

bool AppChap1_3::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    {//create vertex
        memset(v, 0, sizeof(v));
        for(int i = 1; i <= 360; ++i){
            v[i].x = 0.8 * std::cos(DG2RD(i));
            v[i].y = 0.8 * std::sin(DG2RD(i));
        }
        v[361] = v[1];
    }
    {//vao
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }
    
    {//vbo
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
    }
    
    {//program & shader
        m_pg = new NX::Program();
        m_pg->AddShader("./Chap1/VS1_3.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./Chap1/FS1_3.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
    }
    
    {//reset
        glDisableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    return true;
}
void AppChap1_3::Tick(const double DeltaTime){
    
}

void AppChap1_3::Render(){
    m_pg->UseProgram();
    glClearColor(0.0f, 0.25f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    glEnableVertexAttribArray(0);
    m_pg->UseProgram();
    glDrawArrays(GL_TRIANGLE_FAN, 0, 362);
}

void AppChap1_3::OnKeyEvent(int key, int scancode, int action, int mods){
    Application::OnKeyEvent(key, scancode, action, mods);
    
    if(action == GLFW_PRESS){
        return;
    }else{
        std::cout << "key press" << std::endl;
    }
}
