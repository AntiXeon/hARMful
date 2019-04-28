#ifndef __HOPE__SCENE_LIGHT_DATA__
#define __HOPE__SCENE_LIGHT_DATA__

#include <matrices/Matrix4x4f.hpp>

namespace Hope {
    class DirectionalLightComponent ;
    class PointLightComponent ;
}

namespace Hope::GL {
    /**
     * Light and its transformation matrix.
     */
    struct DirectionalLightData {
        DirectionalLightComponent* light ;
        Mind::Matrix4x4f worldTransformation ;
    } ;

    /**
     * Light and its transformation matrix.
     */
    struct PointLightData {
        PointLightComponent* light ;
        Mind::Matrix4x4f worldTransformation ;
    } ;
}

#endif
