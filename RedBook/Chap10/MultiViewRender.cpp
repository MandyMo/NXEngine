
#include "MultiViewRender.h"
#include "../engine/common/NXLog.h"
#include "../engine/render/NXShaderManager.h"
#include "../engine/system/NXSystem.h"
#include "../engine/math/NXMath.h"
#include "iostream"
using namespace std;

static int State;
uint Outer;
MultiViewRender::MultiViewRender():m_Camera(NX::float3(0, 0, 0), NX::float3(0, 0, 1), NX::float3(0, 1, 0), 90, 1.0f, 1.0f, 3000){
}


MultiViewRender::~MultiViewRender(){
    
}

bool MultiViewRender::Init(__in const char* vCmdLine[], __in const int iCmdCount,
                   __in const int iWidth, __in const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    
   
    {//vertex data
        v[0] = {NX::float3(-400, -400, 800)};
        v[1] = {NX::float3(400, 400, 400)};
        v[2] = {NX::float3(400, -400, 600)};
        v[3] = {NX::float3(-400, 400, 900)};
    }
    
    
    {//vao
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
    }
    
    {//vbo
        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), CLS_MEM_OFFSET(Vertex, Position));
        glEnableVertexAttribArray(0);
    }
    {//ibo
//        ubyte idx[] = {0, 1, 2, 1, 2, 3};
//        glGenBuffers(1, &m_ibo);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
    }
    
    {//program
        m_pg = new NX::Program();
        NX::ShaderManager &SM = NX::ShaderManager::Instance();
        m_pg->AddShader(SM.FetchShaderResource("./redbook/Chap10/MultiViewRenderVS.glsl",  GL_VERTEX_SHADER));
        m_pg->AddShader(SM.FetchShaderResource("./redbook/Chap10/MultiViewRenderTCS.glsl", GL_TESS_CONTROL_SHADER));
        m_pg->AddShader(SM.FetchShaderResource("./redbook/Chap10/MultiViewRenderTES.glsl", GL_TESS_EVALUATION_SHADER));
        m_pg->AddShader(SM.FetchShaderResource("./redbook/Chap10/MultiViewRenderGS.glsl",  GL_GEOMETRY_SHADER));
        m_pg->AddShader(SM.FetchShaderResource("./redbook/Chap10/MultiViewRenderFS.glsl",  GL_FRAGMENT_SHADER));
        m_pg->LinkProgram();
        m_pg->UseProgram();
        Outer = 4;
        m_MVPLocation    = glGetUniformLocation(m_pg->GetId(), "MVP");
        m_OuterLocation  = glGetUniformLocation(m_pg->GetId(), "Outer");
        m_ColorLocation  = glGetUniformLocation(m_pg->GetId(), "Color");
    }
    
    {//4 view port
        glViewportIndexedf(0, 0, 0, 400, 400);
        glViewportIndexedf(1, 0, 400, 400, 400);
        glViewportIndexedf(2, 400, 0, 400, 400);
        glViewportIndexedf(3, 400, 400, 400, 400);
    }
    
    {//color value
        NX::float4 cc[] = {
            NX::float4(1, 0, 0, 1),
            NX::float4(0, 1, 0, 1),
            NX::float4(0, 0, 1, 1),
            NX::float4(1, 1, 1, 1)
        };
        glUniform4fv(m_ColorLocation, 4, &cc[0].x);
    }
    return true;
}

void MultiViewRender::Render(){
    glClearColor(0.3, 0.3, 0.3, 0);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    {
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBindVertexArray(m_vao);
        m_pg->UseProgram();
        glPatchParameteri(GL_PATCH_VERTICES, 4);
        auto MVP = m_Camera.GetWatchMatrix();
        glUniformMatrix4fv(m_MVPLocation, 1, GL_TRUE, &MVP[0][0]);
        glUniform1i(m_OuterLocation, Outer);
        glDrawArrays(GL_PATCHES, 0, 4);
    }
    
//    NX::System& ST = NX::System::Instance();
//    ST.Sleep(1000);
}

void MultiViewRender::OnCursorPositionEvent(double xByScreen, double yByScreen){
    static double xPrePos = xByScreen;
    static double yPrePos = yByScreen;
    if(State == 1){
        m_Camera.RotateByUpDownAxis((xByScreen - xPrePos) * 0.001);
        m_Camera.RotateByLeftRightAxis((yByScreen - yPrePos) * 0.001);
    }else if(State == 2){
    }
    xPrePos = xByScreen;
    yPrePos = yByScreen;
}

void MultiViewRender::OnKeyEvent(int key, int scancode, int action, int mods){
    Application::OnKeyEvent(key, scancode, action, mods);
    if(action != GLFW_PRESS){
        State = 0;
        return;
    }
    if(key == GLFW_KEY_LEFT_CONTROL){
        State = 1;
    }else if(key == GLFW_KEY_LEFT_ALT){
        State = 2;
    }
    if(key == GLFW_KEY_LEFT){
        m_Camera.MoveLeft(50);
    }else if(key == GLFW_KEY_RIGHT){
        m_Camera.MoveRight(50);
    }else if(key == GLFW_KEY_UP){
        m_Camera.MoveUp(50);
    }else if(key == GLFW_KEY_DOWN){
        m_Camera.MoveDown(50);
    }else if(key == GLFW_KEY_W){
        m_Camera.MoveFront(50);
    }else if(key == GLFW_KEY_S){
        m_Camera.MoveBack(50);
    }else if(key == GLFW_KEY_PAGE_UP){
        m_Camera.RotateByLeftRightAxis(DG2RD(15));
    }else if(key == GLFW_KEY_PAGE_DOWN){
        m_Camera.RotateByLeftRightAxis(-DG2RD(15));
    }else if(key == GLFW_KEY_1){
        ++Outer;
    }else if(key == GLFW_KEY_2){
        --Outer;
        NX::ClampFloor(Outer, 2);
    }
}