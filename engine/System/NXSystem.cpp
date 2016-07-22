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
        virtual NXInt64 GetMillSecondsFromSystemStart();
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
    
    virtual NXInt64 GetMillSecondsFromSystemStart(){
    	static LARGE_INTEGER TicksPerSecond = {0};
    	LARGE_INTEGER Tick;

    	if(!TicksPerSecond.QuadPart){
    		::QueryPerformanceFrequency(&TicksPerSecond);
    	}

    	::QueryPerformanceCounter(&Tick);
    	__int64 Seconds     = Tick.QuadPart/TicksPerSecond.QuadPart;
    	__int64 LeftPart    = Tick.QuadPart - (TicksPerSecond.QuadPart*Seconds);
    	__int64 MillSeconds = LeftPart*1000/TicksPerSecond.QuadPart;
    	__int64 Ret         = Seconds*1000+MillSeconds;
    	return Ret;
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
    	NXAssert(0 && "ios::not implemented");
    	return 0;
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

/**
 *  MAC OSX system only
 */
#ifdef PLATFORM_OSX
namespace NX{
    class OSXSystem: public PosixSystem{
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

    virtual OSXSystem::NXInt64 GetMillSecondsFromSystemStart(){
    	NXAssert(0 && "not implemented");
    	return 0;
    }
}
#endif
