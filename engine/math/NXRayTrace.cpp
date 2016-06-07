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
#include "NXRayTrace.h"
#include "NXMath.h"
#include "NXComplex.h"

float NX::RayTrace::RTAABB(const NX::Line &ray,     const NX::AABB &aabb){
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

float NX::RayTrace::RTCircle(const NX::Line &ray,   const NX::Circle &circle){
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

float NX::RayTrace::RTLine(const NX::Line &ray, const NX::Line &line){
    return 0;
}

float NX::RayTrace::RTPlane(const NX::Line &ray,    const NX::Plane &plane){
    const float nv = NX::Dot(plane.GetNormal(), ray.GetDirection());
    if(EqualZero(nv)){
        return -kf1;
    }
    return -(plane.GetDistFromOriginal() + NX::Dot(plane.GetNormal(), ray.GetBeginPosition())) / nv;
}

float NX::RayTrace::RTSphere(const NX::Line &ray,   const NX::Sphere &sphere){
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

float NX::RayTrace::RTTriangle(const NX::Line &ray, const NX::Triangle &triangle){
    return 0;
}