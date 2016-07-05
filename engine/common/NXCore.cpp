/*
 *  File:     NXCore.cpp
 *  Author:   张雄
 *  Date:     2016_05_28
 *  Purpose:  引擎中需要使用的一些共公东西
 */

#include "NXLog.h"
#include "NXCore.h"


void NX::NXAssertFailed(const char *szFileName, const char *szFuncName, const int iLine, const char * expr){
    char MsgBuf[1024];
    std::sprintf(MsgBuf, "NXAssert failed at {[expr: %s] [file: %s] [func: %s] [line: %d]}", expr, szFileName, szFuncName, iLine);
    NX::glb_GetLog().logToConsole(MsgBuf);
    NX::glb_GetLog().log(MsgBuf);
}