
#include "NXCamera.h"
#include "../math/NXAlgorithm.h"

NX::MVMatrixController::MVMatrixController(const float3 &Eye, const float3 &Looked, const float3 &Up){
    m_vLooked = Looked;
    m_vEye    = Eye;
    m_vUp     = Up;
    CaculateAxis();
}

void NX::MVMatrixController::CaculateAxis(){
    m_vFront  = m_vLooked - m_vEye;
    m_vRight  = NX::Cross(m_vUp, m_vFront);
    m_vUp     = NX::Cross(m_vFront, m_vRight);
    Normalize(m_vUp);
    Normalize(m_vFront);
    Normalize(m_vRight);
}

NX::MVMatrixController::~MVMatrixController(){
    //empty here just for abstract interface used...
}

void NX::MVMatrixController::MoveLeft(const float PosDiff){
    MoveRight(-PosDiff);
}

void NX::MVMatrixController::MoveRight(const float PosDiff){
    MoveByAxis(m_vRight, PosDiff);
}

void NX::MVMatrixController::MoveFront(const float PosDiff){
    MoveByAxis(m_vFront, PosDiff);
}

void NX::MVMatrixController::MoveBack(const float PosDiff){
    MoveFront(-PosDiff);
}

void NX::MVMatrixController::MoveDown(const float PosDiff){
    MoveUp(-PosDiff);
}

void NX::MVMatrixController::MoveUp(const float PosDiff){
    MoveByAxis(m_vUp, PosDiff);
}

void NX::MVMatrixController::MoveByVector(const float3 &vTranslate){
    m_vEye    += vTranslate;
    m_vLooked += vTranslate;
}

void NX::MVMatrixController::MoveByAxis(const float3 &vDirection, const float Distance){
    if(NXAbs(Distance) < FLOAT_EPSILON){//too small, then skip
        return;
    }
    
    float3 oo = vDirection;
    NX::Normalize(oo);
    oo.Set(oo.x * Distance, oo.y * Distance, oo.z * Distance);
    m_vEye    += oo;
    m_vLooked += oo;
}

void NX::MVMatrixController::RotateByFrontBackAxis(const float radian){
    RotateByAxis(NX::float3(0, 0, 1), radian);
}

void NX::MVMatrixController::RotateByLeftRightAxis(const float radian){
    RotateByAxis(NX::float3(1, 0, 0), radian);
}

void NX::MVMatrixController::RotateByUpDownAxis(const float radian){
    RotateByAxis(NX::float3(0, 1, 0), radian);
}

static inline void Rotate(const NX::float3x3 &TranslateMatrix, NX::float3 &Rotated){
    NX::float3x1 oo = TranslateMatrix * Rotated;
    Rotated.Set(oo[0][0], oo[1][0], oo[2][0]);
}

void NX::MVMatrixController::RotateByAxis(const float3 &axis, const float radian){
    NX::float3x3 RotateMatrix = NX::RotateAix<float, 3, float>(axis, radian);
    Rotate(RotateMatrix, m_vUp);
    m_vLooked -= m_vEye;
    Rotate(RotateMatrix, m_vLooked);
    m_vLooked += m_vEye;
    CaculateAxis();
}

NX::float4x4  NX::MVMatrixController::GetMVMatrix(){
    return NX::LookAt<float>(m_vEye, m_vLooked, m_vUp);
}

NX::PerspectCamera::PerspectCamera(const float3 &Eye, const float3 &Looked, const float3 &Up,
                                   const float FovByAngel, const float Ratio, const float Near, const float Far):MVMatrixController(Eye, Looked, Up){
    m_fFovByAngel   = FovByAngel;
    m_fRatio        = Ratio;
    m_fNearPlane    = Near;
    m_fFarPlane     = Far;
}

NX::PerspectCamera::~PerspectCamera(){
    //empty here
}

NX::float4x4 NX::PerspectCamera::GetWatchMatrix(){
    return NX::Perspective(m_fFovByAngel, m_fRatio, m_fNearPlane, m_fFarPlane) * GetMVMatrix();
}

NX::float4x4 NX::PerspectCamera::GetProjectMatrix(){
    return NX::Perspective<float, 4>(m_fFovByAngel, m_fRatio, m_fNearPlane, m_fFarPlane);
}

NX::OrthogonalCamera::OrthogonalCamera(const float3 &Eye, const float3 &Looked, const float3 &Up,
                                       const float Width, const float Height, const float Near, const float Far):MVMatrixController(Eye, Looked, Up){
    m_fWidth     = Width;
    m_fHeight    = Height;
    m_fNearPlane = Near;
    m_fFarPlane  = Far;
}
NX::OrthogonalCamera::~OrthogonalCamera(){
    
}

NX::float4x4 NX::OrthogonalCamera::GetWatchMatrix(){
    return NX::Orthogonal(m_fWidth, m_fHeight, m_fNearPlane, m_fFarPlane) * GetMVMatrix();
}

NX::float4x4 NX::OrthogonalCamera::GetProjectMatrix(){
    return NX::Orthogonal(m_fWidth, m_fHeight, m_fNearPlane, m_fFarPlane);
}