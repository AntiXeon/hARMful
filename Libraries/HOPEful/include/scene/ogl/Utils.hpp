#ifndef __HOPE__GL_UTILS__
#define __HOPE__GL_UTILS__

#include <matrices/Matrix4x4f.hpp>
#include <GL/glew.h>

namespace Hope::GL {
    /**
     * Compute the perspective matrix.
     * Replaces the deprecated gluPerspective() function.
     * @param   result  Projection matrix as output
     * @param   fovY    Specifies the field of view angle, in degrees, in the y
     *                  direction.
     * @param   aspect  Specifies the aspect ratio that determines the field of
     *                  view in the x direction.
     *                  The aspect ratio is the ratio of x (width) to y
     *                  (height).
     * @param   zNear   Specifies the distance from the viewer to the near
     *                  clipping plane (always positive).
     * @param   zFar    Specifies the distance from the viewer to the far
     *                  clipping plane (always positive).
     */
    void GLPerspective(
        Mind::Matrix4x4f& result,
        const GLdouble fovY,
        const GLdouble aspect,
        const GLdouble zNear,
        const GLdouble zFar
    ) ;

    /**
     * Compute the orthographic matrix.
     * Replaces the deprecated glOrtho() function.
     * @param   result  Projection matrix as output
     * @param   top     Specify the coordinates for the top horizontal clipping
     *                  plane.
     * @param   bottom  Specify the coordinates for the bottom horizontal
     *                  clipping plane.
     * @param   left    Specify the coordinates for the left vertical clipping
     *                  plane.
     * @param   right   Specify the coordinates for the right vertical clipping
     *                  plane.
     * @param   zNear   Specifies the distance from the viewer to the near
     *                  clipping plane (always positive).
     * @param   zFar    Specifies the distance from the viewer to the far
     *                  clipping plane (always positive).
     */
    void GLOrthographic(
        Mind::Matrix4x4f& result,
        const GLdouble left,
        const GLdouble right,
        const GLdouble bottom,
        const GLdouble top,
        const GLdouble zNear,
        const GLdouble zFar
    ) ;
}

#endif
