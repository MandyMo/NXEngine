/*
 *  File:    NXKVFile.h
 *
 *  author:  张雄
 *  date:    2016_08_27
 *  Purpose: 用于定义操作<k,v>数据文件的接口
 */

#pragma once

#include <string>

namespace NX {
    class KVFile{
    public:
        /**
         *  注意，KVFile对象是进程惟一对象，建议使用kv对象的地方使用KVFile::Instance获取对象并使用。
         */
        KVFile(){/*empty here*/}
        virtual ~KVFile(){/*empty here*/}
        static KVFile& Instance();
        
    public:
        virtual bool HasKey(const std::string &key) = 0;
        virtual std::string GetValue(const std::string &key) = 0;
        virtual std::string SetValue(const std::string &key, const std::string &value) = 0;
        virtual std::string DeleteValue(const std::string &key) = 0;
        virtual bool FlushToDisk() = 0;
    };
}