#include "SkyBox1.h"
#include "../engine/math/NXAlgorithm.h"
SkyBox1::SkyBox1(){

}

SkyBox1::~SkyBox1(){
}

bool SkyBox1::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    {//shader
        NX::Program *pg = new NX::Program();
        pg->AddShader("./Chap1/VS1_9.glsl", GL_VERTEX_SHADER);
        pg->AddShader("./Chap1/FS1_9.glsl", GL_FRAGMENT_SHADER);
        pg->LinkProgram();
        m_PositionLocation = glGetAttribLocation(pg->GetId(), "Position");
        m_UVWLocation      = glGetAttribLocation(pg->GetId(), "cUV");
        m_SkyBoxTextureSamplerLocation = glGetUniformLocation(pg->GetId(), "SMP2D");
        m_MVP              = glGetUniformLocation(pg->GetId(), "MVP");
        pg->UseProgram();
    }
    {//vertex
        memset(m_v, 0, sizeof(m_v));
        {//top
            m_v[0] = {NX::float3(-1000, 1000, 1000),   NX::float2(0.5, 2.0 / 3)};
            m_v[1] = {NX::float3(-1000, 1000, -1000),  NX::float2(0.5, 1.0)};
            m_v[2] = {NX::float3(1000, 1000, 1000),    NX::float2(0.25, 2.0 / 3)};
            m_v[3] = {NX::float3(1000, 1000, -1000)},  NX::float2(0.25, 1.0);
        }
        
        {//bottom
            m_v[4] = {NX::float3(-1000, -1000, 1000),   NX::float2(0.5, 1.0 / 3)};
            m_v[5] = {NX::float3(-1000, -1000, -1000),  NX::float2(0.5, 0)};
            m_v[6] = {NX::float3(1000, -1000, 1000),    NX::float2(0.25, 1.0 / 3)};
            m_v[7] = {NX::float3(1000, -1000, -1000)},  NX::float2(0.25, 0);
        }
        
        {//left
            m_v[8] =  {NX::float3(-1000, 1000, -1000),   NX::float2(0.5, 2.0 / 3)};
            m_v[9] =  {NX::float3(-1000, 1000, 1000),    NX::float2(0.25, 2.0 / 3)};
            m_v[10] = {NX::float3(-1000, -1000, -1000),  NX::float2(0.5, 1.0 / 3)};
            m_v[11] = {NX::float3(-1000, -1000, 1000),   NX::float2(0.25, 1.0 / 3)};
        }
        
        {//right
            m_v[12] = {NX::float3(1000, 1000, -1000),    NX::float2(0.75, 2.0 / 3)};
            m_v[13] = {NX::float3(1000, 1000, 1000),    NX::float2(1.0,  2.0 / 3)};
            m_v[14] = {NX::float3(1000, -1000, -1000),  NX::float2(0.75, 1.0 / 3)};
            m_v[15] = {NX::float3(1000, -1000, 1000),   NX::float2(1.0,  1.0 / 3)};
        }
        
        {//front
            m_v[16] = {NX::float3(-1000, 1000, 1000),   NX::float2(0.25, 2.0 / 3)};
            m_v[17] = {NX::float3(-1000, -1000, 1000),  NX::float2(0.25, 1.0 / 3)};
            m_v[18] = {NX::float3(1000, 1000, 1000),    NX::float2(0, 2.0 / 3)};
            m_v[19] = {NX::float3(1000, -1000, 1000),   NX::float2(0, 1.0 / 3)};
        }
        
        {//back
            m_v[20] = {NX::float3(-1000, 1000, -1000), NX::float2(0.5, 2.0 / 3)};
            m_v[21] = {NX::float3(-1000, -1000, -1000), NX::float2(0.5, 1.0 / 3)};
            m_v[22] = {NX::float3(1000, 1000, -1000),   NX::float2(0.75, 2.0 / 3)};
            m_v[23] = {NX::float3(1000, -1000, -1000),   NX::float2(0.75, 1.0 / 3)};
        }
        
        {//vao
            glGenVertexArrays(1, &m_vao);
            glBindVertexArray(m_vao);
        }
        
        {//vbo
            GLuint  vbo;
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(m_v), BUFFER_OFFSET(m_v), GL_STATIC_DRAW);
            glVertexAttribPointer(m_PositionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), CLS_MEM_OFFSET(Vertex, Position));
            glVertexAttribPointer(m_UVWLocation,      2, GL_FLOAT, GL_FALSE, sizeof(Vertex), CLS_MEM_OFFSET(Vertex, UV));
            glEnableVertexAttribArray(m_PositionLocation);
            glEnableVertexAttribArray(m_UVWLocation);
        }
        
        {//ibo
            GLuint ibo;
            glGenBuffers(1, &ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            GLubyte  idx[36] = {
                0, 1, 2, 1, 2, 3,
                4, 5, 6, 5, 6, 7,
                8, 9, 10, 9, 10, 11,
                12, 13, 14, 13, 14, 15,
                16, 17, 18, 17, 18, 19,
                20, 21, 22, 21, 22, 23
            };
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), BUFFER_OFFSET(idx), GL_STATIC_DRAW);
        }
        
        {//sampler
            NX::Texture * texture = new NX::Texture;
            m_SKyBoxTextureId = texture->Load("image/skybox2.png");
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_SKyBoxTextureId);
            glUniform1i(m_SkyBoxTextureSamplerLocation, 0);
        }
    }
    return true;
}

void SkyBox1::Tick(const double DeltaTime){
    Application::Tick(DeltaTime);
  }

void SkyBox1::Render(){
    glClearColor(0, 0, 0, 0);
    glClearDepth(2.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    auto MVP = NX::Perspective<float>(75, 1.0, 1.0, 20000.0) * NX::LookAt<float>(NX::float3(0, 0, 0), NX::float3(1, 0, 0), NX::float3(0, 1, 0));
    static float radius = 0;
    radius += 0.003;
    auto R = NX::RotateY(radius);
    MVP = MVP * R;
    glUniformMatrix4fv(m_MVP, 1, GL_TRUE, &MVP[0][0]);
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
}

void SkyBox1::OnKeyEvent(int key, int scancode, int action, int mods){
    Application::OnKeyEvent(key, scancode, action, mods);
    if(action == GLFW_PRESS){
        return;
    }else{
        std::cout << "key press" << std::endl;
    }
}
