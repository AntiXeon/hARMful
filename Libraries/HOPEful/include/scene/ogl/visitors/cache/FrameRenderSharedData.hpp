#ifndef __HOPE__FRAME_RENDER_SHARED_DATA__
#define __HOPE__FRAME_RENDER_SHARED_DATA__

#include <scene/framegraph/Viewport.hpp>
#include <matrices/Matrix3x3f.hpp>
#include <matrices/Matrix4x4f.hpp>
#include <geometry/points/Point3Df.hpp>

namespace Hope::GL {
    /**
     * Data that are required to render the current frame.
     */
    struct FrameRenderSharedData final {
        /**
         * View matrix.
         */
        Mind::Matrix4x4f viewMatrix ;

        /**
         * Projection matrix.
         */
        Mind::Matrix4x4f projectionMatrix ;
    } ;
}

#endif
