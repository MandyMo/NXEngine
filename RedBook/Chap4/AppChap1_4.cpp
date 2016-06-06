
#include "AppChap1_4.h"
#include "NXShader.h"
#include "../engine/math/NXAlgorithm.h"
AppChap1_4::AppChap1_4(){
    vao   = 0;
    vbo   = 0;
    m_pg  = NULL;
}

AppChap1_4::~AppChap1_4(){
    if(vao){
        glDeleteBuffers(1, &vao);
        glDeleteBuffers(1, &vbo);
        delete m_pg;
    }
}

bool AppChap1_4::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    {//create vertex
        memset(v, 0, sizeof(v));
        v[1] = {NX::uint3(0, 0, 100),    NX::ubyte4(255, 0, 0, 128)};
        v[0] = {NX::uint3(800, 0, 100),  NX::ubyte4(255, 0, 0, 128)};
        v[2] = {NX::uint3(800, 800, 100),NX::ubyte4(255, 0, 0, 128)};
        v[3] = {NX::uint3(0, 800, 100),  NX::ubyte4(255, 0, 0, 128)};
        v[4] = {NX::uint3(200, 200, 100),NX::ubyte4(0, 255, 0, 128)};
        v[5] = {NX::uint3(600, 600, 100),NX::ubyte4(0, 255, 0, 128)};
        v[6] = {NX::uint3(200, 600, 100),NX::ubyte4(0, 255, 0, 128)};
    }
    {//vao
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }
    
    {//vbo
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_INT,           GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, Position));
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE,  sizeof(vertex), CLS_MEM_OFFSET(vertex, Color));
    }
    
    {//ibo
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        const int idx[] = {0, 1, 2, 3, 4, 5, 6};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
    }
    
    {//program & shader
        m_pg = new NX::Program();
        m_pg->AddShader("./RedBook/Chap4/VS1_4.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./RedBook/Chap4/FS1_4.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
    }
    {
        auto P = NX::GetPerspectiveMatrix<float>(90, 1, 1, 10000);
        auto V = NX::GetLookAtMatrix(NX::float3(0, 0, -300), NX::float3(0, 0, 0), NX::float3(0,1,0));
        auto M = NX::GetTranslated<float>(-400, -400, 0);
        MVP = P * V * M;
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
    {//        GLuint        fbo;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    }
        
    {//        GLuint        dbo;
        glGenRenderbuffers(1, &dbo);
        glBindRenderbuffer(GL_RENDERBUFFER, dbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 800, 800);
        glFramebufferRenderbuffer(GL_READ_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, dbo);
    }
    
    {//        Gluint        cbo;
        glGenRenderbuffers(1, &cbo);
        glBindRenderbuffer(GL_RENDERBUFFER, cbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, 800, 800);
        glFramebufferRenderbuffer(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, cbo);
        
        glGenRenderbuffers(1, &c1bo);
        glBindRenderbuffer(GL_RENDERBUFFER, c1bo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, 800, 800);
        glFramebufferRenderbuffer(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_RENDERBUFFER, c1bo);
    }

    return true;
}
void AppChap1_4::Tick(const double DeltaTime){
    Application::Tick(DeltaTime);
}

void AppChap1_4::Render(){
    //glDrawBuffer();
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
    GLuint buf[2] = {GL_COLOR_ATTACHMENT0,  GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2, buf);
    glBindFragDataLocation(m_pg->GetId(), 0, "vColor");
    glBindFragDataLocation(m_pg->GetId(), 1, "xColor");
    glClearColor(0.5f, 0.5, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 800, 800);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glUniformMatrix4fv(MVPLocation, 1, GL_TRUE, &MVP[0][0]);
    m_pg->UseProgram();
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)0);


    
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_READ_BUFFER     , fbo);
    glReadBuffer(GL_COLOR_ATTACHMENT1);
    glBlitFramebuffer(0, 0, 800, 800, 0, 0, 800, 800, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void AppChap1_4::OnKeyEvent(int key, int scancode, int action, int mods){
    Application::OnKeyEvent(key, scancode, action, mods);
    
    if(action == GLFW_PRESS){
        return;
    }else{
        std::cout << "key press" << std::endl;
    }
}
