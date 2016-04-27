
#include "TFBDemo.h"
#include "../engine/common/NXLog.h"
#include "../engine/render/NXShaderManager.h"
#include "../engine/system/NXSystem.h"
#include "iostream"
using namespace std;

static int State;

TFBDemo::TFBDemo():m_Camera(NX::float3(0, 0, 100), NX::float3(0, 0, 300), NX::float3(0, 1, 0), 90, 1.0f, 1.0f, 5000.f){
    NX::glb_GetLog().logToConsole("TFBDemo::TFBDemo():m_Camera(NX::float3(-1, -1, -1), NX::float3(1, 1, 1), NX::float3(0, 1, 0), 90, 1.0f, 1.0f, 1000.f)");
}


TFBDemo::~TFBDemo(){
    
}

bool TFBDemo::Init(__in const char* vCmdLine[], __in const int iCmdCount,
                   __in const int iWidth, __in const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    
    {//vao
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
    }
    
    {//vertex data
        v[0] = {NX::float3(-400, 400, 500)};
        v[1] = {NX::float3(-400, -400, 500)};
        v[2] = {NX::float3(400, 400, 500)};
        v[3] = {NX::float3(400, -400, 500)};
    }
    
    {//vbo
        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
    }
    
    {//ibo
        ubyte idx[] = {0, 1, 2, 1, 2, 3};
        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), CLS_MEM_OFFSET(Vertex, Position));
    }
    
    {//program
        m_pg = new NX::Program();
        NX::ShaderManager &SM = NX::ShaderManager::Instance();
        m_pg->AddShader(SM.FetchShaderResource("./redbook/Chap10/TFBDemoVS.glsl", GL_VERTEX_SHADER));
        m_pg->LinkProgram();
        m_MVPLocation = glGetUniformLocation(m_pg->GetId(), "MVP");
        
        m_pfb = new NX::Program();
        m_pfb->AddShader(SM.FetchShaderResource("./redbook/Chap10/TFBDemoVS.glsl", GL_VERTEX_SHADER));
        m_pfb->AddShader(SM.FetchShaderResource("./redbook/Chap10/TFBDemoFS.glsl", GL_FRAGMENT_SHADER));
        m_pfb->LinkProgram();
    }
    
    {//tfb
        glGenTransformFeedbacks(1, &m_TFBO);
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_TFBO);
        
        glGenBuffers(1, &m_TFB);
        glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, m_TFB);
        glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, 10000, NULL, GL_DYNAMIC_COPY);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_TFB);
    }
    return true;
}

void TFBDemo::Render(){
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0f);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glEnable(GL_DEPTH_TEST);

    {//
        m_pg->UseProgram();
        glEnable(GL_RASTERIZER_DISCARD);
        glBeginTransformFeedback(GL_TRIANGLES);
        static const char *name[] = {"TPosition"};
        glTransformFeedbackVaryings(m_pg->GetId(), 1, name, GL_INTERLEAVED_ATTRIBS);
        m_pg->LinkProgram();
        m_pg->UseProgram();
        auto MVP = m_Camera.GetWatchMatrix();
        glUniformMatrix4fv(m_MVPLocation, 1, GL_TRUE, &MVP[0][0]);
        glEnableVertexAttribArray(0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
        glEndTransformFeedback();
    }
    
    {//read data
        const char *name[] = {"first", "second", "third", "fourth"};
        glBindBuffer(GL_PIXEL_PACK_BUFFER, m_TFB);
        float * ptr = (float*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
        for(int i = 0; i < 4; ++i){
            NX::glb_GetLog().logToConsole("The %s vertex is [%.2f, %.2f, %.2f, %.2f]\n", name[i], *ptr++, *ptr++, *ptr++, *ptr++);
        }
        glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
    }
    
    {//draw tfb
        glBindVertexArray(m_vao);
        glDisable(GL_RASTERIZER_DISCARD);
        m_pfb->UseProgram();
        glEnableVertexAttribArray(0);
        glDrawTransformFeedback(GL_TRIANGLES, m_TFBO);
    }
    
    NX::System& ST = NX::System::Instance();
    ST.Sleep(1000);
}

void TFBDemo::OnCursorPositionEvent(double xByScreen, double yByScreen){
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

void TFBDemo::OnKeyEvent(int key, int scancode, int action, int mods){
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
        //OutValue += 2;
    }else if(key == GLFW_KEY_2){
        //OutValue -= 2;
        //NX::ClampFloor(OutValue, 1);
    }
}