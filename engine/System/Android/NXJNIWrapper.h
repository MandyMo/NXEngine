/*
 *  NXJNIWrapper.h
 *
 *  Date:    2016_07_29
 *  Author:  张雄
 *  purpose: 用于获取JNIEnv结构的类和少量调试函数
 */

#ifndef __ZX_NXENGINE_JNIWRPAPPER_H__
#define __ZX_NXENGINE_JNIWRPAPPER_H__

#include "../../common/NXCore.h"

#ifdef PLATFORM_ANDROID

#include <jni.h>

namespace NX{
    class JNIWrapper{
    public:
        JNIWrapper();
        ~JNIWrapper();
    public:
        JNIEnv* GetEnv(){
            return m_pEnv;
        }
    private:
        JNIEnv		*m_pEnv;
        bool        m_bOk;
    public:
        static int          m_JNI_VERSION;
        static JavaVM*      g_JVM;
    };
}
#endif	//!PLATFORM_ANDROID
#endif	//!__ZX_NXENGINE_JNIWRPAPPER_H__