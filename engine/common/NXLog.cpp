/*
 *  File:    NXLog.cpp
 *  Author:  张雄
 *  Date:    2016_02_22
 *  purpose: 日志文件的实现
 */
#include "../System/NXMutex.h"
#include "NXLog.h"

#if defined(PLATFORM_IOS) || defined(PLATFORM_OSX)         //iOS OSX us std::cout
#include <iostream>
#elif defined(PLATFORM_ANDROID)                            //android us __android_log_print
#include <android/log.h>
#else                                                      //windows us OutputDebugStringA
#include <windows.h>
#pragma comment(lib, "kernel32.lib")
#endif

static char MsgBuf[1024];

#ifndef FORMAT_MSG_LOG_2016_02_22
#define FORMAT_MSG_LOG_2016_02_22 \
{\
va_list VarArgList;\
va_start(VarArgList, szFormat);\
vsprintf(MsgBuf, szFormat, VarArgList);\
va_end(VarArgList);\
}
#endif

NX::Log::Log(const std::string& strLogFilePath):m_strLogFilePath(strLogFilePath){
#if defined(PLATFORM_WINDOWS)
    AllocConsole();
    SetConsoleTitle(_T("Debug output"));
    freopen("CONOUT$","w",stdout);
#endif
    if(strLogFilePath != ""){
        m_outStream.open(m_strLogFilePath);
        log("log file [%s] open.", m_strLogFilePath.c_str());
    }
}

NX::Log::~Log(){
#if defined(PLATFORM_WINDOWS)
    FreeConsole();
#endif
    log("log file [%s] closed.", m_strLogFilePath.c_str());
    m_outStream.close();
}

void NX::Log::RedirectLogFile(const std::string& strNewLogFilePath){
    log("log file [%s] closed and switched to log file [%s].", m_strLogFilePath.c_str(), strNewLogFilePath.c_str());
    m_outStream.close();
    m_strLogFilePath = strNewLogFilePath;
    m_outStream.open(m_strLogFilePath);
}

void NX::Log::log(const char* szFormat, ...){
    FORMAT_MSG_LOG_2016_02_22
    m_outStream << GetTimeDescription() << "  " << MsgBuf << std::endl;
}

void NX::Log::log(__out std::string& strDst, __in const char *szFormat, ...){
    FORMAT_MSG_LOG_2016_02_22
    strDst =  GetTimeDescription();
    strDst += "  ";
    strDst += MsgBuf;
}

void NX::Log::logToConsole(__in const char *szFormat, ...){
    FORMAT_MSG_LOG_2016_02_22;
    std::string StrMsg = GetTimeDescription() + std::string(" ") + MsgBuf;
#if defined(PLATFORM_OSX) || defined(PLATFORM_IOS)
    std::cout << StrMsg << std::endl;
#elif defined(A_PLATFORM_ANDROID)
    __android_log_print(ANDROID_LOG_INFO, "JoyStick", "%s", StrMsg.c_str());
#else
    OutputDebugStringA(StrMsg.c_str());
    std::cout << StrMsg << std::endl;
#endif
}

std::string NX::Log::GetTimeDescription(){
    time_t GlobalTime = time(NULL);
    tm* pLocalTime = localtime(&GlobalTime);
    char buf[1024];
    sprintf(buf, "[%04d-%02d-%02d %02d:%02d:%02d]",
           pLocalTime->tm_year+1900, pLocalTime->tm_mon+1, pLocalTime->tm_mday,
           pLocalTime->tm_hour, pLocalTime->tm_min, pLocalTime->tm_sec);
    return buf;
}

#undef FORMAT_MSG_LOG_2016_02_22

namespace NX {
    Log& glb_GetLog(){
        static Log log("../render/NXEngine.txt");
        return log;
    }
}