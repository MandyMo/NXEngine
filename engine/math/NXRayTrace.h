/*
 *  File:    NXRayTrace.h
 *  author:  张雄
 *  date:    2016_06_05
 *  purpose: basic ray trace function
 */

#ifndef __ZX_NXENGINE_RAYTRACE_H__
#define __ZX_NXENGINE_RAYTRACE_H__

namespace NX {
    class RayTrace{
    public:
        static RayTrace& Instance(){
            static RayTrace &SharedObject;
            return SharedObject;
        }
    public:
        std::pair<bool, float> RTSphere(const NX::Line &ray,  const NX::Sphere &sphere);
        std::pair<bool, float> RTPlane(const NX::Line &ray,   const NX::Plane &plane);
        std::pair<bool, float> RTAABB(const NX::Line &ray,    const NX::AABB &aabb);
    };
}


#endif // !__ZX_NXENGINE_RAYTRACE_H__