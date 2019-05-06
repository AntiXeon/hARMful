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

    void GLOrthographic(
        Mind::Matrix4x4f& result,
        const GLdouble left,
        const GLdouble right,
        const GLdouble bottom,
        const GLdouble top,
        const GLdouble zNear,
        const GLdouble zFar
    ) {
        const float RightMinusLeft = right - left ;
        const float TopMinusBottom = top - bottom ;
        const float FarMinusNear = zFar - zNear ;

        result[0][0] = 2.f / RightMinusLeft ;
        result[1][1] = -2.f / TopMinusBottom ;
        result[2][2] = -2.f / FarMinusNear ;
        result[0][3] = -(right + left) / RightMinusLeft ;
        result[1][3] = (top + bottom) / TopMinusBottom ;
        result[2][3] = -(zFar + zNear) / FarMinusNear ;
        result[3][3] = 1.f ;
    }
}
