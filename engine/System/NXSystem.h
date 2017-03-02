/*
 *  File:    NXSystem.h
 *
 *  author:  张雄
 *  date:    2016_04_27
 *  purpose: define a general interface for some system relative call
 */

#ifndef __ZX_NXENGINE_SYSTEM_H__
#define __ZX_NXENGINE_SYSTEM_H__

#include "../common/NXCore.h"

namespace NX {
    class System{
    public:
        System();
        virtual ~System() = 0;
        static System& Instance();
    public:
        virtual void Sleep(__in const unsigned int iMilliSeconds) = 0;
        virtual bool FileExist(__in const std::string& strFilePath) = 0;
        virtual bool DeleteFile(__in const std::string& strFilePath);
        virtual bool CreateFileDirectory(__in const std::string& strDirPath) = 0;
        virtual bool DeleteFileDirectory(__in const std::string& strDirPath) = 0;
        virtual NXInt64 GetMillSecondsFromSystemStart() = 0;
    };
}

#endif //!__ZX_NXENGINE_SYSTEM_H__
