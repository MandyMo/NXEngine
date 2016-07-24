/*
 *  File:    NXPosixSystem.cpp
 *  author:  张雄
 *  date:    2016_07_24
 *  purpose: implementation for some posix based systemcall
 */

#include "NXPosixSystem.h"

#if defined(PLATFORM_IOS) || defined(PLATFORM_ANDROID) || defined(PLATFORM_OSX)

#include <glob.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

namespace NX{
    PosixSystem::PosixSystem(){
        //empty here
    }
    
    PosixSystem::~PosixSystem(){
        //empty here
    }
    
    void PosixSystem::Sleep(__in const unsigned int iMilliSeconds){
        usleep(iMilliSeconds * 1000);
    }
    
    bool PosixSystem::CreateDirectory(__in const std::string& strDirPath){
        if(mkdir(strDirPath.c_str(), S_IRWXU) == -1){
            return false;
        }
        return true;
    }
    
    bool PosixSystem::DeleteDirectory(__in const std::string& strDirPath){
        if(!NX::System::Instance().FileExist(strDirPath)){
            return true;
        }
        struct stat statbuf;
        if(lstat(strDirPath.c_str(), &statbuf) != 0){
            return false;
        }
        if(S_ISREG(statbuf.st_mode) != 0){
            remove(strDirPath.c_str());
            return true;
        }
        if(S_ISDIR(statbuf.st_mode) == 0){
            return false;
        }
        DIR *dir = opendir(strDirPath.c_str());
        if(dir == NULL){
            return false;
        }
        char file_path[PATH_MAX];
        dirent *dir_info;
        while((dir_info = readdir(dir)) != NULL){
            strcpy(file_path, strDirPath.c_str());
            if(file_path[strDirPath.length() - 1] != '/'){
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
        rmdir(strDirPath.c_str());
        return true;
    }
    
    bool PosixSystem::FileExist(__in const std::string& strFilePath){
        return access(strFilePath.c_str(), 0) == 0;
    }
}
#endif