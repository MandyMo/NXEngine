#include <iostream>
#include <memory>
#include "NXShader.h"
#include "NXLog.h"
#include "NXVector.h"
#include "NXMatrix.h"
#include "NXShaderManager.h"
#include "DemoHeader.h"
#include "../engine/common/NXMemory.h"
#include "../engine/math/NXPrimitive.h"

using std::cout;
using std::endl;
using std::cin;

int main(){
    NX::vector<float, 3> a(1,2,3), b(4,5,6), c;
    c = NX::GetNormalize(a);
}


//int main(int argc, const char* argv[]){
////    NX::Plane pA(NX::float4(1, 2, 3, 4));
////    NX::Plane pB(NX::float4(2, 3, 4, 5));
////    auto X = pA.Intersect(pB);
//    NX::Matrix<double, 50, 50> M;
//    for(int i = 0; i< M.GetRowCount(); ++i){
//        for(int j = 0; j < M.GetColCount(); ++j){
//            M[i][j] = NX::RandFloatInRange(-100, 100);
//        }
//    }
//    auto X = Reverse(M);
//    auto Y = M * X;
//    SimplifyMatrix(Y);
//    bool bOK = true;
//    for(int i = 0; i < M.GetRowCount(); ++i){
//        for(int j = 0; j < M.GetColCount(); ++j){
//            if(i == j && NX::NXAbs(Y[i][j] - 1) > NX::Epsilon<double>::m_Epsilon){
//                bOK = false;
//            }
//            if(i != j && NX::NXAbs(Y[i][j]) > NX::Epsilon<double>::m_Epsilon){
//                bOK= false;
//            }
//        }
//    }
//    NX::glb_GetLog().logToConsole("Reverse: %s", bOK ? "true" : "false");
//    std::auto_ptr<NX::Application> app(new MultiViewRender());
//    if(!app->Init(argv, argc, 800, 800)){
//        std::cout << "failed init application..." << std::endl;
//        return 1;
//    }
//    NX::Mutex *pMutex = NX::Mutex::Create();
//    pMutex->Enter();
//    pMutex->Leave();
//    delete pMutex;
//    NX::glb_GetLog().logToConsole("begin application");
//    app->Run();
//    NX::glb_GetLog().logToConsole("end main");
//    return 0;
//}