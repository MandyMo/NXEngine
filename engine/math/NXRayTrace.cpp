/*
 *  File:    NXRayTrace.cpp
 *  author:  张雄
 *  date:    2016_06_05
 *  purpose: basic ray trace function
 */

#include "NXAABB.h"
#include "NXCircle.h"
#include "NXLine.h"
#include "NXPlane.h"
#include "NXSphere.h"
#include "NXTriangle.h"
#include "NXEllipse.h"
#include "NXEllipsoid.h"
#include "NXCone.h"
#include "NXCylinder.h"
#include "NXRayTrace.h"
#include "NXMath.h"
#include "NXComplex.h"


float NX::RayTrace::RayIntersect(const NX::Line &ray,     const NX::AABB &aabb){
    const NX::vector<float, 3> V  = ray.GetDirection();
    const NX::vector<float, 3> S  = ray.GetBeginPosition();
    const NX::vector<float, 3> LB = aabb.GetMinPoint();
    const NX::vector<float, 3> RT = aabb.GetMaxPoint();
    float T = -kf1, t;
    {//x plane test
        if(!EqualZero(V.x)){
            {//left
                t = (LB.x - S.x) / V.x;
                if(t >= 0.0f && aabb.InAABB(ray.GetPoint(t))){
                    if(T <  kf0){
                        T = t;
                    }else{
                        T = NX::NXMin(T, t);
                    }
                }
            }
            
            {//right
                t = (RT.x - S.x) / V.x;
                if(t >= 0.0f && aabb.InAABB(ray.GetPoint(t))){
                    if(T <  kf0){
                        T = t;
                    }else{
                        T = NX::NXMin(T, t);
                    }
                }
            }
        }
    }
    
    {//y plane test
        if(!EqualZero(V.y)){
            {//top
                t = (RT.y - S.y) / V.y;
                if(t >= 0.0f && aabb.InAABB(ray.GetPoint(t))){
                    if(T <  kf0){
                        T = t;
                    }else{
                        T = NX::NXMin(T, t);
                    }
                }
            }
            
            {//bottom
                t = (LB.y - S.y) / V.y;
                if(t >= 0.0f && aabb.InAABB(ray.GetPoint(t))){
                    if(T <  kf0){
                        T = t;
                    }else{
                        T = NX::NXMin(T, t);
                    }
                }
            }
        }
    }
    
    {//z plane test
        if(!EqualZero(V.z)){
            {//front
                t = (RT.z - S.z) / V.z;
                if(t >= 0.0f && aabb.InAABB(ray.GetPoint(t))){
                    if(T <  kf0){
                        T = t;
                    }else{
                        T = NX::NXMin(T, t);
                    }
                }
            }
            
            {//back
                t = (LB.z - S.z) / V.z;
                if(t > 0.0f && aabb.InAABB(ray.GetPoint(t))){
                    if(T <  kf0){
                        T = t;
                    }else{
                        T = NX::NXMin(T, t);
                    }
                }
            }
        }
    }
    return T;
}

float NX::RayTrace::RayIntersect(const NX::Line &ray,   const NX::Circle &circle){
    const float nv = NX::Dot(circle.GetNormal(), ray.GetDirection());
    if(EqualZero(nv)){
        return -kf1;
    }
    
    const float t = NX::Dot(circle.GetNormal(), circle.GetCenter() - ray.GetBeginPosition()) / nv;
    if(t >= kf0 && circle.InCircle(ray.GetPoint(t))){
        return t;
    }
    return -kf1;
}

