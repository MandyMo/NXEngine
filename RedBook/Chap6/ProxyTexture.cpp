#include "ProxyTexture.h"


ProxyTexture::ProxyTexture(){
    NX::glb_GetLog().logToConsole("ProxyTexture::ProxyTexture()");
}

ProxyTexture::~ProxyTexture(){
    NX::glb_GetLog().logToConsole("ProxyTexture::~ProxyTexture()");
}


bool ProxyTexture::Init(__in const char* vCmdLine[], __in const int iCmdCount,
                        __in const int iWidth, __in const int iHeight){
    if(!NX::Application::Init(vCmdLine, iCmdCount, iWidth, iHeight)){
        return false;
    }
    
    
    GLuint ProxyId;
    glGenTextures(1, &ProxyId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_PROXY_TEXTURE_2D, ProxyId);
    glTexImage2D(GL_PROXY_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
    
    GLint maxTexWidth;
    glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &maxTexWidth);
    if(maxTexWidth){
        NX::glb_GetLog().logToConsole("create succeed");
    }else{
        NX::glb_GetLog().logToConsole("create failed");
    }
    return true;
}