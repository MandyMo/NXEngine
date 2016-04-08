#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "NXApplication.h"
#include "../math/NXMath.h"
#include "../common/NXLog.h"

static NX::Application* g_pThis  = NULL;
static GLFWwindow*        g_window = NULL;

static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mousebutton_callback(GLFWwindow*,int,int,int);
static void windowposition_callback(GLFWwindow*,int,int);
static void windowsize_callback(GLFWwindow*,int,int);
static void cursorposition_callback(GLFWwindow*,double,double);
NX::Application::Application(){
    g_pThis   = NULL;
    g_window  = NULL;
}

NX::Application::~Application(){
    g_pThis    = NULL;
    g_window   = NULL;
}

bool NX::Application::Init(const char* vCmdLine[], const int iCmdCount, const int iWidth, const int iHeight){
    g_pThis = this;
    NX::InitNXMath();
    if (!glfwInit()) {
        fprintf(stderr, "Failed initialize GLFW.");
        exit(EXIT_FAILURE);
        return false;
    }
    {
        glfwSetErrorCallback(error_callback);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    }
    {
        GLFWwindow* window = glfwCreateWindow(iWidth, iHeight, "OpenGL", NULL, NULL);
        if(!window) {
            std::fprintf(stderr, "Failed to create GLFW window.");
            glfwTerminate();
            exit(EXIT_FAILURE);
            return false;
        }
        g_window = window;
        glfwMakeContextCurrent(window);
    }
    
    {//call backs
        glfwSetKeyCallback(g_window, key_callback);
        glfwSetMouseButtonCallback(g_window, mousebutton_callback);
        glfwSetWindowPosCallback(g_window, windowposition_callback);
        glfwSetWindowSizeCallback(g_window, windowsize_callback);
        glfwSetCursorPosCallback(g_window, cursorposition_callback);
    }
    glb_GetLog().logToConsole("OpenGL version supported by this platform (%s)", glGetString(GL_VERSION));
    glb_GetLog().log("OpenGL version supported by this platform (%s)", glGetString(GL_VENDOR));
    glewExperimental = GL_TRUE;
    glewInit();
    return true;
}

void NX::Application::Tick(const double DeltaTime){
    static double iTotalTime = 0;
    iTotalTime += DeltaTime;
    static char Title[32];
    static int iFrameCount = 0;
    ++iFrameCount;
    if(iTotalTime >= 1.0){
        sprintf(Title, "fps: %.2f", (iFrameCount / iTotalTime));
        iFrameCount = 0;
        iTotalTime  = 0;
        glfwSetWindowTitle(g_window, Title);
    }
}

void NX::Application::Render(){
    static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
    glClearBufferfv(GL_COLOR, 0, green);
}

void NX::Application::OnError(int error, const char* description){
    std::fputs(description, stderr);
}

void NX::Application::OnKeyEvent(int key, int scancode, int action, int mods){
    if(g_window == NULL){
        return;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(g_window, GL_TRUE);
    }
}


void NX::Application::OnMouseButtonEvent(int btn,int action,int mods){
    glb_GetLog().logToConsole("void NX::Application::OnMouseButtonEvent(int btn,int action,int mods)");
}


void NX::Application::OnWindowPositionEvent(int xByScreen,int yByScreen){
    glb_GetLog().logToConsole("void NX::Application::OnWindowPositionEvent(int xByScreen,int yByScreen)");
}


void NX::Application::OnWindowSizeEvent(int iNewWidth, int iNewHeight){
    glb_GetLog().logToConsole("void NX::Application::OnWindowSizeEvent(int iNewWidth, int iNewHeight)");
}


void NX::Application::OnCursorPositionEvent(double xByScreen, double yByScreen){
    glb_GetLog().logToConsole("void NX::Application::OnCursorPositionEvent(double xByScreen, double yByScreen)");
}

void NX::Application::Run(){
    static double PreTime = glfwGetTime();
    static double NowTime = glfwGetTime();
    while(!glfwWindowShouldClose(g_window)){
        NowTime = glfwGetTime();
        Tick(NowTime - PreTime);
        Render();
        glFlush();
        glfwSwapBuffers(g_window);
        glfwPollEvents();
        PreTime = NowTime;
    }
}

static void error_callback(int error, const char* description) {
    if(!g_pThis){
        return;
    }
    g_pThis->OnError(error, description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(!g_window){
        return;
    }
    g_pThis->OnKeyEvent(key, scancode, action, mods);
}

void mousebutton_callback(GLFWwindow* window, int btn,int action,int mods){
    if(!g_window){
        return;
    }
    g_pThis->OnMouseButtonEvent(btn, action, mods);
}

void windowposition_callback(GLFWwindow* window, int xByScreen,int yByScreen){
    if(!g_window){
        return;
    }
    g_pThis->OnWindowPositionEvent(xByScreen, yByScreen);
}

void windowsize_callback(GLFWwindow*, int iNewWidth, int iNewHeight){
    if(!g_window){
        return;
    }
    g_pThis->OnWindowSizeEvent(iNewWidth, iNewHeight);
}

void cursorposition_callback(GLFWwindow*, double xByScreen, double yByScreen){
    if(!g_window){
        return;
    }
    g_pThis->OnCursorPositionEvent(xByScreen, yByScreen);
}