float NX::RayTrace::RayIntersect(const NX::Line &ray, const NX::Line &line){
    float V12   = NX::Dot(ray.GetDirection(), line.GetDirection());
    float Delta = V12 * V12 - ::NX::LengthSquare(ray.GetDirection()) * ::NX::LengthSquare(line.GetDirection());
    if(NX::NXAbs(Delta) < Epsilon<float>::m_Epsilon){//line parallel, so it's easy
        return -kf1;
    }else{
        vector<float, 3> v = line.GetBeginPosition() - ray.GetBeginPosition();
        float a = NX::Dot(v, ray.GetDirection()), b = Dot(v, line.GetDirection());
        float V11 = NX::LengthSquare(ray.GetDirection());
        float V22 = NX::LengthSquare(line.GetDirection());
        float t1 = (-V22 * a + V12 * b) / Delta;
        float t2 = (-V12 * a + V11 * b) / Delta;
        if(NX::Length(ray.GetPoint(t1) - line.GetPoint(t2)) > Epsilon<float>::m_Epsilon){
            return -kf1;
        }
        return t1;
    }
    return 0;
}

float NX::RayTrace::RayIntersect(const NX::Line &ray,    const NX::Plane &plane){
    const float nv = NX::Dot(plane.GetNormal(), ray.GetDirection());
    if(EqualZero(nv)){
        return -kf1;
    }
    return -(plane.GetDistFromOriginal() + NX::Dot(plane.GetNormal(), ray.GetBeginPosition())) / nv;
}

float NX::RayTrace::RayIntersect(const NX::Line &ray,   const NX::Sphere &sphere){
    const vector<float, 3> sc = ray.GetBeginPosition() - sphere.GetCenter();
    const vector<float, 3> v  = ray.GetDirection();
    const float r = sphere.GetRadius();
    const float Mult = kf1 / NX::LengthSquare(v);
    const float a = NX::kf2 * NX::Dot(sc, v) * Mult;
    const float b = (NX::LengthSquare(sc) -  r * r) * Mult;
    const float Delta = a * a - 4.0f * b;
    if(Delta < kf0){
        return -kf1;
    }else if(NX::EqualZero(Delta)){
        return a <= kf0 ? -a * kf1Over2 : kf1;
    }else{
        const float s = std::sqrt(Delta);
        const float x = (-a + s) * kf1Over2;
        const float y = (-a - s) * kf1Over2;
        return y >= kf0 ? y : (x >= kf0 ? x : -kf1);
    }
}

float NX::RayTrace::RayIntersect(const NX::Line &ray, const NX::Triangle &triangle){
    return RayIntersect(ray, triangle.GetPointA(), triangle.GetPointB(), triangle.GetPointC());
}

float NX::RayTrace::RayIntersect(const NX::Line &ray, const NX::vector<float, 3> &ptA, const NX::vector<float, 3> &ptB, const NX::vector<float, 3> &ptC){
    const NX::vector<float, 3> e1 = ptB - ptA;
    const NX::vector<float, 3> e2 = ptC - ptA;
    const NX::vector<float, 3> d  = NX::GetNegative(ray.GetDirection());
    const NX::vector<float, 3> s  = ray.GetBeginPosition() - ptA;
    const NX::vector<float, 3> n  = NX::Cross(e1, e2);
    float Mult = NX::Dot(d, n);
    float result;
    do{
        if(EqualZero(Mult)){
            result = -kf1;
            break;
        }
        Mult = kf1 / Mult;
        float u, v, t;
        t = Mult * NX::Dot(s, n);
        if(t < kf0){
            result = -kf1;
            break;
        }
        result = t;
        const NX::vector<float, 3> q  = NX::Cross(d, s);
        u = Mult * NX::Dot(q, e2);
        if(u > kf1 || u < kf0){
            result =  -kf1;
            break;
        }
        
        v = -Mult * NX::Dot(q, e1);
        if(v > kf1 || v < kf0 || u + v > kf1){
            result = -kf1;
        }
    }while(0);
    return result;
}

float NX::RayTrace::RayIntersect(const NX::Line &ray,     const NX::Ellipse     &ellipse){
    const float a = NX::Dot(ray.GetDirection(), ellipse.GetNormal());
    const float b = NX::Dot(ellipse.GetNormal(), ellipse.GetCenter() - ray.GetBeginPosition());
    if(NX::EqualZero(a)){
        return -kf1;
    }
    const float t = b / a;
    if(t > kf0  && ellipse.InEllipse(ray.GetPoint(t))){
        return t;
    }
    return -kf1;
}

