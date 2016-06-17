
#include "AppChap1_5.h"
#include "NXShader.h"

AppChap1_5::AppChap1_5(){
    vao   = 0;
    vbo   = 0;
    m_pg  = NULL;
}

AppChap1_5::~AppChap1_5(){
    if(vao){
        glDeleteBuffers(1, &vao);
        glDeleteBuffers(1, &vbo);
        delete m_pg;
    }
}

bool AppChap1_5::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    {//create vertex
        memset(v, 0, sizeof(v));
        v[0] = {NX::float3(-200, 200, 200),  NX::float4(1, 0, 0, 1)};
        v[1] = {NX::float3(-200, 200, -200), NX::float4(1, 0, 1, 1)};
        v[2] = {NX::float3(200, 200, -200),  NX::float4(0, 0, 1, 1)};
        v[3] = {NX::float3(200, 200, 200),   NX::float4(1, 0.5, 0.05, 1)};
        v[4] = {NX::float3(-200, -200, 200), NX::float4(1, 1, 0, 1)};
        v[5] = {NX::float3(-200, -200, -200),NX::float4(1, 1, 1, 1)};
        v[6] = {NX::float3(200, -200, -200), NX::float4(0, 1, 1, 1)};
        v[7] = {NX::float3(200, -200, 200),  NX::float4(0, 1, 0, 1)};
    }
    {//vao
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }
    
    {//vbo
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)12);
    }
    
    {//ibo
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        const int idx[] = {0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 0, 1, 5, 0, 5, 4, 3, 2, 6, 3, 6, 7, 0, 3, 4, 3, 4, 7, 1, 2, 6, 1, 5, 6};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
    }
    
    {//program & shader
        m_pg = new NX::Program();
        m_pg->AddShader("./Chap1/VS1_5.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./Chap1/FS1_5.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
    }
    {
        auto P = NX::GetPerspectiveMatrix<float>(90, 1, 1, 10000);
        auto V = NX::GetLookAtMatrix(NX::float3(300, 300, 300), NX::float3(0, 0, 0), NX::float3(0,1,0));
        auto M = NX::GetTranslated<float>(0, 0, 0);
        MVP = P * V * M;
        //MVP = P * V;
        //MVP = NX::Perspective<float>(90, 1, 1, 1000) * NX::LookAt(NX::float3(0, 0, -300), NX::float3(0, 0, 0), NX::float3(0,1,0));
    }
    {//translate matrix location
        MVPLocation = glGetUniformLocation(m_pg->GetId(), "MVP");
    }
    {//reset
        glDisableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }
    return true;
}
void AppChap1_5::Tick(const double DeltaTime){
    Application::Tick(DeltaTime);
}

void AppChap1_5::Render(){
    m_pg->UseProgram();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glUniformMatrix4fv(MVPLocation, 1, GL_TRUE, &MVP[0][0]);
    m_pg->UseProgram();
    glScissor(100, 100, 400, 400);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void AppChap1_5::OnKeyEvent(int key, int scancode, int action, int mods){
    Application::OnKeyEvent(key, scancode, action, mods);
    
    if(action == GLFW_PRESS){
        return;
    }else{
        std::cout << "key press" << std::endl;
    }
}
