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
#include "../engine/math/NXQuaternion.h"
#include "../engine/math/NXAlgorithm.h"
#include "../engine/render/NXViewFrustum.h"


using std::cout;
using std::endl;
using std::cin;

int main(){
    {//<quaternion, matrix>
        NX::Quaternion q(1, 3, 2, 4);
        auto y = NX::MatrixToQuaternion(NX::QuaternionToMatrix(q));
        y *= 1.0 / y[0];
    }
    
    {//<euler angle, matrix>
        NX::EulerAngle e(30, 80, 50);
        auto x = NX::MatrixToEulerAngle(NX::EulerAngleToMatrix(e, NX::OBJECT_SPACE_TO_INERTIA_SPACE), NX::OBJECT_SPACE_TO_INERTIA_SPACE);
    }
    
    {//<euler angle, quaternion>
        NX::Quaternion q(1, 2, 3, 4);
        auto y = NX::EulerAngleToQuaternion(NX::QuaternionToEulerAngle(q, NX::OBJECT_SPACE_TO_INERTIA_SPACE), NX::OBJECT_SPACE_TO_INERTIA_SPACE);
        y *= 1.0 / y[0];
    }
    
    {
        auto X = NX::RotateAix<float, 3>(NX::vector<float, 3>(1, 2, 3), NX::DG2RD(60));
        auto Y = NX::Quaternion(NX::DG2RD(30), NX::vector<float, 3>(1, 2, 3));
        NX::vector<float, 3> v(1, 1, 1);
        //Y *= 2;
        Y.Pow(2);
        auto Z = X * v;
        auto W = Y * v;
        auto R = Y.GetRotateMatrix();
        auto RX = R * NX::vector<float, 4>(1, 1, 1, 1);
        auto XX = Y.GetRotateAxis();
        float rd = Y.GetRotateAngle();
        cout << "end" << endl;
    }
    
    {
        NX::EulerAngle e(0, 135, 0), e2(180, 45, 180);
        auto x = NX::EulerAngleToMatrix(e, NX::INERTIA_SPACE_TO_OBJECT_SPACE);
        auto y = NX::EulerAngleToMatrix(e2, NX::INERTIA_SPACE_TO_OBJECT_SPACE);
        cout << "end" << endl;
    }
    
    {
        NX::vector<float, 2> a(1, 22), ax(1, 22);
        auto Y = NX::GetScale(a, ax, 2);
        cout << " end" << endl;
    }
    
    {
        NX::Line a(NX::vector<float, 3>(0, 0, 0), NX::vector<float, 3>(0, 1, 0));
        auto c = a.GetPoint(10);
        auto M = NX::RotateX(NX::DG2RD(90));
        auto b = a.Transform(M);
        cout << " end " << endl;
    }
    
    {
        NX::float2X2 x;
        x[0][0] = 1, x[0][1] = 1;
        x[1][0] = 2, x[1][1] = 2;
        NX::float2 R(3, 8);
        auto RR = NX::SolveEquation(x, R);
        cout << " " << endl;
    }
    
    {//
        NX::Quaternion q1(NX::DG2RD(90), NX::float3(0, 1, 1));
        NX::Quaternion q2(NX::DG2RD(70), NX::float3(1, 1, 2));
        q1.Normalize();
        q2.Normalize();
        std::vector<float> v;
        const int num = 100;
        for(int i = 0; i < num; ++i){
            auto Y = ( 1 - 1.0 * i / num) * q1 + 1.0 * i / num * q2;
            Y.Normalize();
            v.push_back(std::acos(Dot(Y, q1)));
        }
        
        for(int i = 2; i < num; ++i){
            v[i] /=v[1];
        }
        
        cout << "end" << endl;
    }
    
    {
        NX::PerspectCamera camera(NX::float3(0, 0, 0), NX::float3(0, 0, 1), NX::float3(0, 1, 0), 90.0f, 1.0f, 1.0f, 1000.0f);
        auto FV = camera.GetViewFrustumInCameraSpace();
        cout << "end" << endl;
    }
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