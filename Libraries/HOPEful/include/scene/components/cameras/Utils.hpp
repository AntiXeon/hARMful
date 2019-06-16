#ifndef __HOPE__GENERIC_CAMERA_UTILS__
#define __HOPE__GENERIC_CAMERA_UTILS__

#include <matrices/Matrix4x4f.hpp>

namespace Hope {
    /**
     * Compute the perspective matrix.
     * @param   result  Projection matrix as output.
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
    void Perspective(
        Mind::Matrix4x4f& result,
        const double fovY,
        const double aspect,
        const double zNear,
        const double zFar
    ) ;

    /**
     * Compute the orthographic matrix.
     * @param   result  Projection matrix as output.
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
    void Orthographic(
        Mind::Matrix4x4f& result,
        const double left,
        const double right,
        const double bottom,
        const double top,
        const double zNear,
        const double zFar
    ) ;
}

#endif
