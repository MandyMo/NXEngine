/*
 *  File:    Application.h
 *  author:  张雄
 *  date:    2016_02_21
 *  purpose: 用于定义OpenGL应用程序接口，注意，此接口使用了glfw和glew，需要先安装此工具库，
 *  在mac上可使用macports安装，具体操作请google macports，Linux系统使用apt-get，
 *  windows系统请直接下载库和头文件（自己编译估计有点坑）
 */


#ifndef __ZX_NXENGINE_APPLICATION_H__
#define __ZX_NXENGINE_APPLICATION_H__

#include "../common/NXcore.h"

namespace NX {
    class Application{
    public:
        Application();
        virtual ~Application();
    public:
        /*
         *  <函数功能>
         *  使用glfw和glew库初始化OpenGL环境，注意，此函数应该是构造函数之后调用的第一个类函数，
         *  在调用此函数并且成功之前，不得调用其它OpenGL函数。其它类如果继承此类，则需要首先调用
         *  此类的Init函数，再执行子类的Init代码。
         *
         *  <函数参数>
         *  vCmdLine:   命令行字符串数组，与C的main函数类似
         *  iCmdCount:  命令行字符串个数
         *  iWidth:     OpenGL使用的窗口的宽（以像素为单位）
         *  iHeight:    OpenGL使用的窗口的高（以像素为单位）
         
         *  <返回值>
         *  true:  初始化成功，在init之后，即可调用其它OpenGL函数
         *  false: 初始化失败
         */
        virtual bool Init(__in const char* vCmdLine[], __in const int iCmdCount,
                          __in const int iWidth, __in const int iHeight);
        /*
         *  <函数功能>
         *  游戏中的Tick函数。
         *
         *  <函数参数>
         *  iTime:   时间，以秒为单位
         */
        virtual void Tick(const double DeltaTime);
        
        /*
         *  <函数功能>
         *  游戏中的Render函数，主要完成游戏中的渲染
         *
         */
        virtual void Render();
        
        /*
         *  <函数功能>
         *  游戏中的主循环，其它类若要继承此类，最好不要重载Run函数，以免不必要的麻烦
         *
         */
        virtual void Run();
        
    public:
        
        /*
         *  <函数功能>
         *  错误处理函数
         *
         *  <函数参数>
         *  与glfw中错误处理回调函数的参数完全相同。
         */
        virtual void OnError(int error, const char* description);
        
        /*
         *  <函数功能>
         *  错误处理函数
         *
         *  <函数参数>
         *  与glfw中键盘事件回调函数的参数意义完全相同
         */
        virtual void OnKeyEvent(int key, int scancode, int action, int mods);
    };
}


#endif