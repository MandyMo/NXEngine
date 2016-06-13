/*
 *  File:    NXRayTrace.h
 *  author:  张雄
 *  date:    2016_06_05
 *  purpose: basic ray trace function
 */

#ifndef __ZX_NXENGINE_RAYTRACE_H__
#define __ZX_NXENGINE_RAYTRACE_H__

namespace NX {
    class AABB;
    class Circle;
    class Line;
    class Plane;
    class Sphere;
    class Triangle;
    
    class RayTrace{
    public:
        inline static RayTrace& Instance(){
            static RayTrace SharedObject;
            return SharedObject;
        }
    public:
        float RTAABB(const NX::Line &ray,     const NX::AABB &aabb);
        float RTCircle(const NX::Line &ray,   const NX::Circle &circle);
        float RTLine(const NX::Line &ray,     const NX::Line &line);
        float RTPlane(const NX::Line &ray,    const NX::Plane &plane);
        float RTSphere(const NX::Line &ray,   const NX::Sphere &sphere);
        float RTTriangle(const NX::Line &ray, const NX::Triangle &triangle);
        float RTTriangle(const NX::Line &ray, const NX::vector<float, 3> &ptA, const NX::vector<float, 3> &ptB, const NX::vector<float, 3> &ptC);
    };
}


#endif // !__ZX_NXENGINE_RAYTRACE_H__