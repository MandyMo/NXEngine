
#include "BricksSphere.h"


BricksSphere::BricksSphere():camera(NX::float3(0, 0, 0), NX::float3(0, 0, 1), NX::float3(0, 1, 0), 90, 1, 1, 3000){
    
}

BricksSphere::~BricksSphere(){
    
}

bool BricksSphere::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    
    {//shader
        m_pg = new NX::Program();
        m_pg->AddShader("./redbook/chap8/BricksSphereVS.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./redbook/chap8/BricksSphereFS.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
        MVPLocation = glGetUniformLocation(m_pg->GetId(), "MVP");
    }
    
    {//vertex
        v[0] = {NX::float3(0, 0, 500)};
        for(int i = 0; i <= 360; ++i){
            v[i] = {NX::float3(400 * NX::QuickCosWithAngle(i * 1.0f), 400 * NX::QuickSinWithAngle(i * 1.0f), 500)};
        }
    }
    
    {//vao
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }
    
    {//vbo
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, vPosition));
        glEnableVertexAttribArray(0);
    }
    
    return true;
}

static unsigned int State;

void BricksSphere::Tick(const double DeltaTime){
    
}

void BricksSphere::Render(){
    glClearColor(0.3, 0.3, 0.3, 0.3);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    auto MVP = camera.GetWatchMatrix();
    glUniformMatrix4fv(MVPLocation, 1, GL_TRUE, &MVP[0][0]);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 360);
}

void BricksSphere::OnKeyEvent(int key, int scancode, int action, int mods){
    Application::OnKeyEvent(key, scancode, action, mods);
    if(action != GLFW_RELEASE){
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

void BricksSphere::OnCursorPositionEvent(double xByScreen, double yByScreen){
    static double xPrePos = xByScreen;
    static double yPrePos = yByScreen;
    if(State == GLFW_PRESS){
        camera.RotateByLeftRightAxis((yByScreen - yPrePos) * 0.001);
        camera.RotateByUpDownAxis((xByScreen - xPrePos) * 0.01);
    }
    xPrePos = xByScreen;
    yPrePos = yByScreen;
}

void BricksSphere::OnMouseButtonEvent(int btn,int action,int mods){
    State = action;
}

