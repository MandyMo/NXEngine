/*
 *  File:    NXCamera.cpp
 *  author:  张雄
 *  date:    2016_04_07
 *  purpose: 实现操作摄像机的方法
 */


#include "NXViewFrustum.h"
#include "NXCamera.h"
#include "../math/NXAlgorithm.h"
#include "../math/NXPrimitive.h"

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
    m_MVMatrix = NX::GetLookAtMatrix(m_vEye, m_vLooked, m_vUp);
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
    m_MVMatrix = NX::GetLookAtMatrix(m_vEye, m_vLooked, m_vUp);
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
    m_MVMatrix = NX::GetLookAtMatrix(m_vEye, m_vLooked, m_vUp);
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
    NX::float3x3 RotateMatrix = NX::GetMatrixRotateByAix<float, 3, float>(axis, radian);
    Rotate(RotateMatrix, m_vUp);
    m_vLooked -= m_vEye;
    Rotate(RotateMatrix, m_vLooked);
    m_vLooked += m_vEye;
    CaculateAxis();
}

void NX::MVMatrixController::RotateByAxisAtFixedPosition(const float3 &axis, const float3 &Position, const float radian){
    NX::float3X3 RotateMatrix = NX::GetMatrixRotateByAix<float, 3, float>(axis, radian);
    Rotate(RotateMatrix, m_vUp);
    m_vLooked -= Position;
    m_vEye    -= Position;
    Rotate(RotateMatrix, m_vLooked);
    Rotate(RotateMatrix, m_vEye);
    m_vEye    += Position;
    m_vLooked += Position;
    CaculateAxis();
}

NX::float3 NX::MVMatrixController::GetRightAxis() const {
	return m_vRight;
}

NX::float3 NX::MVMatrixController::GetFrontAxis() const {
	return m_vFront;
}

NX::float3 NX::MVMatrixController::GetUpAxis() const {
	return m_vUp;
}

NX::float3  NX::MVMatrixController::GetEyePosition() const {
	return m_vEye;
}

NX::float3  NX::MVMatrixController::GetEyeDirection() const {
	return m_vLooked - m_vEye;
}

NX::float4x4  NX::MVMatrixController::GetMVMatrix() const{
    return m_MVMatrix;
}

NX::PerspectCamera::PerspectCamera(const float3 &Eye, const float3 &Looked, const float3 &Up,
                                   const float FovByAngel, const float Ratio, const float Near, const float Far):MVMatrixController(Eye, Looked, Up){
    m_fFovByAngel   = FovByAngel;
    m_fRatio        = Ratio;
    m_fNearPlane    = Near;
    m_fFarPlane     = Far;
    m_ProjectMatrix = NX::GetPerspectiveMatrix(m_fFovByAngel, m_fRatio, m_fNearPlane, m_fFarPlane);
}

NX::PerspectCamera::~PerspectCamera(){
    //empty here
}

NX::float4x4 NX::PerspectCamera::GetWatchMatrix(){
    return GetProjectMatrix() * GetMVMatrix();
}

NX::float4x4 NX::PerspectCamera::GetProjectMatrix(){
    return m_ProjectMatrix;
}

NX::ViewFrustum NX::PerspectCamera::GetViewFrustumInCameraSpace(){
    NX::float4x4 P = GetProjectMatrix();
    NX::Plane Left (P.GetRow(0) + P.GetRow(3)), Right(P.GetRow(3)  - P.GetRow(0));
    NX::Plane Top  (P.GetRow(3) - P.GetRow(1)), Bottom(P.GetRow(3) + P.GetRow(1));
    NX::Plane Front(P.GetRow(3) - P.GetRow(2)), Back(P.GetRow(2));
    return NX::ViewFrustum(NX::Normalize(Front), NX::Normalize(Back), NX::Normalize(Left), NX::Normalize(Right), NX::Normalize(Top), NX::Normalize(Bottom));
}

