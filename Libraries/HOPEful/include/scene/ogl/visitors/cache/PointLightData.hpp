#ifndef __HOPE__SCENE_POINT_LIGHT_DATA__
#define __HOPE__SCENE_POINT_LIGHT_DATA__

#include <scene/ogl/mesh/MeshPart.hpp>
#include <geometry/points/Point4Df.hpp>

namespace Hope {
    class PointLightComponent ;
}

namespace Hope::GL {
    class FrameRenderSharedData ;

    /**
     * A point light and its world position.
     */
    struct PointLightData {
        PointLightComponent* light ;
        Mind::Vector4f worldPosition ;
        FrameRenderSharedData* sharedData ;
    } ;
}

#endif
