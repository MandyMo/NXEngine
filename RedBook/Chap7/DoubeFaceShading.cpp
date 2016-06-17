#include "DoubeFaceShading.h"
using namespace std;

DoubleFaceShading::DoubleFaceShading(){
    vao   = -1;
    ibo   = -1;
    vbo   = -1;
    m_pg  = NULL;
}

DoubleFaceShading::~DoubleFaceShading(){
}

bool DoubleFaceShading::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    {//shader
        m_pg = new NX::Program();
        m_pg->AddShader("./RedBook/Chap7/DoubleFaceShadingVS.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./RedBook/Chap7/DoubleFaceShadingFS.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
    }
    
    {//vao
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }
    
    {//vbo & ibo
        vertex  v[4];
        v[0] = {NX::float3(-0.8, 0.8, 0.5),    NX::float3(1.0f, 0.0f, 0.0f)};
        v[1] = {NX::float3(-0.8, -0.8, 0.5),   NX::float3(0.0f, 1.0f, 0.0f)};
        v[2] = {NX::float3(0.8f, 0.8f, 0.5),   NX::float3(0.0f, 0.0f, 1.0f)};
        v[3] = {NX::float3(0.8f, -0.8f, 0.5),  NX::float3(1.0f, 1.0f, 1.0f)};
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
        
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        ubyte idx[] = {0, 1, 2, 1, 2, 3};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, Position));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, Color));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }
    
    {
        cout << glGetUniformLocation(m_pg->GetId(), "mmm[2]") << endl;
        cout << glGetUniformLocation(m_pg->GetId(), "nnn") << endl;
    }
    return true;
}

void DoubleFaceShading::Tick(const double DeltaTime){
    
}

void DoubleFaceShading::Render(){
    glClearColor(0.0f, 0.25f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
}

void DoubleFaceShading::OnKeyEvent(int key, int scancode, int action, int mods){
    Application::OnKeyEvent(key, scancode, action, mods);
    if(action == GLFW_PRESS){
        return;
    }
}
