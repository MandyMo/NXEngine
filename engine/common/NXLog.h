/*
 *  File:    Log.h
 *  Author:  张雄
 *  Date:    2016_02_22
 *  purpose: 日志文件，用于记录引擎中相关事件
 */

#ifndef __ZX_NXENGINE_LOG_H__
#define __ZX_NXENGINE_LOG_H__
#include "NXCore.h"

namespace NX{
    class Mutex;
    class Log{
    public:
        /*
         *  <函数功能>
         *  构造log对象
         *
         *  <输入参数>
         *  strLogFilePath：  日志文件名，可选参数
         */
        Log(__in const std::string& strLogFilePath = "");
        virtual ~Log();
    public:
        /*
         *  <函数功能>
         *  重定向日志输出，在调用此函数时，系统会自动关闭之前的日志文件
         *
         *  <输入参数>
         *  strNewLogFilePath:  重定向的日志文件路径
         */
        void RedirectLogFile(__in const std::string& strNewLogFilePath);
    public:
        /*
         *  <函数功能>
         *  将日志输出到日志文件
         *
         *  <输入参数>
         *  szForMat:  格式串
         *  ...     :  变长参数列表
         */
        virtual void log(__in const char *szFormat, ...);
        
        /*
         *  <函数功能>
         *  将日志输出到字符串
         *
         *  <输入参数>
         *  strDst:  日志信息输出的字符串
         *  szForMat:  格式串
         *  ...     :  变长参数列表
         */
        virtual void log(__out std::string& strDst, __in const char *szFormat, ...);
        
        /*
         *  <函数功能>
         *  将日志输出到控制台
         *
         *  <输入参数>
         *  szForMat:  格式串
         *  ...     :  变长参数列表
         */
        virtual void logToConsole(__in const char *szFormat, ...);
    private:
        /*
         *  <函数功能>
         *  获取当前系统时间的描述信息字符串如"[2016-02-22 11:26:11]"
         *
         *  <返回值>
         *  当前系统本地时间的信息描述字符串
         */
        std::string GetTimeDescription();
    private:
        std::string    m_strLogFilePath;
        std::ofstream  m_outStream;
    };
    
    Log& glb_GetLog();
}


#endif