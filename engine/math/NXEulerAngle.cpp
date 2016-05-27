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
}