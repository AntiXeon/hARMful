#ifndef __HOPE__RENDER_REQUIRED_DATA__
#define __HOPE__RENDER_REQUIRED_DATA__

#include <scene/framegraph/Viewport.hpp>
#include <matrices/Matrix3x3f.hpp>
#include <matrices/Matrix4x4f.hpp>
#include <geometry/points/Point3Df.hpp>

namespace Hope {
    /**
     * Data that are required to render the scene graph.
     */
    struct RenderRequiredData final {
        /**
         * Aspect ratio.
         */
        float aspectRatio ;

        /**
         * Time since the launch of the application.
         */
        double time ;

        /**
         * Position of the camera.
         */
        Mind::Vector3f eyePosition ;

        /**
         * View matrix.
         */
        Mind::Matrix4x4f viewMatrix ;

        /**
         * Projection matrix.
         */
        Mind::Matrix4x4f projectionMatrix ;

        /**
         * Viewport in which the scene is rendered.
         */
        Viewport* viewport ;
    } ;
}

#endif
