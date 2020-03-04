#include <scene/components/cameras/CameraUtils.hpp>
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

    const double TanHalfFovY = std::tan(fovY / 2.f) ;
    const double FarMinusNear = zFar - zNear ;
    result.clear() ;

    result[0][0] = static_cast<float>(1.f / aspect * TanHalfFovY) ;
	result[1][1] = static_cast<float>(1.f / TanHalfFovY) ;
	result[2][2] = static_cast<float>(-(zFar + zNear) / FarMinusNear) ;
    result[3][2] = static_cast<float>(-1.f) ;
    result[2][3] = static_cast<float>(-(2.f * zFar * zNear) / FarMinusNear) ;
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
    const double RightMinusLeft = right - left ;
    const double TopMinusBottom = top - bottom ;
    const double FarMinusNear = zFar - zNear ;

    result[0][0] = static_cast<float>(+2.f / RightMinusLeft) ;
    result[1][1] = static_cast<float>(+2.f / TopMinusBottom) ;
    result[2][2] = static_cast<float>(-2.f / FarMinusNear) ;
    result[0][3] = static_cast<float>(-((right + left) / RightMinusLeft)) ;
    result[1][3] = static_cast<float>(-((top + bottom) / TopMinusBottom)) ;
    result[2][3] = static_cast<float>(-((zFar + zNear) / FarMinusNear)) ;
    result[3][3] = static_cast<float>(+1.f) ;
}
