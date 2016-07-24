/*
 *  File:    NXAndroidSystem.cpp
 *
 *  author:  张雄
 *  date:    2016_07_24
 *  purpose: implementation for some OSX systemcall
 */

#include "NXPosixSystem.h"

#if defined(PLATFORM_ANDROID)

namespace NX{
    class AndroidSystem: public NX::PosixSystem{
    public:
        AndroidSystem();
        virtual ~AndroidSystem();
    public:
        virtual NXInt64 GetMillSecondsFromSystemStart();
        virtual bool DeleteDirectory(__in const std::string& strDirPath);
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
    
    bool AndroidSystem::DeleteDirectory(__in const std::string& strDirPath){
        if(!NX::System::Instance().FileExist(strDirPath)){
            return true;
        }
        struct stat statbuf;
        if(lstat(szDir, &statbuf) != 0){
            return false;
        }
        if(S_ISREG(statbuf.st_mode) != 0){
            remove(szDir);
            return true;
        }
        if(S_ISDIR(statbuf.st_mode) == 0){
            return false;
        }
        DIR *dir = opendir(szDir);
        if(dir == NULL){
            return false;
        }
        char file_path[PATH_MAX];
        dirent *dir_info;
        while((dir_info = readdir(dir)) != NULL){
            strcpy(file_path, szDir);
            if(file_path[strlen(szDir) - 1] != '/'){
                strcat(file_path, "/");
            }
            strcat(file_path, dir_info->d_name);
            if(strcmp(dir_info->d_name, ".") == 0 || strcmp(dir_info->d_name, "..") == 0){
                continue;
            }else{
                DeleteDirectory(file_path);
            }
        }
        closedir(dir);
        rmdir(szDir);
        return true;
    }
    
}

#endif