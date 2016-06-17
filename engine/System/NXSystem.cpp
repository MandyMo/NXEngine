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

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
namespace NX {
    class WinSystem: public NX::System{
    public:
        WinSystem();
        virtual ~WinSystem();
    public:
        virtual void Sleep(__in const unsigned int iMilliSeconds);
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
namespace NX{
    class PosixSystem: public NX::System{
    public:
        PosixSystem();
        virtual ~PosixSystem();
    public:
        virtual void Sleep(__in const unsigned int iMilliSeconds);
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
