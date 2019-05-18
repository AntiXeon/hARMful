#ifndef __HOPE__SCENE_POINT_LIGHT_DATA__
#define __HOPE__SCENE_POINT_LIGHT_DATA__

#include <geometry/points/Point4Df.hpp>

namespace Hope {
    class PointLightComponent ;

    /**
     * A point light and its world position.
     */
    struct PointLightData {
        PointLightComponent* light ;
        Mind::Vector4f worldPosition ;
    } ;
}

#endif
