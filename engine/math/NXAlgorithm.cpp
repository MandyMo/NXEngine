/*
 *  File:    NXAlgorithm.cpp
 *  author:  张雄
 *  date:    2016_05_27
 *  purpose: 一些与matrix，vector，quaternion, Eulera angle相关的算法
 */

#include "NXAlgorithm.h"
namespace NX{
    EulerAngle MatrixToEulerAngle(const Matrix<float, 3, 3> &rhs, const EulerAngleMode mode){
        EulerAngle result;
        float sp;
        float NearlyOne = 1.0f - Epsilon<float>::m_Epsilon;
        if(mode == OBJECT_SPACE_TO_INERTIA_SPACE){//rhs为从物体坐标系到惯性坐标系的转换矩阵
            sp = -rhs[1][2];
            if(sp <= -NearlyOne){
                result.pitch = -kfPiOver2;
                sp = -sp;
            }else if(sp >= NearlyOne){
                result.pitch = kfPiOver2;
            }else{
                result.pitch = SafeASin(sp);
            }
            if(sp >= NearlyOne){//锁
                result.bank    = 0.0f;
                result.heading = std::atan2(-rhs[2][0], rhs[0][0]);
            }else{
                result.heading = std::atan2(rhs[0][2], rhs[2][2]);
                result.bank    = std::atan2(rhs[1][0], rhs[1][1]);
            }
        }else if(mode == INERTIA_SPACE_TO_OBJECT_SPACE){//rhs为从惯性坐标系到物体坐标系的转换矩阵
            sp = -rhs[2][1];
            if(sp <= -NearlyOne){
                result.pitch = -kfPiOver2;
                sp = -sp;
            }else if(sp >= NearlyOne){
                result.pitch = kfPiOver2;
            }else{
                result.pitch = SafeASin(sp);
            }
            if(sp >= NearlyOne){
                result.heading = std::atan2(-rhs[1][2], rhs[0][0]);
                result.bank    = 0.0f;
            }else{
                result.heading = std::atan2(rhs[2][0], rhs[2][2]);
                result.bank    = std::atan2(rhs[0][1], rhs[1][1]);
            }
        }else{
            //impossible
        }
        result.heading = RD2DG(result.heading);
        result.bank    = RD2DG(result.bank);
        result.pitch   = RD2DG(result.pitch);
        return result;
    }
    
    EulerAngle MatrixToEulerAngle(const Matrix<float, 4, 4> &rhs, const EulerAngleMode mode){
        return MatrixToEulerAngle(Matrix<float, 3, 3>(rhs), mode);
    }
    
    Matrix<float, 4, 4> EulerAngleToMatrix(const EulerAngle &lhs, const EulerAngleMode mode){
        Matrix<float, 4, 4> result;
        result[3][3] = 1.0f;
        if(mode == OBJECT_SPACE_TO_INERTIA_SPACE){
            result = RotateY(DG2RD(lhs.heading)) * RotateX(DG2RD(lhs.pitch)) * RotateZ(DG2RD(lhs.bank));
        }else if(mode == INERTIA_SPACE_TO_OBJECT_SPACE){
            result = RotateZ(-DG2RD(lhs.bank)) * RotateX(-DG2RD(lhs.pitch)) * RotateY(-DG2RD(lhs.heading));
        }
        return result;
    }
    Matrix<float, 4, 4> QuaternionToMatrix(const Quaternion &lhs){
        return Quaternion(lhs).Normalize().GetRotateMatrix();
    }
    
    Quaternion MatrixToQuaternion(const Matrix<float, 4, 4> &lhs){
        return MatrixToQuaternion(Matrix<float, 3, 3>(lhs));
    }
    
    Quaternion MatrixToQuaternion(const Matrix<float, 3, 3> &lhs){
        Quaternion result;
        float MW = lhs[0][0] + lhs[1][1] + lhs[2][2];
        float MX = lhs[0][0] - lhs[1][1] - lhs[2][2];
        float MY = lhs[1][1] - lhs[0][0] - lhs[2][2];
        float MZ = lhs[2][2] - lhs[0][0] - lhs[1][1];
        int iPivotIndex = 0;
        float MM = MW;
        if(MX > MM){
            iPivotIndex = 1;
            MM = MX;
        }
        if(MY > MM){
            iPivotIndex = 2;
            MM = MY;
        }
        if(MZ > MM){
            iPivotIndex = 3;
            MM = MZ;
        }
        float PivotValue = std::sqrt(MM + 1) * 0.5;
        float Mult = 0.25f / PivotValue;
        switch(iPivotIndex){
            case 0:
                result.w = PivotValue;
                result.x = (lhs[2][1] - lhs[1][2]) * Mult;
                result.y = (lhs[0][2] - lhs[2][0]) * Mult;
                result.z = (lhs[1][0] - lhs[0][1]) * Mult;
                break;
            case 1:
                result.x = PivotValue;
                result.w = (lhs[2][1] - lhs[1][2]) * Mult;
                result.y = (lhs[0][1] * lhs[1][0]) * Mult;
                result.z = (lhs[0][2] + lhs[2][0]) * Mult;
                break;
            case 2:
                result.y = PivotValue;
                result.w = (lhs[0][2] - lhs[2][0]) * Mult;
                result.x = (lhs[0][1] + lhs[1][0]) * Mult;
                result.z = (lhs[1][2] + lhs[2][1]) * Mult;
                break;
            case 3:
                result.z = PivotValue;
                result.w = (lhs[1][0] - lhs[0][1]) * Mult;
                result.x = (lhs[0][2] + lhs[2][0]) * Mult;
                result.y = (lhs[1][2] + lhs[2][1]) * Mult;
                break;
            default:
                break;
        }
        return result;
    }
    
    EulerAngle QuaternionToEulerAngle(const Quaternion &lhs, const EulerAngleMode mode){
        return MatrixToEulerAngle(QuaternionToMatrix(lhs), mode);
    }
    
    Quaternion EulerAngleToQuaternion(const EulerAngle &lhs, const EulerAngleMode mode){
        return MatrixToQuaternion(EulerAngleToMatrix(lhs, mode));
    }
}