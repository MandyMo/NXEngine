/*
 *  File:    NXAndroidSystem.cpp
 *
 *  author:  张雄
 *  date:    2016_07_24
 *  purpose: implementation for some OSX systemcall
 */

#include "../NXPosixSystem.h"

#if defined(PLATFORM_ANDROID)

namespace NX{
    class AndroidSystem: public NX::PosixSystem{
    public:
        AndroidSystem();
        virtual ~AndroidSystem();
    public:
        virtual NXInt64 GetMillSecondsFromSystemStart();
    };
    
    AndroidSystem::AndroidSystem(){
        //empty here
    }
    
    AndroidSystem::~AndroidSystem(){
        //empty here
    }
    
    System& System::Instance(){
        static AndroidSystem SharedObject;
        return SharedObject;
    }
    
    NXInt64 AndroidSystem::GetMillSecondsFromSystemStart(){
        timespec now;
        int err = clock_gettime(CLOCK_MONOTONIC, &now);
        return now.tv_sec* 1000LL + now.tv_nsec / 1000000;
    }
}

#endif