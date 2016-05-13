#include <iostream>
#include <memory>
#include "NXShader.h"
#include "NXLog.h"
#include "NXVector.h"
#include "NXMatrix.h"
#include "NXShaderManager.h"
#include "DemoHeader.h"
#include "../engine/common/NXMemory.h"

int main(int argc, const char* argv[]){
    for(int i = 0; i < 1000; ++i){
        NX::float4x4 m;
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 4; ++j){
                m[i][j] = NX::RandFloatInRange(-100, 100);
            }
        }
    
        auto x = NX::Reverse(m);
        auto y = x * m;
        SimplifyMatrix(y);
        bool Ok = true;
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 4; ++j){
                if(i == j && NX::abs(y[i][j] - 1) > NX::FLOAT_EPSILON){
                    Ok = false;
                }
                if(i != j && NX::abs(y[i][j]) > NX::FLOAT_EPSILON){
                    Ok = false;
                }
            }
        }
        
        NX::glb_GetLog().logToConsole("Check Result: %s\n", Ok ? "true" : "false");
    }
    NX::glb_GetLog().logToConsole("begin main");
    std::auto_ptr<NX::Application> app(new MultiViewRender());
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