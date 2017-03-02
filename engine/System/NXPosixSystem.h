/*
 *  File:    NXPosixSystem.h
 *  author:  张雄
 *  date:    2016_07_24
 *  purpose: implementation for some posix based systemcall
 */

#ifndef __ZX_NXENGINE_POSIXSYSTEM_H__
#define __ZX_NXENGINE_POSIXSYSTEM_H__

#include "NXSystem.h"

#if defined(PLATFORM_IOS) || defined(PLATFORM_ANDROID) || defined(PLATFORM_OSX)

namespace NX{
    class PosixSystem: public NX::System{
    public:
        PosixSystem();
        virtual ~PosixSystem();
    public:
        virtual void Sleep(__in const unsigned int iMilliSeconds);
        virtual bool FileExist(__in const std::string& strFilePath);
        virtual bool CreateFileDirectory(__in const std::string& strDirPath);
        virtual bool DeleteFileDirectory(__in const std::string& strDirPath);
    };
}

#endif

#endif //!__ZX_NXENGINE_POSIXSYSTEM_H__
