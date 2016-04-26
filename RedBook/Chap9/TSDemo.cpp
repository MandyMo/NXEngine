#include "TSDemo.h"

static unsigned int State;

TSDemo::TSDemo():camera(NX::float3(0, 0, 0), NX::float3(0, 0, 1), NX::float3(0, 1, 0), 90, 1, 1, 3000){
}

TSDemo::~TSDemo(){
}

bool TSDemo::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    {//vertex data
        
        v[0] = {NX::float3(-400, 400, 500)};
        v[1] = {NX::float3(-400, -400, 500)};
        v[2] = {NX::float3(400, 400, 500)};
        v[3] = {NX::float3(400, -400, 500)};
//        v[0] = {NX::float3(0, 0, 400)};
//        v[1] = {NX::float3(0, 400, 0)};
//        v[2] = {NX::float3(400, 0, 0)};
//        
//        v[3] = {NX::float3(0, 0, 400)};
//        v[4] = {NX::float3(0, 400, 0)};
//        v[5] = {NX::float3(-400, 0, 0)};
//        
//        v[6] = {NX::float3(0, 0, 400)};
//        v[7] = {NX::float3(0, -400, 0)};
//        v[8] = {NX::float3(400, 0, 0)};
//        
//        v[9] = {NX::float3(0, 0, -400)};
//        v[10] = {NX::float3(0, 400, 0)};
//        v[11] = {NX::float3(400, 0, 0)};
//        
//        v[12] = {NX::float3(0, 0, -400)};
//        v[13] = {NX::float3(0, -400, 0)};
//        v[14] = {NX::float3(400, 0, 0)};
//        
//        v[15] = {NX::float3(0, 0, -400)};
//        v[16] = {NX::float3(0, 400, 0)};
//        v[17] = {NX::float3(-400, 0, 0)};
//        
//        v[18] = {NX::float3(0, 0, 400)};
//        v[19] = {NX::float3(0, -400, 0)};
//        v[20] = {NX::float3(-400, 0, 0)};
//        
//        v[21] = {NX::float3(0, 0, -400)};
//        v[22] = {NX::float3(0, -400, 0)};
//        v[23] = {NX::float3(-400, 0, 0)};
        
        
        
//        v[0] = {NX::float3(-400, 400, 400)};
//        v[1] = {NX::float3(-400, -400,400)};
//        v[2] = {NX::float3(400, 400, 400)};
//        v[3] = {NX::float3(-400, -400,400)};
//        v[4] = {NX::float3(400, 400, 400)};
//        v[5] = {NX::float3(400, -400, 400)};
//        
//        v[6] = {NX::float3(-400, 400, -400)};
//        v[7] = {NX::float3(-400, -400,-400)};
//        v[8] = {NX::float3(400, 400, -400)};
//        v[9] = {NX::float3(-400, -400,-400)};
//        v[10] = {NX::float3(400, 400, -400)};
//        v[11] = {NX::float3(400, -400, -400)};
//        
//        v[12] = {NX::float3(400, -400, 400)};
//        v[13] = {NX::float3(400, -400,-400)};
//        v[14] = {NX::float3(400, 400, 400)};
//        v[15] = {NX::float3(400, -400,-400)};
//        v[16] = {NX::float3(400, 400, 400)};
//        v[17] = {NX::float3(400, 400, -400)};
//        
//        v[18] = {NX::float3(-400, -400, 400)};
//        v[19] = {NX::float3(-400, -400,-400)};
//        v[20] = {NX::float3(-400, 400, 400)};
//        v[21] = {NX::float3(-400, -400,-400)};
//        v[22] = {NX::float3(-400, 400, 400)};
//        v[23] = {NX::float3(-400, 400, -400)};
//        
//        v[24] = {NX::float3(-400, 400, 400)};
//        v[25] = {NX::float3(-400, 400,-400)};
//        v[26] = {NX::float3(400, 400, 400)};
//        v[27] = {NX::float3(-400, 400,-400)};
//        v[28] = {NX::float3(400, 400, 400)};
//        v[29] = {NX::float3(400, 400, -400)};
//        
//        v[30] = {NX::float3(-400, -400, 400)};
//        v[31] = {NX::float3(-400, -400,-400)};
//        v[32] = {NX::float3(400, -400, 400)};
//        v[33] = {NX::float3(-400, -400,-400)};
//        v[34] = {NX::float3(400, -400, 400)};
//        v[35] = {NX::float3(400, -400, -400)};
    }
    
    {//vbo
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
    }
    
    {//vao
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, vPosition));
        glEnableVertexAttribArray(0);
    }
    
    {//ibo
    }
    
    {//shader
        m_pg = new NX::Program();
        m_pg->AddShader("./redBook/Chap9/TSDemoVS.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./redBook/Chap9/TSDemoFS.glsl", GL_FRAGMENT_SHADER);
        m_pg->AddShader("./redbook/Chap9/TSDemoTCS.glsl", GL_TESS_CONTROL_SHADER);
        m_pg->AddShader("./redbook/chap9/TSDemoTES.glsl", GL_TESS_EVALUATION_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
        MVPLocation  = glGetUniformLocation(m_pg->GetId(), "MVP");
    }
    
    return true;
}

void TSDemo::Tick(const double DeltaTime){
    Application::Tick(DeltaTime);
    //camera.RotateByUpDownAxis(DeltaTime / 10);
}

void TSDemo::Render(){
    glClearColor(0.3, 0.3, 0.3, 0);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    glPatchParameteri(GL_PATCH_VERTICES, 4);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    auto MVP = camera.GetWatchMatrix();
    glUniformMatrix4fv(MVPLocation, 1, GL_TRUE, &MVP[0][0]);
    glDrawArrays(GL_PATCHES, 0, 4);
    
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glDrawArrays(GL_PATCHES, 0, 3);
}

void TSDemo::OnCursorPositionEvent(double xByScreen, double yByScreen){
    static double xPrePos = xByScreen;
    static double yPrePos = yByScreen;
    if(State == 1){
        camera.RotateByUpDownAxis((xByScreen - xPrePos) * 0.001);
        camera.RotateByLeftRightAxis((yByScreen - yPrePos) * 0.001);
    }else if(State == 2){
    }
    xPrePos = xByScreen;
    yPrePos = yByScreen;
}

void TSDemo::OnKeyEvent(int key, int scancode, int action, int mods){
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
        camera.MoveLeft(50);
    }else if(key == GLFW_KEY_RIGHT){
        camera.MoveRight(50);
    }else if(key == GLFW_KEY_UP){
        camera.MoveUp(50);
    }else if(key == GLFW_KEY_DOWN){
        camera.MoveDown(50);
    }else if(key == GLFW_KEY_W){
        camera.MoveFront(50);
    }else if(key == GLFW_KEY_S){
        camera.MoveBack(50);
    }else if(key == GLFW_KEY_PAGE_UP){
        camera.RotateByLeftRightAxis(DG2RD(15));
    }else if(key == GLFW_KEY_PAGE_DOWN){
        camera.RotateByLeftRightAxis(-DG2RD(15));
    }
}
