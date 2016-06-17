
#include "AppChap1_6.h"
#include "NXShader.h"

#include <iostream>
using std::cout;
using std::endl;
AppChap1_6::AppChap1_6(){
    vao   = 0;
    vbo   = 0;
    m_pg  = NULL;
}

AppChap1_6::~AppChap1_6(){
    if(vao){
        glDeleteBuffers(1, &vao);
        glDeleteBuffers(1, &vbo);
        delete m_pg;
    }
}

bool AppChap1_6::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    {//create vertex
        memset(v, 0, sizeof(v));
        v[0] = {NX::float3(-200, 200, 200),  NX::float4(1, 0, 0, 1),    NX::float2(0, 1)};
        v[1] = {NX::float3(-200, -200, 200), NX::float4(0, 1, 0, 1),    NX::float2(0, 0)};
        v[2] = {NX::float3(200, 200, 200),   NX::float4(0, 0, 1, 1),    NX::float2(1, 1)};
        v[3] = {NX::float3(200, -200, 200),  NX::float4(1, 1, 1, 1),    NX::float2(1, 0)};
        
        memset(vm, 0, sizeof(vm));
        vm[0] = {NX::float3(-25, 25, 200),  NX::float2(0,1)};
        vm[1] = {NX::float3(-25, -25, 200), NX::float2(0,0)};
        vm[2] = {NX::float3(25,25,200),     NX::float2(1,1)};
        vm[3] = {NX::float3(25, -25, 200),  NX::float2(1,0)};
    }
    {//vao
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }
    
    {//vbo
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, Position));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, Color));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, UV));
    }
    
    {//ibo
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        const int idx[] = {0, 1, 2, 3};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
    }
    
    {//program & shader
        m_pg = new NX::Program();
        m_pg->AddShader("./Chap1/VS1_6.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./Chap1/FS1_6.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
    }
    {
        auto P = NX::GetPerspectiveMatrix<float>(90, 1, 1, 10000);
        auto V = NX::GetLookAtMatrix(NX::float3(0, 0, -200), NX::float3(0, 0, 1), NX::float3(0,1,0));
        auto M = NX::GetTranslated<float>(0, 0, 0);
        MVP = P * V * M;
    }
    {//translate matrix location
        MVPLocation = glGetUniformLocation(m_pg->GetId(), "MVP");
    }
    {//texture location
        m_tex = new NX::Texture();
        textureId = m_tex->Load("/zhangxiong/NXEngine/image/desktop.jpg");
        TexLocation = glGetUniformLocation(m_pg->GetId(), "text");
    }
    
    {//vao
        glGenVertexArrays(1, &vaom);
        glBindVertexArray(vaom);
    }
    {//vbo
        glGenBuffers(1, &vbom);
        glBindBuffer(GL_ARRAY_BUFFER, vbom);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vm), vm, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Mirror), CLS_MEM_OFFSET(Mirror, Position));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Mirror), CLS_MEM_OFFSET(Mirror, UV));

    }
    {//ibo
        glGenBuffers(1, &ibom);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibom);
        GLuint idx[] = {0,1,2,3};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
    }
    {//reset
        glDisableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    {//gentexture
        glGenTextures(1, &textureMirror);
        glBindTexture(GL_TEXTURE_2D, textureMirror);
       // glTextureStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, 800, 800);
    }
    return true;
}
void AppChap1_6::Tick(const double DeltaTime){
    Application::Tick(DeltaTime);
}

void AppChap1_6::Render(){
    m_pg->UseProgram();
    static double radius = 0;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    auto P = NX::GetPerspectiveMatrix<float>(90, 1, 1, 10000);
    auto V = NX::GetLookAtMatrix(NX::float3(0, -10, -100), NX::float3(0, 0, 1), NX::float3(0,1,0));
    auto M = NX::GetTranslated<float>(0, 0, 0);
    auto R = NX::GetMatrixRotateByZ(radius);
    radius += 0.001;
    MVP = P * R* V * M;
    glUniformMatrix4fv(MVPLocation, 1, GL_TRUE, &MVP[0][0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,textureId);
    glUniform1i(TexLocation, 1);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
    //glFlush();
    
    m_pg->UseProgram();
    glBindVertexArray(vaom);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(2);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureMirror);
    MVP = P * V * M;
    glReadBuffer(0);
    int pixel [800 * 800];
    glReadPixels(0, 0, 800, 800, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 512, 512, 0);
    cout<<glGetError()<<endl;
    glUniform1i(TexLocation, 0);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
}

void AppChap1_6::OnKeyEvent(int key, int scancode, int action, int mods){
    Application::OnKeyEvent(key, scancode, action, mods);
    
    if(action == GLFW_PRESS){
        return;
    }else{
        std::cout << "key press" << std::endl;
    }
}
