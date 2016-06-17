#include "PointSprite.h"
#include "../../engine/math/NXAlgorithm.h"
bool PointSprite::Init(__in const char* vCmdLine[], __in const int iCmdCount, __in const int iWidth,       __in const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    
    {//shader
        m_pg = new NX::Program();
        m_pg->AddShader("./redbook/Chap6/PointSpriteVS.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./redbook/Chap6/PointSpriteFS.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
        
        m_MVPLocation = glGetUniformLocation(m_pg->GetId(), "MVP");
        m_TexLocation = glGetUniformLocation(m_pg->GetId(), "TexSprite");
    }
    
    {//vao
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
    }
    
    {//vertex
        memset(v, 0, sizeof(v));
        for(int i = 0; i < ARRAY_LENGTH(v); ++i){
            v[i] = {NX::float3(NX::RandFloatInRange(-400, 400), NX::RandFloatInRange(-400, 400), NX::RandFloatInRange(-1000, 1000)), NX::RandFloatInRange(1, 30)};
        }
    }
    
    {//vbo
        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, Position));
        glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(vertex), CLS_MEM_OFFSET(vertex, Position));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }
    
    {//ibo
        ubyte idx[ARRAY_LENGTH(v)];
        for(int i = 0; i < ARRAY_LENGTH(idx); ++i){
            idx[i] = i;
        }
        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
    }
    
    {//texture
        glActiveTexture(GL_TEXTURE1);
        NX::Texture* loader = new NX::Texture;
        glBindTexture(GL_TEXTURE_2D, loader->Load("image/smoke.tga"));
        glGenerateMipmap(GL_TEXTURE_2D);
        glUniform1i(m_TexLocation, 1);
    }
    
    {//MVP
        NX::float4X4 MVP = NX::GetOrthogonalMatrix<float>(800, 800, 1, 3000);
        //NX::float4X4 MVP = NX::Perspective(90.f, 1.f, 1.f, 1000.f);
        glUniformMatrix4fv(m_MVPLocation, 1, GL_TRUE, &MVP[0][0]);
    }
    return true;
}

void PointSprite::Render(){
    glClearColor(0.0, 0.0, 0.0, 0.0f);
    glClearDepth(1.0f);
    glDepthRange(0.f, 1.f);
    glEnable(GL_BLEND);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_ONE, GL_ONE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glDrawElements(GL_POINTS, ARRAY_LENGTH(v), GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
}

void PointSprite::Tick(const double DeltaTime){
    NX::Application::Tick(DeltaTime);
    static float Sum = 0;
    Sum += DeltaTime / 5;
    NX::float4X4 MVP = NX::GetOrthogonalMatrix<float>(800, 800, 1, 3000) * NX::GetMatrixRotateByY(Sum);
    glUniformMatrix4fv(m_MVPLocation, 1, GL_TRUE,  &MVP[0][0]);
}