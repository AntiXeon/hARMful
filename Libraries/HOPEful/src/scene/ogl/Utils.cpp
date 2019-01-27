#include <scene/ogl/Utils.hpp>
#include <Math.hpp>
#include <algorithm>

namespace Hope::GL {

    void GLPerspective(
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

        glFrustum(left, right, bottom, top, zNear, zFar) ;
    }

}
