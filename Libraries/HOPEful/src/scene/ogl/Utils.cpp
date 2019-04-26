#include <scene/ogl/Utils.hpp>
#include <Math.hpp>
#include <cassert>
#include <algorithm>
#include <limits>

namespace Hope::GL {

    void GLPerspective(
        Mind::Matrix4x4f& result,
        const GLdouble fovY,
        const GLdouble aspect,
        const GLdouble zNear,
        const GLdouble zFar
    ) {
        assert(abs(aspect - std::numeric_limits<float>::epsilon()) > 0.f) ;

        const float TanHalfFovY = std::tan(fovY / 2.f) ;
        const GLdouble FarMinusNear = zFar - zNear ;
        result.clear() ;

        result[0][0] = 1.f / (aspect * TanHalfFovY) ;
		result[1][1] = 1.f / (TanHalfFovY) ;
		result[2][2] = -(zFar + zNear) / FarMinusNear ;
        result[3][2] = -1.f ;
        result[2][3] = -(2.f * zFar * zNear) / FarMinusNear ;
    }
}
