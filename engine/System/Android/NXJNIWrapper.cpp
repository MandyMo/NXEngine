/*
 *  NXJNIWrapper.cpp
 *
 *  Date:    2016_07_29
 *  Author:  张雄
 *  purpose: 用于获取JNIEnv结构的类和少量调试函数
 */

#if defined(PLATFORM_ANDROID)

#include "NXJNIWrapper.h"
#include "../../common/NXLog.h"

JavaVM* NX::JNIWrapper::g_JVM           = NULL;
int     NX::JNIWrapper::m_JNI_VERSION   = JNI_VERSION_1_6;

/**
 *   sava JavaVM pointer
 */
extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void* reserved){
    NX::glb_GetLog().logToConsole("saved JavaVM pointer succedd");
    NX::JNIWrapper::g_JVM =vm;
    return JNIWrapper::m_JNI_VERSION;
}

NX::JNIWrapper::JNIWrapper(){
    m_pEnv = NULL;
    m_bOk  = false;
    if(g_JVM->GetEnv((void**)&m_pEnv, m_JNI_VERSION) != JNI_OK){
        m_bOk = g_JVM->AttachCurrentThread(&m_pEnv, NULL) >= 0;
    }else{
        m_bOk = false;
    }
}

NX::JNIWrapper::~JNIWrapper(){
    if(m_bOk){
        g_JVM->DetachCurrentThread();
        m_pEnv = NULL;
        m_bOk  = false;
    }
}

#endif //!PLATFORM_ANDROID