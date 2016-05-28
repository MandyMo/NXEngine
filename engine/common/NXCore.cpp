/*
 *  File:     NXCore.cpp
 *  Author:   张雄
 *  Date:     2016_05_28
 *  Purpose:  引擎中需要使用的一些共公东西
 */

#include "NXLog.h"
#include "NXCore.h"


void NX::NXAssertFailed(const char *szFileName, const int iLine){
    char MsgBuf[1024];
    std::sprintf(MsgBuf, "NXAssert failed at {[file: %s] [line: %d]}", szFileName, iLine);
    NX::glb_GetLog().logToConsole(MsgBuf);
    NX::glb_GetLog().log(MsgBuf);
}

