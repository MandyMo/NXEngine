/*
 *  File:    NXSystem.cpp
 *  author:  张雄
 *  date:    2016_04_27
 *  purpose: implement  some system relative call
 */

#include "NXSystem.h"

NX::System::System(){
    //empty here
}

NX::System::~System(){
    //empty here
}

bool NX::System::CreateDirectory(__in const std::string strDirPath){
    NXAssert(0 && "bool NX::System::CreateDirectory(__in const std::string strDirPath)");
    return false;
}

unsigned long NX::System::GetMillSeconds(){
    NXAssert("not implementation" && 1);
    return clock();
}

#ifdef PLATFORM_WINDOWS
#include <Windows.h>

namespace NX {
    class WinSystem: public NX::System{
    public:
        WinSystem();
        virtual ~WinSystem();
    public:
        virtual void Sleep(__in const unsigned int iMilliSeconds);
        virtual bool CreateDirectory(__in const std::string strDirPath);
        virtual unsigned long GetMillSeconds();
    };
    
    WinSystem::WinSystem(){
        //empty here
    }
    
    WinSystem::~WinSystem(){
        //empty here
    }
    
    void WinSystem::Sleep(__in const unsigned int iMilliSeconds){
        ::Sleep(iMilliSeconds);
    }
    
    bool WinSystem::CreateDirectory(__in const std::string strDirPath){
        return NX::System::CreateDirectory(strDirPath);
    }
    
    unsigned long WinSysteM::GetMillSeconds(){
        return NX::System::GetMillSeconds();
    }
    
    NX::System& NX::System::Instance(){
        static WinSystem SharedObject;
        return SharedObject;
    }
}
#endif  //PLATFORM_WINDOWS

/**
 *  Posix compatible system
 */
#if defined(PLATFORM_IOS) || defined(PLATFORM_ANDROID) || defined(PLATFORM_OSX)
#include <unistd.h>
#include <time.h>
namespace NX{
    class PosixSystem: public NX::System{
    public:
        PosixSystem();
        virtual ~PosixSystem();
    public:
        virtual void Sleep(__in const unsigned int iMilliSeconds);
        virtual bool CreateDirectory(__in const std::string strDirPath);
        virtual unsigned long GetMillSeconds();
    };
    
    PosixSystem::PosixSystem(){
        //empty here
    }
    
    PosixSystem::~PosixSystem(){
        //empty here
    }
    
    void PosixSystem::Sleep(__in const unsigned int iMilliSeconds){
        usleep(iMilliSeconds * 1000);
    }
    
    bool PosixSystem::CreateDirectory(__in const std::string strDirPath){
        return NX::System::CreateDirectory(strDirPath);
    }
    unsigned long PosixSystem::GetMillSeconds(){
        return NX::System::GetMillSeconds();
    }
}
#endif

/**
 *  IOS system only
 */
#ifdef PLATFORM_IOS
namespace NX{
    class IOSSystem: public PosixSystem{
    public:
        IOSSystem();
        virtual ~IOSSystem();
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
}
#endif

/**
 *  android system only
 */
#ifdef PLATFORM_ANDROID
namespace NX{
    class AndroidSystem: public PosixSystem{
    public:
        AndroidSystem();
        virtual ~AndroidSystem();
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
}
#endif

/**
 *  MAC OSX system only
 */
#ifdef PLATFORM_OSX
namespace NX{
    class OSXSystem: public PosixSystem{
    public:
        OSXSystem();
        virtual ~OSXSystem();
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
}
#endif
