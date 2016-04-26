#include <iostream>
#include <memory>
#include "NXShader.h"
#include "NXLog.h"
#include "NXVector.h"
#include "NXMatrix.h"
#include "NXShaderManager.h"
#include "DemoHeader.h"

int main(int argc, const char* argv[]){
    NX::glb_GetLog().logToConsole("begin main");
    std::auto_ptr<NX::Application> app(new GSDemo());
    if(!app->Init(argv, argc, 800, 800)){
        std::cout << "failed init application..." << std::endl;
        return 1;
    }
    NX::Mutex *pMutex = NX::Mutex::Create();
    pMutex->Enter();
    NX::glb_GetLog().logToConsole("begin application");
    pMutex->Enter();
    app->Run();
    NX::glb_GetLog().logToConsole("end main");
    return 0;
}