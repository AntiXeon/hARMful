#include <scene/ogl/Utils.hpp>
#include <Math.hpp>
#include <algorithm>

namespace Hope::GL {

    void GLPerspective(
        Mind::Matrix4x4f& result,
        const GLdouble fovY,
        const GLdouble aspect,
        const GLdouble zNear,
        const GLdouble zFar
    ) {
        GLdouble usedNear = zNear ;
        GLdouble usedFar = zFar ;

        if (usedNear < 0.f) {
            usedNear = -usedNear ;
        }

        if (usedFar < 0.f) {
            usedFar = -usedFar ;
        }

        // Specify the coordinates for the left and right vertical clipping planes.
        GLdouble left, right ;
        // Specify the coordinates for the bottom and top horizontal clipping planes.
        GLdouble top, bottom ;

        // top = tan( (fovY / 2) / 180 * pi ) * zNear;
        top = tan(fovY / 360.f * Mind::Math::Pi) * zNear ;
        bottom = -top ;
        right = top * aspect ;
        left = -right ;

        GLdouble rightMinusLeft = right - left ;
        GLdouble topMinusBottom = top - bottom ;
        GLdouble farMinusNear = zFar - zNear ;

        // Set the matrix as glFrustum() would do.
        result[0][0] = (2.f * zNear) / rightMinusLeft ;
        result[0][1] = 0.f ;
        result[0][2] = (right + left) / rightMinusLeft ;
        result[0][3] = 0.f ;
        result[1][0] = 0.f ;
        result[1][1] = (2.f * zNear) / topMinusBottom ;
        result[1][2] = (top + bottom) / topMinusBottom ;
        result[1][3] = 0.f ;
        result[2][0] = 0.f ;
        result[2][1] = 0.f ;
        result[2][2] = (zFar + zNear) / farMinusNear ;
        result[2][3] = 0.f ;
        result[3][0] = 0.f ;
        result[3][1] = 0.f ;
        result[3][2] = -1.f ;
        result[3][3] = (2.f * zFar * zNear) / farMinusNear ;
    }
}
