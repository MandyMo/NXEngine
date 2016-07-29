/*
 *  File:    NXOSXSystem.cpp
 *
 *  author:  张雄
 *  date:    2016_07_24
 *  purpose: implementation for some OSX systemcall
 */

#include "../NXPosixSystem.h"

#if defined(PLATFORM_OSX)

#include <glob.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>   
#include <sys/time.h>
#include <dirent.h>

namespace NX{
    class OSXSystem: public NX::PosixSystem{
    public:
        OSXSystem();
        virtual ~OSXSystem();
        
    public:
        virtual NXInt64 GetMillSecondsFromSystemStart();
    };
    
    OSXSystem::OSXSystem(){
        //empty here
    }
    
    OSXSystem::~OSXSystem(){
        //empty here
    }
    
    System& System::Instance(){
        static OSXSystem SharedObject;
        return SharedObject;
    }
    
    NXInt64 OSXSystem::GetMillSecondsFromSystemStart(){
        timeval tp;
        gettimeofday(&tp, NULL);
        return (tp.tv_sec * 1000000LL + tp.tv_usec) / 1000;
    }
}


#endif //PLATFORM_OSX