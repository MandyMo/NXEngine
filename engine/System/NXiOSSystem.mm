/*
 *  File:    NXiOSSystem.mm
 *
 *  author:  张雄
 *  date:    2016_07_24
 *  purpose: implementation for some OSX systemcall
 */

#include "NXPosixSystem.h"

#if defined(PLATFORM_IOS)

namespace NX{
    class IOSSystem: public NX::PosixSystem{
    public:
        IOSSystem();
        virtual ~IOSSystem();
        
    public:
        virtual NXInt64 GetMillSecondsFromSystemStart();
    };
    
    IOSSystem::IOSSystem(){
        //empty here
    }
    
    IOSSystem::~IOSSystem(){
        //empty here
    }
    
    System& System::Instance(){
        static IOSSystem SharedObject;
        return SharedObject;
    }
    
    NXInt64 IOSSystem::GetMillSecondsFromSystemStart(){
        timeval tp;
        gettimeofday(&tp, NULL);
        return (tp.tv_sec * 1000000LL + tp.tv_usec) / 1000;
    }
}
#endif
