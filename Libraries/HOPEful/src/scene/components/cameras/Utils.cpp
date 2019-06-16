#include <scene/components/cameras/Utils.hpp>
#include <Math.hpp>
#include <cassert>
#include <algorithm>
#include <limits>

using namespace Hope ;

void Hope::Perspective(
    Mind::Matrix4x4f& result,
    const double fovY,
    const double aspect,
    const double zNear,
    const double zFar
) {
    assert(abs(aspect - std::numeric_limits<float>::epsilon()) > 0.f) ;

    const float TanHalfFovY = std::tan(fovY / 2.f) ;
    const double FarMinusNear = zFar - zNear ;
    result.clear() ;

    result[0][0] = 1.f / (aspect * TanHalfFovY) ;
	result[1][1] = 1.f / (TanHalfFovY) ;
	result[2][2] = -(zFar + zNear) / FarMinusNear ;
    result[3][2] = -1.f ;
    result[2][3] = -(2.f * zFar * zNear) / FarMinusNear ;
}

void Hope::Orthographic(
    Mind::Matrix4x4f& result,
    const double left,
    const double right,
    const double bottom,
    const double top,
    const double zNear,
    const double zFar
) {
    const float RightMinusLeft = right - left ;
    const float TopMinusBottom = top - bottom ;
    const float FarMinusNear = zFar - zNear ;

    result[0][0] = +2.f / RightMinusLeft ;
    result[1][1] = +2.f / TopMinusBottom ;
    result[2][2] = -2.f / FarMinusNear ;
    result[0][3] = -((right + left) / RightMinusLeft) ;
    result[1][3] = -((top + bottom) / TopMinusBottom) ;
    result[2][3] = -((zFar + zNear) / FarMinusNear) ;
    result[3][3] = +1.f ;
}
