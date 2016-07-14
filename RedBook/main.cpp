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
#include "../engine/math/NXComplex.h"
#include "../engine/math/NXLine.h"
#include "../engine/math/NXPlane.h"
#include "../engine/math/NXSphere.h"
#include "../engine/math/NXCircle.h"
#include "../engine/math/NXTriangle.h"
#include "../engine/math/NXRayTrace.h"
#include "../engine/math/NXAABB.h"
#include "../engine/math/NXNumeric.h"
#include "../engine/math/NXEllipse.h"
#include "../engine/math/NXCylinder.h"
#include "../engine/math/NXCone.h"
#include "../engine/common/NXUtility.h"
#include "../engine/math/NXEllipsoid.h"
#include "../engine/System/NXSystem.h"
using std::cout;
using std::endl;
using std::cin;

int xxxmain(){
    {
        NXAssert(0);
    }
    {//cartan formula
        auto X = NX::SolveEquation(-NX::kf1, 2.5f, -7.0 / 8, 1.0 / 16);
        cout << "end" << endl;
    }
    
    {//std::vector<float> GetEigenvalueOfSymmetricMatrix(const NX::Matrix<float, 3, 3> &M);
        NX::Matrix<float, 3, 3> M;
        M[0][0] = 1.5;
        M[0][1] = M[1][0] = 0.5;
        M[0][2] = M[2][0] = 0.75;
        M[1][1] = 0.5;
        M[1][2] = M[2][1] = 0.25;
        M[2][2] = 0.5;
        auto X = NX::GetEigenValueOfSymmetricMatrix(M);
        cout << "end" << endl;
    }
    {//TR & RT
        auto T = NX::GetTranslated(1, 2, 3);
        auto R = NX::GetMatrixRotateByX(NX::DG2RD(30));
        auto X = T * R;
        auto Y = R * T;
        
        cout << "end" << endl;
    }
    
    {
        const float w = std::sqrt(0.0370370485f);
        cout << w << endl;;
        auto Solv = NX::SolveEquation(1, -3, 3, -1);
        
        cout << "emd" << endl;
    }
    NX::RayTrace &RT = NX::RayTrace::Instance();
    
    srand(time(NULL));
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
        auto X = NX::GetMatrixRotateByAix<float, 3>(NX::vector<float, 3>(1, 2, 3), NX::DG2RD(60));
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
        auto Y = NX::GetScaledByDirection(a, ax, 2);
        cout << " end" << endl;
    }
    
    {
        NX::Line a(NX::vector<float, 3>(0, 0, 0), NX::vector<float, 3>(0, 1, 0));
        auto c = a.GetPoint(10);
        auto M = NX::GetMatrixRotateByX(NX::DG2RD(90));
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
        NX::PerspectCamera camera(NX::float3(0, 0, 100), NX::float3(0, 0, 1000), NX::float3(0, 1, 0), 90.0f, 1.0f, 1.0f, 1000.0f);
        auto FV = camera.GetViewFrustumInWorldSpace();
        cout << "end" << endl;
    }
    
    {
        NX::float3 pA = NX::float3(1, 1, 1), pB(2, 2, 5), pC(7, 8, 9);
        NX::Circle c(pA, pB, pC);
        auto M = ::NX::GetMatrixRotateByAix<float, 4, float>(NX::float3(2, 2, 4), NX::DG2RD(90.f));
        {
            auto X = M * NX::float4(1, 1, 1, 1);
            pA.Set(X[0][0], X[1][0], X[2][0]);
        }
        {
            auto X = M * NX::float4(2, 2, 5, 1);
            pB.Set(X[0][0], X[1][0], X[2][0]);
        }
        {
            auto X = M * NX::float4(7, 8, 9, 1);
            pC.Set(X[0][0], X[1][0], X[2][0]);
        }
        
        NX::Circle cc(pA, pB, pC);
        
        c.Transform(M);
        cout << "end" << endl;
    }
    
    {
#define SCALE 3
        NX::Matrix<float, SCALE, SCALE> m;
        for(int i = 0; i < SCALE; ++i){
            for(int j = 0; j < SCALE; ++j){
                m[i][j] = NX::RandFloatInRange(-100, 100);
            }
        }
        auto RM = NX::GetReverse(m);
        auto I  = RM * m;
        NX::SimplifyMatrix(I);
        cout << "end " << endl;
    }
    
    {
        NX::Plane p(NX::float3(1, 2, 0), NX::float3(2, 0, -1), NX::float3(3, -2, -1));
        cout << "end" << endl;
    }
    
    {
        NX::OrthogonalCamera camera(NX::float3(0, 0, 1), NX::float3(0, 0, 1000), NX::float3(0, 1, 0), -500, 500, -500, 500, 1, 1000);
        auto fv = camera.GetViewFrustumInCameraSpace();
        cout << "end" << endl;
        cout << "hello" << endl;
    }
    
    {
        NX::float3 v[4];
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 3; ++j){
                v[i][j] = NX::RandFloatInRange(-100, 100);
            }
        }
        NX::Sphere s(v[0], v[1], v[2], v[3]);
        cout << "end" << endl;
    }
    
    {
        NX::Complex ca(1, 1), cb(3, 4);
        auto t = ca * cb;
        auto a = ca / cb;
        auto b = ca + cb;
        auto c = ca - cb;
        auto e = ca.GetReverse();
        auto f = ca.GetConjugate();
        auto g = ca + 2;
        auto h = ca - 2;
        auto i = ca * 2;
        auto j = ca / 2;
        auto k = 2 + ca;
        auto l = 2 - ca;
        auto m = 2 * ca;
        auto n = 2 / ca;
        
        cout << " end " << endl;
    }
    
    {
        float x = NX::NXQuickKSquare(-0.001, 100000000000001, 0.0000000001);
        float y = std::pow(0.001, 1.0 / 100000000000000);
        cout << "end" << endl;
    }
    
    {
        auto Solv = NX::SolveEquation(2, -2, 2);
        cout <<"end" << endl;
    }
    
    {
        auto Solv = NX::SolveEquation(1, -1, -2, -2, 4);
        
        cout <<"end" << endl;
    }
    
    {
        NX::float3 a(1, 1, 1), b(200, 3, 4), c(4, 5, 6);
        NX::Circle cc(a, b, c);
        auto n = NX::GetNormalized(NX::Cross(b - a, c - a));
        auto ll = cc.GetRadius() * cc.GetRadius();
        auto aa = NX::Length(a - cc.GetCenter());
        auto bb = NX::Length(b - cc.GetCenter());
        auto dd = NX::Length(c - cc.GetCenter());
        
        auto ti = NX::Triangle(a, b, c);
        
        auto oc = ti.GetGetCircumCircle();
        auto ic = ti.GetInscribedCircle();
        
        auto bar = a * 0.3 + b * 0.7 + c * 0.0;
        auto sov = ti.GetBaryCentricCoord(bar);
        cout << "end" << endl;
    }
    
    {//ray aabb
        NX::RayTrace &RT = NX::RayTrace::Instance();
        NX::AABB aabb(NX::float3(1, 1, 1), NX::float3(10, 100, 100));
        NX::Line ray(NX::float3(-1, -3, -5), NX::float3(1, 1, 0.5));
        auto t = RT.RayIntersect(ray, aabb);
        
        cout <<"end" << endl;
    }
    
    {//ray circlr
        NX::RayTrace &RT = NX::RayTrace::Instance();
        NX::float3 a(1, 1, 1);
        NX::float3 b(2, 3, 4);
        NX::float3 c(7, 8, 9);
        NX::Circle cc(a, b, c);
        NX::Line ray(NX::float3(0, 1, 1), (a + b + c) / NX::kf2);
        
        float t = RT.RayIntersect(ray, cc);
        NX::float3 pt = ray.GetPoint(t);
        auto sov = NX::Triangle(a, b, c).GetBaryCentricCoord(pt);
        auto np = sov.x * a + sov.y * b + sov.z * c;
        cout <<"end" << endl;
    }
    
    {//ray plane
        NX::RayTrace &RT = NX::RayTrace::Instance();
        NX::float3 a(1, 1, 1);
        NX::float3 b(2, 3, 4);
        NX::float3 c(7, 8, 9);
        NX::Plane cc(a, b, c);
        NX::Line ray(NX::float3(0, 1, 1), (a + b + c) / NX::kf2);
        
        float t = RT.RayIntersect(ray, cc);
        NX::float3 pt = ray.GetPoint(t);
        auto sov = NX::Triangle(a, b, c).GetBaryCentricCoord(pt);
        auto np = sov.x * a + sov.y * b + sov.z * c;
        cout <<"end" << endl;
    }
    
    {//ray sphere
        NX::RayTrace &RT = NX::RayTrace::Instance();
        NX::float3 a(1, 1, 1);
        NX::float3 b(2, 3, 4);
        NX::float3 c(7, 8, 9);
        NX::Plane cc(a, b, c);
        NX::Line ray(NX::float3(0, 1, 1), (a + b + c) / NX::kf2);
        NX::Sphere sphere(NX::float3(0, 0, 0), 0.770080023);
        
        float l = ray.Distance(sphere.GetCenter());
        
        float t = RT.RayIntersect(ray, sphere);
        
        auto pt = ray.GetPoint(-0.12790697813034058);
        
        auto ss = NX::Length(pt - sphere.GetCenter());
        
        cout << "end" << endl;
    }
    
    {//ray triangle
        NX::RayTrace &RT = NX::RayTrace::Instance();
        NX::float3 a(1, 1, 1);
        NX::float3 b(2, 3, 4);
        NX::float3 c(7, 8, 9);
        NX::Triangle cc (a, b, c);
        
        NX::Line ray(NX::float3(0, 1, 1), (a + b + c) / NX::kf2);
        
        auto t = RT.RayIntersect(ray, cc);
        
        auto p = ray.GetPoint(t);
        
        auto np =  0.4 * b  + 0.6 * c;
        auto npp = cc.GetPointByBaryCentricCoord(0, 0.4, 0.6);
        cout << "end" << endl;
    }
    
    {//ray line
        
    }
    
    {//ellipse
        NX::Ellipse ec(2, 1);
        auto M = NX::GetTranslated<float>(1, 2, 3) * NX::GetMatrixRotateByY(NX::DG2RD(45)) * NX::GetTranslated(100.f, 200.f, 300.f) * NX::GetMatrixRotateByX(NX::DG2RD(25));
        NX::vector<float, 3> pt(std::sqrt(3), 0, 0.5);
        ec.Transform(M);
        NX::TransformPoint(pt, M);
        bool b = ec.InEllipse(pt);
        cout << "end" << endl;
    }
    
    {
        auto x = NX::MakePair(1, 2), y = NX::MakePair(1, 2);
        
        cout << (x == y) << endl;
        
        auto xt = NX::MakePair(1, 2, 3), yt = NX::MakePair(1, 2, 3);
        
        cout << (xt == yt) << endl;
        
        auto xq = NX::MakePair(1, 2, 3, 4), yq = NX::MakePair(0, 2, 3, 4);
        
        cout << (xq == yq) << endl;
        
        cout << "end" << endl;
    }
    
    {//test cone
        NX::Cone c(2, 1, 4);
        auto M = NX::GetTranslated<float>(100, 200, 300) * NX::GetMatrixRotateByX(NX::DG2RD(20)) * NX::GetMatrixRotateByY(NX::DG2RD(15)) * NX::GetMatrixRotateByZ(NX::DG2RD(40));
        auto pt = NX::float3(std::sqrt(3) / 2, 2.000005,  0.5 / 2);
        c.Transform(M);
        NX::TransformPoint(pt, M);
        bool b = c.OnCone(pt);
        cout << "end" << endl;
    }
    
    {//ray ellipse
        NX::Ellipse ec(4, 2);
        NX::Line ray(NX::float3(1, 1, 1), NX::float3(1, -3, 2));
        const float t = RT.RayIntersect(ray, ec);
        const NX::float3 pt = ray.GetPoint(t);
        
        auto M = NX::GetTranslated<float>(100, 200, 300) * NX::GetMatrixRotateByX(NX::DG2RD(20)) * NX::GetMatrixRotateByY(NX::DG2RD(15)) * NX::GetMatrixRotateByZ(NX::DG2RD(40)) *NX::GetTranslated<float>(80, 60, 310);
        
        ec.Transform(M);
        ray.Transform(M);
        
        const float at = RT.RayIntersect(ray, ec);
        
        bool ai = ec.InEllipse(ray.GetPoint(at));
        
        cout << "end" << endl;
    }
    
    {//ray ellipsoid
        NX::Ellipsoid ec(5, 4, 3);
        NX::Line ray(NX::float3(0, 100, 0), NX::float3(1, -10, 1));
        const float t = RT.RayIntersect(ray, ec);
        const NX::float3 pt = ray.GetPoint(t);
        bool ai = ec.OnEllipsoid(pt);
        
        auto M = NX::GetTranslated<float>(100, 200, 300) * NX::GetMatrixRotateByX(NX::DG2RD(20)) * NX::GetMatrixRotateByY(NX::DG2RD(15)) * NX::GetMatrixRotateByZ(NX::DG2RD(40)) *NX::GetTranslated<float>(80, 60, 310);
        
        ec.Transform(M);
        ray.Transform(M);
        
        const float at = RT.RayIntersect(ray, ec);
        
        ai = ec.OnEllipsoid(ray.GetPoint(at));
        
        cout << "end" << endl;
        
    }
    
    {//ray cylinder
        NX::Cylinder ec(5, 4, 10);
        NX::Line ray(NX::float3(10, 3, 10), NX::float3(1, 5, 1));
        const float t = RT.RayIntersect(ray, ec);
        const NX::float3 pt = ray.GetPoint(t);
        bool ai = ec.OnCylinder(pt);
        
        auto M = NX::GetTranslated<float>(100, 200, 300) * NX::GetMatrixRotateByX(NX::DG2RD(20)) * NX::GetMatrixRotateByY(NX::DG2RD(15)) * NX::GetMatrixRotateByZ(NX::DG2RD(40)) *NX::GetTranslated<float>(80, 60, 310);
        
        ec.Transform(M);
        ray.Transform(M);
        
        const float at = RT.RayIntersect(ray, ec);
        
        ai = ec.OnCylinder(ray.GetPoint(at));
        
        cout << "end" << endl;
    }
    
    {//ray cone
        NX::Cone ec(5, 4, 10);
        NX::Line ray(NX::float3(3, 1, 3), NX::float3(3, 5, 3));
        const float t = RT.RayIntersect(ray, ec);
        const NX::float3 pt = ray.GetPoint(t);
        bool ai = ec.OnCone(pt);
        
        auto M = NX::GetTranslated<float>(100, 200, 300) * NX::GetMatrixRotateByX(NX::DG2RD(20)) * NX::GetMatrixRotateByY(NX::DG2RD(15)) * NX::GetMatrixRotateByZ(NX::DG2RD(40)) *NX::GetTranslated<float>(80, 60, 310);
        
        ec.Transform(M);
        ray.Transform(M);
        
        const float at = RT.RayIntersect(ray, ec);
        
        ai = ec.OnCone(ray.GetPoint(at));
        
        cout << "end" << endl;
    }
    return 1;
}

template<int iScale>
NX::Matrix<float, iScale, iScale> GetDSPMatrix(const NX::vector<int, iScale> &vdsp);

int main(int argc, const char* argv[]){
    
    NX::InitNXMath();
    
    {
#define N 10
        NX::Matrix<float, N, N> m;
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                m[i][j] = NX::RandFloatInRange(-100, 100);
            }
        }

        auto Pre = m;
        auto x = NX::GetLUPDecomposed(m);
        auto P = GetDSPMatrix(x.first);
        auto L = x.second;
        auto U = x.third;
        auto Now = P * Pre;
        auto LU = L * U;
        auto Dif = Now - LU;
        NX::SimplifyMatrix(Dif);
        cout << "end" << endl;
    }
    
    
    std::auto_ptr<NX::Application> app(new Bricks());
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


template<int iScale>
NX::Matrix<float, iScale, iScale> GetDSPMatrix(const NX::vector<int, iScale> &vdsp){
    NX::Matrix<float, iScale, iScale> dsp;
    for(int i = 0; i < iScale; ++i){
        dsp[i][vdsp[i]] = NX::kf1;
    }
    return dsp;
}