float NX::RayTrace::RayIntersect(const NX::Line &ray,     const NX::Ellipsoid   &ellipsoid){
    const NX::vector<float, 3> v   = ray.GetDirection();
    const NX::vector<float, 3> cs  = ray.GetBeginPosition() - ellipsoid.GetCenter();
    const float rpx = kf1 / (ellipsoid.GetAxisXLength() * ellipsoid.GetAxisXLength());
    const float rpy = kf1 / (ellipsoid.GetAxisYLength() * ellipsoid.GetAxisYLength());
    const float rpz = kf1 / (ellipsoid.GetAxisZLength() * ellipsoid.GetAxisZLength());
    
    const float vx  = NX::Dot(v,  ellipsoid.GetAxisX());
    const float vy  = NX::Dot(v,  ellipsoid.GetAxisY());
    const float vz  = NX::Dot(v,  ellipsoid.GetAxisZ());
    const float csx = NX::Dot(cs, ellipsoid.GetAxisX());
    const float csy = NX::Dot(cs, ellipsoid.GetAxisY());
    const float csz = NX::Dot(cs, ellipsoid.GetAxisZ());
    
    const float a = vx * vx * rpx + vy * vy * rpy * vz * vz * rpz;
    const float b = vx * csx * kf2 * rpx + vy * csy * kf2 * rpy + vz * csz * kf2 * rpz;
    const float c = csx * csx * rpx + csy * csy * rpy + csz * csz * rpz - kf1;
    
    if(NX::EqualZero(a)){
        return -kf1;
    }
    const std::vector<float> SOV = NX::SolveEquationWithOnlyRealResult(a, b, c);
    if(SOV.empty()){
        return -kf1;
    }
    int idx = 0;
    for(int i = 1; i < SOV.size(); ++i){
        if(SOV[i] > kf0 && SOV[i] < SOV[idx]){
            idx = i;
        }
    }
    
    return SOV[idx] > kf0 ? SOV[idx] : -kf1;
}

float NX::RayTrace::RayIntersect(const NX::Line &ray,     const NX::Cone        &cone){
    return -kf1;
}

float NX::RayTrace::RayIntersect(const NX::Line &ray,     const NX::Cylinder    &cylinder){
    //to be continue
    //    const NX::vector<float, 3> v  = ray.GetDirection();
    //    const NX::vector<float, 3> cs = ray.GetBeginPosition() - ellipse.GetCenter();
    //    const float rpl  = kf1 / (ellipse.GetLongSemiAxisLength()  * ellipse.GetLongSemiAxisLength());
    //    const float rps  = kf1 / (ellipse.GetShortSemiAxisLength() * ellipse.GetShortSemiAxisLength());
    //    const float vl   = NX::Dot(v,  ellipse.GetLongSemiAxis());
    //    const float vs   = NX::Dot(v,  ellipse.GetShortSemiAxis());
    //    const float csl  = NX::Dot(cs, ellipse.GetLongSemiAxis());
    //    const float css  = NX::Dot(cs, ellipse.GetShortSemiAxis());
    //    const float a = vl * vl * rpl + vs * vs * rps;
    //    const float b = vl * csl * kf2 * rpl + vs * css * kf2 * rps;
    //    const float c = csl * csl * rpl + css * css * rps - kf1;
    //    if(NX::EqualZero(a)){
    //        return -kf1;
    //    }
    //    const std::vector<float> SOV = NX::SolveEquationWithOnlyRealResult(a, b, c);
    //    if(SOV.empty()){
    //        return -kf1;
    //    }
    //    int idx = 0;
    //    for(int i = 1; i < SOV.size(); ++i){
    //        if(SOV[i] > kf0 && SOV[i] < SOV[idx]){
    //            idx = i;
    //        }
    //    }
    //
    //    return SOV[idx] > kf0 ? SOV[idx] : -kf1;
    return -kf1;

    return -kf1;
}
