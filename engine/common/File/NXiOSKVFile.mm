/*
 *  File:    NXiOSKVFile.mm
 *
 *  author:  张雄
 *  date:    2016_08_27
 *  Purpose: 定义iOS操作<k,v>数据文件的接口, iOS的实现使用iOS内置 nsuserdefaults
 */

#include "NXKVFile.h"

#if defined(__APPLE__)

#import <Foundation/Foundation.h>

namespace NX{
    class IOSKVFile: public NX::KVFile{
    public:
        IOSKVFile();
        virtual ~IOSKVFile();
        
    public:
        virtual bool HasKey(const std::string &key);
        virtual std::string GetValue(const std::string &key);
        virtual std::string SetValue(const std::string &key, const std::string &value);
        virtual std::string DeleteValue(const std::string &key);
        virtual bool FlushToDisk();
    };
}

NX::IOSKVFile::IOSKVFile(){
    /*empty here*/
}

NX::IOSKVFile::~IOSKVFile(){
    /*empty here*/
}

bool NX::IOSKVFile::HasKey(const std::string &key){
    NSUserDefaults *userDef = [NSUserDefaults standardUserDefaults];
    if(userDef == nil){
        return false;
    }
    return [userDef objectForKey:[NSString stringWithUTF8String: key.c_str()]] != nil;
}

std::string NX::IOSKVFile::GetValue(const std::string &key){
    NSUserDefaults *userDef = [NSUserDefaults standardUserDefaults];
    if(userDef == nil){
        return "";
    }
    NSString * OCKey   = [NSString stringWithUTF8String: key.c_str()];
    NSString * OCValue = [userDef objectForKey:OCKey];
    return OCValue != nil ? [OCValue UTF8String] : "";
}

std::string NX::IOSKVFile::SetValue(const std::string &key, const std::string &value){
    NSUserDefaults *userDef = [NSUserDefaults standardUserDefaults];
    if(userDef == nil){
        return "";
    }
    NSString * OCKey   = [NSString stringWithUTF8String: key.c_str()];
    NSString * OCValue = [NSString stringWithUTF8String: value.c_str()];
    NSString * OCOldValue = [userDef objectForKey: OCKey];
    std::string Oldvalue(OCOldValue ? [OCOldValue UTF8String] : "");
    [userDef setObject:OCValue forKey:OCKey];
    FlushToDisk();
    return Oldvalue;
}

std::string NX::IOSKVFile::DeleteValue(const std::string &key){
    if(!HasKey(key)){
        return "";
    }
    NSUserDefaults *userDef = [NSUserDefaults standardUserDefaults];
    if(userDef == nil){
        return "";
    }
    NSString * OCKey   = [NSString stringWithUTF8String: key.c_str()];
    NSString * OCOldValue = [userDef objectForKey: OCKey];
    std::string Oldvalue(OCOldValue ? [OCOldValue UTF8String] : "");
    [userDef removeObjectForKey: OCKey];
    FlushToDisk();
    return Oldvalue;
}

bool NX::IOSKVFile::FlushToDisk(){
    NSUserDefaults *userDef = [NSUserDefaults standardUserDefaults];
    if(userDef == nil){
        return false;
    }
    return [userDef synchronize];
}

NX::KVFile& NX::KVFile::Instance(){
    static NX::IOSKVFile SharedObject;
    return SharedObject;
}

#endif