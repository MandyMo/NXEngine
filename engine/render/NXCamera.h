/*
 *  File:    NXCamera.h
 *  author:  张雄
 *  date:    2016_04_07
 *  purpose: 定义一组操作摄像机的方法
 */

#pragma once

#include "../math/NXVector.h"
#include "../math/NXMatrix.h"
namespace NX {
    class ViewFrustum;
    
    class MVMatrixController{
    public:
        MVMatrixController(const float3 &Eye, const float3 &Looked, const float3 &Up);
        virtual ~MVMatrixController() = 0;
        
    public:
        virtual MVMatrixController& MoveLeft(const float PosDiff);
        virtual MVMatrixController& MoveRight(const float PosDiff);
        virtual MVMatrixController& MoveFront(const float PosDiff);
        virtual MVMatrixController& MoveBack(const float PosDiff);
        virtual MVMatrixController& MoveDown(const float PosDiff);
        virtual MVMatrixController& MoveUp(const float PosDiff);
        virtual MVMatrixController& MoveByVector(const float3 &vTranslate);
        virtual MVMatrixController& MoveByAxis(const float3 &vDirection, const float Distance);
        
    public:
        virtual MVMatrixController& RotateByFrontBackAxis(const float radian);
        virtual MVMatrixController& RotateByLeftRightAxis(const float radian);
        virtual MVMatrixController& RotateByUpDownAxis(const float radian);
        virtual MVMatrixController& RotateByAxis(const float3 &axis, const float radian);
        virtual MVMatrixController& RotateByAxisAtFixedPosition(const float3 &axis, const float3 &Position, const float radian);

    public:
        float4x4  GetMVMatrix() const;
        float3    GetRightAxis() const;
		float3    GetFrontAxis() const;
		float3    GetUpAxis() const;
		float3    GetEyePosition() const;
		float3    GetEyeDirection() const;

	public:
		MVMatrixController& SetCameraPosition(const NX::float3 &_Pos);

    private:
        void CaculateAxis();
        
    public:
        float3                  m_vRight;
        float3                  m_vUp;
        float3                  m_vFront;
        float3                  m_vEye;
        float3                  m_vLooked;
        float4X4                m_MVMatrix;
    };
    
    class ProjectController{
    public:
        ProjectController();
        virtual ~ProjectController()        = 0;
    public:
        virtual float4x4 GetWatchMatrix()   = 0;
        virtual float4x4 GetProjectMatrix() = 0;
        virtual ViewFrustum GetViewFrustumInCameraSpace()  = 0;
        virtual ViewFrustum GetViewFrustumInWorldSpace()   = 0;
        
    public:
        float4X4         m_ProjectMatrix;
    };
        
    class PerspectCamera: public MVMatrixController, public ProjectController{
    public:
        PerspectCamera(const float3 &Eye, const float3 &Looked, const float3 &Up,
                       const float FovByAngel, const float Ratio, const float Near, const float Far);
        virtual ~PerspectCamera();
        
    public:
        virtual float4x4 GetWatchMatrix();
        virtual float4x4 GetProjectMatrix();
        virtual ViewFrustum GetViewFrustumInCameraSpace();
        virtual ViewFrustum GetViewFrustumInWorldSpace();
        
    private:
        float           m_fFovByAngel;
        float           m_fRatio;
        float           m_fNearPlane;
        float           m_fFarPlane;
    };
    
    class OrthogonalCamera: public MVMatrixController, public ProjectController{
    public:
        OrthogonalCamera(const float3 &Eye, const float3 &Looked, const float3 &Up,
                         const float Width, const float Height, const float Near, const float Far);
        OrthogonalCamera(const float3 &Eye, const float3 &Looked, const float3 &Up,
                         const float Left, const float Right, const float Top, const float Bottom,
                         const float Near, const float Far);
        virtual ~OrthogonalCamera();
        
    public:
        virtual float4x4 GetWatchMatrix();
        virtual float4x4 GetProjectMatrix();
        virtual ViewFrustum GetViewFrustumInCameraSpace();
        virtual ViewFrustum GetViewFrustumInWorldSpace();
        
    private:
        float           m_fLeft;
        float           m_fRight;
        float           m_fTop;
        float           m_fBottom;
        float           m_fNearPlane;
        float           m_fFarPlane;
    };
}

