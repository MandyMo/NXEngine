#include "SkyBox.h"


bool SkyBox::Init(__in const char* vCmdLine[], __in const int iCmdCount, __in const int iWidth, __in const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    
    {//shader
        m_pg = new NX::Program();
        m_pg->AddShader("./redbook/Chap6/SkyBoxVS.glsl", GL_VERTEX_SHADER);
        m_pg->AddShader("./redbook/Chap6/SkyBoxFS.glsl", GL_FRAGMENT_SHADER);
        m_pg->LinkProgram();
        m_pg->UseProgram();
        m_MVPLocation     = glGetUniformLocation(m_pg->GetId(), "MVP");
        m_CubeTexLocation = glGetUniformLocation(m_pg->GetId(), "CubeTex");
    }
    {//cubte texture
        NX::float4X4 MVP = NX::GetPerspectiveMatrix(90.f, 1.0f, 1.f, 1000.f) * NX::GetLookAtMatrix(NX::float3(0, 0, 0), NX::float3(0, 0, 1), NX::float3(0, 1, 0));
        glUniformMatrix4fv(m_MVPLocation, 1, GL_TRUE, &MVP[0][0]);
        
        glActiveTexture(GL_TEXTURE0);
        std::vector<std::string> strImgSet;
        strImgSet.push_back("image/SkyBox/SkyBox1/Top.bmp");
        strImgSet.push_back("image/SkyBox/SkyBox1/Bottom.bmp");
        strImgSet.push_back("image/SkyBox/SkyBox1/Right.bmp");
        strImgSet.push_back("image/SkyBox/SkyBox1/Left.bmp");
        strImgSet.push_back("image/SkyBox/SkyBox1/Front.bmp");
        strImgSet.push_back("image/SkyBox/SkyBox1/Back.bmp");
        GLuint  CubeTex = CreateSkyBox(strImgSet);
        glBindTexture(GL_TEXTURE_CUBE_MAP, CubeTex);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glUniform1i(m_CubeTexLocation, 0);
    }
    {//vao
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
    }
    
    {//vertex buffer
        v[0] = {NX::float3(-900, 900, -900)};
        v[1] = {NX::float3(-900, 900, 900)};
        v[2] = {NX::float3(900, 900, 500)};
        v[3] = {NX::float3(900, 900, -900)};
        v[4] = {NX::float3(-900, -900, -900)};
        v[5] = {NX::float3(-900, -900, 900)};
        v[6] = {NX::float3(900, -900, 900)};
        v[7] = {NX::float3(900, -900, -900)};

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(0));
        glEnableVertexAttribArray(0);
    }
    
    {//index buffer
        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        GLubyte idx[][6] = {
            {0, 1, 2, 0, 2, 3},//top
            {4, 5, 6, 4, 6, 7},//bottom
            {0, 1, 5, 0, 5, 4},//left
            {3, 2, 6, 3, 6, 7},//right
            {3, 0, 4, 3, 4, 7},//back
            {2, 1, 5, 2, 5, 6},//front
        };
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
    }
    
    return true;
}

void SkyBox::Render(){
    glClearColor(0, 0, 0, 1);
    glClearDepth(1.0f);
    glDepthRange(0, 1);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_pg->UseProgram();
    
    glBindVertexArray(m_vao);
    
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
    return;
}

static void FlipImage(NX::ImagePixelLoader * loader);

GLuint SkyBox::CreateSkyBox(__in const std::vector<std::string>& strFilePathSet){
    GLuint  TexId;
    glGenTextures(1, &TexId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, TexId);
    GLenum face[] = {
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
    };
    
    NX::ImagePixelLoader Loader[6];
    for(int i = 0; i < 6; ++i){
        Loader[i].Load(strFilePathSet[i]);
    }
    
    for(int i = 0; i < 6; ++i){
        FlipImage(Loader + i);
        glTexImage2D(face[i], 0, GL_RGBA, Loader[i].Width(), Loader[i].Height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, Loader[i].Pixels());
    }
    
    return TexId;
}

static void FlipImage(NX::ImagePixelLoader * loader){
    int end = loader->Height() - 1, begin = 0;
    int width = loader->Width();
    unsigned int* pixel = (unsigned int*)loader->Pixels();
    unsigned int *l, *r;
    while(begin < end){
        for(int i = 0; i < width; ++i){
            l = pixel + begin * width + i;
            r = pixel + end   * width + i;
            std::swap(*l, *r);
        }
        ++begin;
        --end;
    }
}

void SkyBox::Tick(const double DeltaTime){
    static float Sum = 0;
    Sum += DeltaTime / 10;
    NX::float4X4 MV = NX::GetLookAtMatrix(NX::float3(0, 0, 0), NX::float3(0, 0, 1), NX::float3(0, 1, 0)) * NX::GetTranslated(0.0f, 0.0f, 0.f) * NX::GetMatrixRotateByY(Sum);
    NX::float4X4 P  = NX::GetPerspectiveMatrix(120.f, 1.0f, 1.f, 2000.f) ;
    NX::float4X4 MVP = P * MV;
    glUniformMatrix4fv(m_MVPLocation, 1, GL_TRUE, &MVP[0][0]);
    return;
}