/*
 *  File:    NXEulerAngle.h
 *  author:  张雄
 *  date:    2016_05_27
 *  purpose: 欧拉角操作函数
 */

#ifndef __ZX_NXENGINE_EULER_ANGLE_H__
#define __ZX_NXENGINE_EULER_ANGLE_H__

namespace NX {
    template<typename T, int Scale> class vector;
    template<typename T, int Row, int Col> class Matrix;
    class Quaternion;
    enum EulerAngleMode{
        INERTIA_SPACE_TO_OBJECT_SPACE,
        OBJECT_SPACE_TO_INERTIA_SPACE,
    };
    
    class EulerAngle{
    public:
        EulerAngle();
        EulerAngle(const EulerAngle &rhs);
        EulerAngle(const Matrix<float, 3, 3> &rhs, const EulerAngleMode mode);
        EulerAngle(const Matrix<float, 4, 4> &rhs, const EulerAngleMode mode);
        EulerAngle(const float yAxisRotateAngle, const float xAxisRotateAngle, const float zAxisRotateAngle);
        ~EulerAngle();
    public:
        EulerAngle& Normalize();
        EulerAngle GetNormalized() const;
        
    public:
        EulerAngle& FromObjectToWorldMatrix(const Matrix<float, 3, 3> &matrix);
        EulerAngle& FromObjectToWorldMatrix(const Matrix<float, 4, 4> &matrix);
        EulerAngle& FromWorldToObjectMatrix(const Matrix<float, 3, 3> &matrix);
        EulerAngle& FromWorldToObjectMatrix(const Matrix<float, 4, 4> &matrix);
        EulerAngle& FromMatrix(const Matrix<float, 3, 3> &matrix, const EulerAngleMode mode);
        EulerAngle& FromMatrix(const Matrix<float, 4, 4> &matrix, const EulerAngleMode mode);
        Matrix<float, 4, 4> ToMatrix(const EulerAngleMode mode);
        Quaternion          ToQuaternion(const EulerAngleMode mode);
        EulerAngle& FromObjectToWorldQuaternion(const Quaternion &q);
        EulerAngle& FromWorldToObjectQuaternion(const Quaternion &q);
        EulerAngle& FromQuaternion(const Quaternion &q, const EulerAngleMode mode);

    public:
        /**
         *  (heading, pitch, bank) = (yaw, pitch, roll) = (y, x, z) rotate angles
         */
        struct{
            union{
                float heading;
                float yaw;
            };
            float pitch;
            union{
                float bank;
                float roll;
            };
        };
    };
    extern const EulerAngle kEulerAngleIndentity;
}

#endif