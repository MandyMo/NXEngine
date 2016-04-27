#include <iostream>
#include <memory>
#include "NXShader.h"
#include "NXLog.h"
#include "NXVector.h"
#include "NXMatrix.h"
#include "NXShaderManager.h"
#include "DemoHeader.h"

int main(int argc, const char* argv[]){
    
    
    NX::float3X3 m;
    m.SetRow(0, NX::float3(1, 2, 3));
    m.SetRow(1, NX::float3(2, 3, 4));
    m.SetRow(2, NX::float3(3, 4, 6));
    
    auto XX = Reverse(m);
    
    NX::glb_GetLog().logToConsole("begin main");
    std::auto_ptr<NX::Application> app(new GSDemo());
    if(!app->Init(argv, argc, 800, 800)){
        std::cout << "failed init application..." << std::endl;
        return 1;
    }
    NX::Mutex *pMutex = NX::Mutex::Create();
    pMutex->Enter();
    pMutex->Leave();
    delete pMutex;
    NX::glb_GetLog().logToConsole("begin application");
    app->Run();
    NX::glb_GetLog().logToConsole("end main");
    return 0;
}