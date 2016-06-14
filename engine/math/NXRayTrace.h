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
    class Ellipse;
    class Ellipsoid;
    class Cone;
    class Cylinder;
    
    class RayTrace{
    public:
        inline static RayTrace& Instance(){
            static RayTrace SharedObject;
            return SharedObject;
        }
    public:
        float RayIntersect(const NX::Line &ray,     const NX::AABB        &aabb);
        float RayIntersect(const NX::Line &ray,     const NX::Circle      &circle);
        float RayIntersect(const NX::Line &ray,     const NX::Line        &line);
        float RayIntersect(const NX::Line &ray,     const NX::Plane       &plane);
        float RayIntersect(const NX::Line &ray,     const NX::Sphere      &sphere);
        float RayIntersect(const NX::Line &ray,     const NX::Triangle    &triangle);
        float RayIntersect(const NX::Line &ray,     const NX::vector<float, 3> &ptA, const NX::vector<float, 3> &ptB, const NX::vector<float, 3> &ptC);
        float RayIntersect(const NX::Line &ray,     const NX::Ellipse     &ellipse);
        float RayIntersect(const NX::Line &ray,     const NX::Ellipsoid   &ellipsoid);
        float RayIntersect(const NX::Line &ray,     const NX::Cone        &cone);
        float RayIntersect(const NX::Line &ray,     const NX::Cylinder    &cylinder);
    };
}


#endif // !__ZX_NXENGINE_RAYTRACE_H__