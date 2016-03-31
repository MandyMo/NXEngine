#include "DrawInstance.h"
#include "../engine/math/NXMath.h"
#define INSTANCE_COUNT 20

DrawInstance::DrawInstance(){
    
}

DrawInstance::~DrawInstance(){
    
}

bool DrawInstance::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    
    {//shader
        m_pg = new NX::Program();
        m_pg->AddShader("./RedBook/Chap3/DrawInstanceVS.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./RedBook/Chap3/DrawInstanceFS.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
    }
    
    {//vao
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        NX::float3 v = NX::float3(0.0f, 0.0f, 0.0f);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), &v, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glEnableVertexAttribArray(0);
    }
    
    {//color instance
        GLuint  cI;
        NX::float3 Color[INSTANCE_COUNT];
        for(int i = 0; i < INSTANCE_COUNT; ++i){
            Color[i].r = NX::RandUnitFloat();
            Color[i].g = NX::RandUnitFloat();
            Color[i].b = NX::RandUnitFloat();
        }
        glGenBuffers(1, &cI);
        glBindBuffer(GL_ARRAY_BUFFER, cI);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Color), Color, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Color[0]), BUFFER_OFFSET(0));
        glEnableVertexAttribArray(1);
        glVertexAttribDivisor(1, 1);
    }
    
    {//dif
        GLuint dI;
        glGenBuffers(1, &dI);
        glBindBuffer(GL_ARRAY_BUFFER, dI);
        NX::float2 Dif[INSTANCE_COUNT];
        for(int i = 0; i < INSTANCE_COUNT; ++i){
            Dif[i].x = 2 * NX::RandUnitFloat() - 1;
            Dif[i].y = 2 * NX::RandUnitFloat() - 1;
        }
        glBufferData(GL_ARRAY_BUFFER, sizeof(Dif), Dif, GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Dif[0]), BUFFER_OFFSET(0));
        glEnableVertexAttribArray(2);
        glVertexAttribDivisor(2, 1);
    }
    
    {//ibo
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        GLbyte idx[] = {0};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
    }
    
    {//clear
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glUseProgram(0);
    }
    GLint xx;
    glGetIntegerv(GL_SAMPLES, &xx);
    std::cout << "you know " << xx << std::endl;
    return true;
}

void DrawInstance::Tick(const double DeltaTime){
    
}

void DrawInstance::Render(){
    glClearColor(0.0f, 0.25f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glPointSize(15.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vao);
    m_pg->UseProgram();
    //glColorMask(0, 0, 0, 0);
    glDrawElementsInstanced(GL_POINTS, 1, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0), INSTANCE_COUNT);
}

void DrawInstance::OnKeyEvent(int key, int scancode, int action, int mods){
    Application::OnKeyEvent(key, scancode, action, mods);
    if(action == GLFW_PRESS){
        return;
    }
}