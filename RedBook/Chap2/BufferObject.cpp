#include "BufferObject.h"
#include "NXShader.h"

BufferObject::BufferObject(){
    vao   = -1;
    ibo   = -1;
    vbo   = -1;
    bbo   = -1;
    m_pg  = NULL;
}

BufferObject::~BufferObject(){
}

bool BufferObject::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    
    {//shader
        m_pg = new NX::Program();
        m_pg->AddShader("./RedBook/Chap2/BufferObjectVS.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./RedBook/Chap2/BufferObjectFS.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
    }
    
    {//vao
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }
    
    {//vbo & ibo
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        vertex  v[4];
        v[0] = {NX::float3(-0.8, 0.8, 0),    NX::float3(1.0f, 0.0f, 0.0f)};
        v[1] = {NX::float3(-0.8, -0.8, 0),   NX::float3(0.0f, 1.0f, 0.0f)};
        v[2] = {NX::float3(0.8f, 0.8f, 0),   NX::float3(0.0f, 0.0f, 1.0f)};
        v[3] = {NX::float3(0.8f, -0.8f, 0),  NX::float3(1.0f, 1.0f, 1.0f)};
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
        
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        ubyte idx[4] = {0, 1, 2, 3};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, Position));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, Color));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }
    
    {//bbo
        glGenBuffers(1, &bbo);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, bbo);
        int ary = 100;
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(int), &ary, GL_DYNAMIC_DRAW);
        //(GLuint program, const GLchar* uniformBlockName);
        glGetUniformBlockIndex(m_pg->GetId(), "BO");
    }
    
    {//subroutine
        GLuint idx = glGetSubroutineUniformLocation(m_pg->GetId(), GL_FRAGMENT_SHADER, "ColorFunc");
        GLuint self = glGetSubroutineIndex(m_pg->GetId(), GL_FRAGMENT_SHADER, "SelfColor");
        GLuint half = glGetSubroutineIndex(m_pg->GetId(), GL_FRAGMENT_SHADER, "HalfColor");
        int n;
        glGetIntegerv(GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS, &n);
        GLuint *idxs = new GLuint[n];
        idxs[idx] = half;
        glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, n, idxs);
    }
    return true;
}

void BufferObject::Tick(const double DeltaTime){
    
}

void BufferObject::Render(){
    glClearColor(0.0f, 0.25f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
}

void BufferObject::OnKeyEvent(int key, int scancode, int action, int mods){
    Application::OnKeyEvent(key, scancode, action, mods);
    if(action == GLFW_PRESS){
        return;
    }
}
