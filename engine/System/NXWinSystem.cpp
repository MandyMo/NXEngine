/*
 *  File:    NXWinSystem.cpp
 *
 *  author:  张雄
 *  date:    2016_07_24
 *  purpose: implementation for some win32 systemcall
 */

#include "NXSystem.h"

#if defined(PLATFORM_WINDOWS)

#ifdef PLATFORM_WINDOWS
#include <Windows.h>

namespace NX {
    class WinSystem: public NX::System{
    public:
        WinSystem();
        virtual ~WinSystem();
    public:
        virtual void Sleep(__in const unsigned int iMilliSeconds);
        virtual bool FileExist(__in const std::string& strFilePath);
        virtual bool DeleteDirectory(__in const std::string& strDirPath);
        virtual bool CreateDirectory(__in const std::string& strDirPath);
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
    
    bool WinSystem::DeleteDirectory(__in const std::string& strDirPath){
        if(!NX::System::Instance().IsFileExist(strDirPath)){
            return true;
        }
        char szSearchFinal[MAX_PATH];
        strcpy(szSearchFinal, strDirPath.c_str());
        strcat(szSearchFinal,  "/*");
        WIN32_FIND_DATAA dataFile;
        HANDLE hSearch = ::FindFirstFileA(szSearchFinal, &dataFile);
        if(hSearch != NULL){
            do{
                if(strcmp(dataFile.cFileName, ".") == 0)
                    continue;
                if(strcmp(dataFile.cFileName, "..") == 0)
                    continue;
                strcpy(szSearchFinal, szDir);
                strcat(szSearchFinal, "/");
                strcat(szSearchFinal, dataFile.cFileName);
                if(dataFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
                    NX::System::Instance().DeleteDirectory(szSearchFinal);
                }else{
                    NX::System::Instance().DeleteFile(szSearchFinal);
                }
            } while (::FindNextFileA(hSearch, &dataFile));
            ::FindClose(hSearch);
            return ::RemoveDirectoryA(szDir);
        }
        return false;
    }
    
    bool WinSystem::FileExist(__in const std::string& strFilePath){
        WIN32_FIND_DATA FindFileData;
        NX::NXZeroMemory(&FindFileData);
        HANDLE hFind = ::FindFirstFile(strDirPath.c_str(), &FindFileData);
        if (hFind == INVALID_HANDLE_VALUE) {
            return false;
        }else {
            ::FindClose(hFind);
            return true;
        }
    }
    
    NXInt64 WinSystem::GetMillSecondsFromSystemStart(){
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

#endif


