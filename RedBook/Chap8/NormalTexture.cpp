#include "NormalTexture.h"

static GLuint State;

NormalTexture::NormalTexture():camera(NX::float3(0, 0, 0), NX::float3(0, 0, 1), NX::float3(0, 1, 0), 90, 1, 1, 2000){
    
}

NormalTexture::~NormalTexture(){
    
}


bool NormalTexture::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    
    {//shader
        m_pg = new NX::Program();
        m_pg->AddShader("./redbook/chap8/NormalTextureVS.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./redbook/chap8/NormalTextureFS.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
        
        MVLocation      = glGetUniformLocation(m_pg->GetId(), "MV");
        MVPLocation     = glGetUniformLocation(m_pg->GetId(), "MVP");
        LightLocation   = glGetUniformLocation(m_pg->GetId(), "LightDirection");
        TextureLocation = glGetUniformLocation(m_pg->GetId(), "Texture");
        NormalLocation  = glGetUniformLocation(m_pg->GetId(), "Normal");
    }
    
    {//vertex
        v[0] = {NX::float3(-400, -400, 500), NX::float2(0, 0)};
        v[1] = {NX::float3(-400, 400, 500),   NX::float2(0, 1)};
        v[2] = {NX::float3(400, 400, 500),   NX::float2(1, 1)};
        v[3] = {NX::float3(400, -400, 500),  NX::float2(1, 0)};
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
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, vUV));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }
    
    {//ibo
        ubyte idx[] = {1, 0, 2, 3};
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
    }
    
    {//texture
        NX::Texture * tex = new NX::Texture();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex->Load("./redbook/image/Textures/lion.tga"));
        glUniform1i(TextureLocation, 0);
    }
    
    {//normal
        NX::Texture *tex = new NX::Texture();
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex->Load("image/Textures/lion_ddn.tga"));
        glUniform1i(NormalLocation, 1);
    }
    return true;
}

void NormalTexture::Tick(const double DeltaTime){
    
}

void NormalTexture::Render(){
    glClearColor(0.3, 0.3, 0.3, 1);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    auto MVP = camera.GetWatchMatrix();
    glUniformMatrix4fv(MVPLocation, 1, GL_TRUE, &MVP[0][0]);
    
    auto MV = camera.GetMVMatrix();
    glUniformMatrix4fv(MVLocation, 1, GL_TRUE, &MV[0][0]);
    
    auto LightDir = NX::float4(0, 1, 1, 0);
    glUniform4fv(LightLocation, 1, &LightDir[0]);
    
    glEnable(GL_DEPTH_TEST);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
}

void NormalTexture::OnKeyEvent(int key, int scancode, int action, int mods){
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

void NormalTexture::OnCursorPositionEvent(double xByScreen, double yByScreen){
    static double xPrePos = xByScreen;
    static double yPrePos = yByScreen;
    if(State == GLFW_PRESS){
        camera.RotateByLeftRightAxis((yByScreen - yPrePos) * 0.001);
        camera.RotateByUpDownAxis((xByScreen - xPrePos) * 0.01);
    }
    xPrePos = xByScreen;
    yPrePos = yByScreen;
}

void NormalTexture::OnMouseButtonEvent(int btn,int action,int mods){
    State = action;
}