/*
 *  File:    NXSystem.cpp
 *
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

bool NX::System::DeleteFile(__in const std::string& strFilePath){
    return !remove(strFilePath.c_str());
}

bool NX::System::CreateDirectory(__in const std::string& strDirPath){
    NXAssert(0 && "bool NX::System::CreateDirectory(__in const std::string strDirPath)");
    return false;
}