#pragma once

#include "matrix.h"
#include <vector>
#include "object.h"

namespace aline{
    const real Sw = 800;
    const real Sh = 600;
    const real a = Sh/Sw;

    class Frustum{
    public:
        Vec4r near;
        Vec4r far;
        Vec4r right;
        Vec4r left;
        Vec4r bottom;
        Vec4r top;

        Frustum(){}
        Frustum(real near_dist, real far_dist);

        Object clip(const Object & obj);

        aline::Vertex intersectPlan(Vec4r plan, Vec3r & v0 , Vec3r & v1);

        aline::Vertex intersectPoint(Vec4r plan, Vec3r & v0 , Vec3r & v1); 
        
        int signed_distance(Vec4r  plan, const Vec3r & v);

        Object clipPlane(Vec4r plan, Object obj);
    };

}