NX::ViewFrustum NX::PerspectCamera::GetViewFrustumInWorldSpace(){
    NX::float4X4 MVP = GetProjectMatrix() * GetMVMatrix();
    NX::Plane Left (MVP.GetRow(0) + MVP.GetRow(3)), Right(MVP.GetRow(3)  - MVP.GetRow(0));
    NX::Plane Top  (MVP.GetRow(3) - MVP.GetRow(1)), Bottom(MVP.GetRow(3) + MVP.GetRow(1));
    NX::Plane Front(MVP.GetRow(3) - MVP.GetRow(2)), Back(MVP.GetRow(2));
    return NX::ViewFrustum(NX::Normalize(Front), NX::Normalize(Back), NX::Normalize(Left), NX::Normalize(Right), NX::Normalize(Top), NX::Normalize(Bottom));
}

NX::OrthogonalCamera::OrthogonalCamera(const float3 &Eye, const float3 &Looked, const float3 &Up,
                                       const float Width, const float Height, const float Near, const float Far):MVMatrixController(Eye, Looked, Up){
    m_fLeft    = -Width * 0.5f;
    m_fRight   = -m_fLeft;
    m_fTop     = Height * 0.5f;
    m_fBottom  = -m_fTop;
    m_fNearPlane    = Near;
    m_fFarPlane     = Far;
    m_ProjectMatrix = NX::GetOrthogonalMatrix(m_fLeft, m_fRight, m_fTop, m_fBottom, m_fNearPlane, m_fFarPlane);
}

NX::OrthogonalCamera::OrthogonalCamera(const float3 &Eye, const float3 &Looked, const float3 &Up,
                                       const float Left, const float Right, const float Top, const float Bottom,
                                       const float Near, const float Far):NX::MVMatrixController(Eye, Looked, Up){
    m_fLeft = Left, m_fRight = Right, m_fTop = Top, m_fBottom = Bottom, m_fNearPlane = Near, m_fFarPlane = Far;
    m_ProjectMatrix = NX::GetOrthogonalMatrix(m_fLeft, m_fRight, m_fTop, m_fBottom, m_fNearPlane, m_fFarPlane);
}

NX::ViewFrustum NX::OrthogonalCamera::GetViewFrustumInCameraSpace(){
    NX::float4x4 P = GetProjectMatrix();
    NX::Plane Left(P.GetRow(0) + P.GetRow(3)), Right(P.GetRow(3)  - P.GetRow(0));
    NX::Plane Top (P.GetRow(3) - P.GetRow(1)), Bottom(P.GetRow(3) + P.GetRow(1));
    NX::Plane Front(P.GetRow(3)- P.GetRow(2)), Back(P.GetRow(2));
    return NX::ViewFrustum(Front, Back, Left, Right, Top, Bottom);
}

NX::ViewFrustum NX::OrthogonalCamera::GetViewFrustumInWorldSpace(){
    NX::float4X4 MVP = GetProjectMatrix() * GetMVMatrix();
    NX::Plane Left(MVP.GetRow(0) + MVP.GetRow(3)), Right(MVP.GetRow(3)  - MVP.GetRow(0));
    NX::Plane Top (MVP.GetRow(3) - MVP.GetRow(1)), Bottom(MVP.GetRow(3) + MVP.GetRow(1));
    NX::Plane Front(MVP.GetRow(3)- MVP.GetRow(2)), Back(MVP.GetRow(2));
    return NX::ViewFrustum(Front, Back, Left, Right, Top, Bottom);
}

NX::OrthogonalCamera::~OrthogonalCamera(){
    //empty here
}

NX::float4x4 NX::OrthogonalCamera::GetWatchMatrix(){
    return GetProjectMatrix() * GetMVMatrix();
}

NX::float4x4 NX::OrthogonalCamera::GetProjectMatrix(){
    return m_ProjectMatrix;
}