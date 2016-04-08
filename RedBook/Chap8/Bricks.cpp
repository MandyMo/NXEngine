#include "Bricks.h"

static unsigned int State;

Bricks::Bricks():camera(NX::float3(0, 0, 0), NX::float3(0, 0.25, 1), NX::float3(0, 1, 0), 90, 1, 1, 1000){
}

Bricks::~Bricks(){
}

bool Bricks::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    {//vertex data
        v[0] = {NX::float3(-500, 500, 500)};
        v[1] = {NX::float3(-500, -500, 600)};
        v[2] = {NX::float3(500, 500, 700)};
        v[3] = {NX::float3(500, -500, 800)};
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
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        ubyte idx[] = {0, 1, 2, 1, 2, 3};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
    }
    
    {//shader
        m_pg = new NX::Program();
        m_pg->AddShader("./redBook/Chap8/BricksVS.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./redBook/Chap8/BricksFS.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
        MVPLocation  = glGetUniformLocation(m_pg->GetId(), "MVP");
    }
    
    camera.MoveUp(-200);
    camera.MoveRight(-200);
    return true;
}

void Bricks::Tick(const double DeltaTime){
    Application::Tick(DeltaTime);
    //camera.RotateByUpDownAxis(DeltaTime / 10);
}

void Bricks::Render(){
    glClearColor(0.3, 0.3, 0.3, 0);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    auto MVP = camera.GetWatchMatrix();
    glUniformMatrix4fv(MVPLocation, 1, GL_TRUE, &MVP[0][0]);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
}

void Bricks::OnCursorPositionEvent(double xByScreen, double yByScreen){
    static double xPrePos = xByScreen;
    static double yPrePos = yByScreen;
    if(State == GLFW_PRESS){
        camera.RotateByUpDownAxis((xByScreen - xPrePos) * 0.001);
        camera.RotateByLeftRightAxis((yByScreen - yPrePos) * 0.001);
    }
    xPrePos = xByScreen;
    yPrePos = yByScreen;
}

void Bricks::OnKeyEvent(int key, int scancode, int action, int mods){
    Application::OnKeyEvent(key, scancode, action, mods);
    if(key == GLFW_KEY_LEFT_CONTROL){
        State = action;
    }
    if(action != GLFW_PRESS){
        return;
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
    }
}
