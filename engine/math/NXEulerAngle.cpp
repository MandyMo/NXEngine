/*
 *  File:    NXEulerAngle.cpp
 *  author:  张雄
 *  date:    2016_05_27
 *  purpose: 欧拉角操作函数
 */
#include "NXEulerAngle.h"
#include "NXVector.h"
#include "NXMatrix.h"
#include "NXQuaternion.h"
#include "NXAlgorithm.h"

namespace NX {
    EulerAngle::EulerAngle(){
        heading = pitch = bank = 0.0f;
    }
    
    EulerAngle::EulerAngle(const EulerAngle &rhs){
        heading  = rhs.heading;
        pitch    = rhs.pitch;
        bank     = rhs.bank;
    }

    EulerAngle::EulerAngle(const Matrix<float, 3, 3> &rhs, const EulerAngleMode mode):EulerAngle(MatrixToEulerAngle(rhs, mode)){
        
    }

    EulerAngle::EulerAngle(const Matrix<float, 4, 4> &rhs, const EulerAngleMode mode):EulerAngle(MatrixToEulerAngle(rhs, mode)){
        
    }

    EulerAngle::EulerAngle(const float yAxisRotateAngle, const float xAxisRotateAngle, const float zAxisRotateAngle){
        heading = yAxisRotateAngle;
        pitch   = xAxisRotateAngle;
        bank    = zAxisRotateAngle;
    }

    EulerAngle::~EulerAngle(){
        //empty here
    }
    
    EulerAngle& EulerAngle::Normalize(){
        pitch = Wrap(pitch, 360.0f);
        pitch -= 180.0f;
        if(pitch < kfPiOver2){
            to be continue;
        }
        return *this;
    }
    
    const EulerAngle kEulerAngleIndentity(0.0f, 0.0f, 0.0f);
}