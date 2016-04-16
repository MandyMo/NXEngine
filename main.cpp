#include <iostream>
#include <memory>
#include "NXShader.h"
#include "NXLog.h"
#include "NXVector.h"
#include "NXMatrix.h"
#include "DemoHeader.h"


int main(int argc, const char* argv[]){
    
    NX::glb_GetLog().logToConsole("begin main");
    std::auto_ptr<NX::Application> app(new Bricks());
    if(!app->Init(argv, argc, 800, 800)){
        std::cout << "failed init application..." << std::endl;
        return 1;
    }
    NX::glb_GetLog().logToConsole("begin application");
    app->Run();
    NX::glb_GetLog().logToConsole("end main");
    return 0;
}