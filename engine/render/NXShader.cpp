#include <fstream>
#include <string>

#include "NXShader.h"
#include "NXLog.h"


NX::Shader::Shader(const char* szFilePath, GLenum uShaderType){
    m_strShaderSourceFilePath = (szFilePath);
    m_uShaderId               = 0;
    m_uShaderType             = uShaderType;
}

NX::Shader::~Shader(){
    if(m_uShaderId != 0){
        glDeleteShader(m_uShaderId);
        m_uShaderId   = 0;
        m_uShaderType = 0;
    }
}

std::string NX::Shader::Compile(){
    std::string strErr(256 + 1, 0);
    m_uShaderId                    = glCreateShader(m_uShaderType);
    const std::string strShaderSrc = ReadShaderSource();
    if(strShaderSrc.empty()){
        sprintf((char*)strErr.c_str(), "shader file [%s] not exist or is empty", m_strShaderSourceFilePath.c_str());
        glb_GetLog().log("%s", strErr.c_str());
        return strErr;
    }
    const char * szShaderSrc = strShaderSrc.c_str();
    glShaderSource(m_uShaderId, 1, &szShaderSrc, NULL);
    glCompileShader(m_uShaderId);
    glGetShaderInfoLog(m_uShaderId, (GLuint)strErr.length(), NULL, &(strErr[0]));
    glb_GetLog().log("compile shader [type: %s] [file: %s] with compile msg [%s]", GetSaderTypeDescription(), m_strShaderSourceFilePath.c_str(),
                     (strErr[0] == 0 ? "Compile succeed" : strErr.c_str()));
    return strErr;
}

std::string NX::Shader::ReadShaderSource(){
    std::ifstream in(m_strShaderSourceFilePath);
    std::string line;
    std::string strShaderSrc;
    while(std::getline(in, line)){
        line          += "\r\n";
        strShaderSrc  += line;
    }
    in.close();
    return strShaderSrc;;
}

const char* NX::Shader::GetSaderTypeDescription() const{
    switch(m_uShaderType){
        case GL_VERTEX_SHADER:
            return "Vertex shader";
            break;
        case GL_FRAGMENT_SHADER:
            return "Fragment shader";
            break;
        case GL_TESS_CONTROL_SHADER:
            return "Tesslation control shader";
            break;
        case GL_TESS_EVALUATION_SHADER:
            return "Tesslation evaluation shader";
            break;
        case GL_GEOMETRY_SHADER:
            return "Geometry shader";
            break;
        default:
            return "unkonw shader";
    }
}