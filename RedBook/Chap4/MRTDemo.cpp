
#include "MRTDemo.h"

static unsigned int uColorBuf = GL_COLOR_ATTACHMENT0;

MRT::MRT(){
    
}

MRT::~MRT(){
    
}

bool MRT::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    {//shader
        m_pg   = new NX::Program();
        m_pg->AddShader("./RedBook/Chap4/MRTVS.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./RedBook/Chap4/MRTFS.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
    }
    
    {//vertex
        v[0] = {NX::float3(-0.8, -0.8, 0.0), NX::float3(1.0f, 0.0f, 0.0f)};
        v[1] = {NX::float3(0.8, -0.8, 0.0),  NX::float3(0.0f, 1.0f, 0.0f)};
        v[2] = {NX::float3(-0.8, 0.8, 0.0),  NX::float3(0.0f, 0.0f, 1.0f)};
        v[3] = {NX::float3(0.8, 0.8, 0.0),   NX::float3(1.0f, 1.0f, 1.0f)};
    }
    
    {//vao
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }
    
    {//vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, Position));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, Color));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }
    
    {//ibo
        ubyte idx[] = {0, 1, 2, 3};
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx),idx, GL_STATIC_DRAW);
    }
    
    {//fbo
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        glGenRenderbuffers(1, &cboa);
        glBindRenderbuffer(GL_RENDERBUFFER, cboa);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, iWidth, iHeight);
        glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, cboa);
        
        glGenRenderbuffers(1, &cbob);
        glBindRenderbuffer(GL_RENDERBUFFER, cbob);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, iWidth, iHeight);
        glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_RENDERBUFFER, cbob);
        
        glGenRenderbuffers(1, &sdbo);
        glBindRenderbuffer(GL_RENDERBUFFER, sdbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, iWidth, iHeight);
        glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, sdbo);
    }
    return true;
}

void MRT::Tick(const double DeltaTime){
    
}

void MRT::Render(){
    m_pg->UseProgram();
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
    
    {//render to fbo
        glViewport(0, 0, 800, 800);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
        glBindFragDataLocation(m_pg->GetId(), 1, "ColorA");
        glBindFragDataLocation(m_pg->GetId(), 3, "ColorB");
        GLuint buf[] = {GL_COLOR_ATTACHMENT0,  GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
        //glDrawBuffers(3, buf);
        glDrawBuffer(GL_COLOR_ATTACHMENT0);
        glClearColor(0.5f, 0.5, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glDrawBuffer(GL_COLOR_ATTACHMENT1);
        glClearColor(0.0f, 0.0, 0.0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glDrawBuffers(3, buf);
        glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
    }
    
    {//copy to monitor
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
        glReadBuffer(uColorBuf);
        glViewport(0, 0, 800, 800);
        glBlitFramebuffer(0, 0, 800, 800, 0, 0, 800, 800, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    }
}

void MRT::OnKeyEvent(int key, int scancode, int action, int mods){
    Application::OnKeyEvent(key, scancode, action, mods);
    
    if(action == GLFW_PRESS){
        return;
    }else{
        if(uColorBuf == GL_COLOR_ATTACHMENT0){
            uColorBuf = GL_COLOR_ATTACHMENT1;
        }else{
            uColorBuf = GL_COLOR_ATTACHMENT0;
        }
    }
}
