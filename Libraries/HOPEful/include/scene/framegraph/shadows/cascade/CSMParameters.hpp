#ifndef __HOPE__DIRECTIONAL_LIGHT_SHADOW_CASCADE_PARAMETERS__
#define __HOPE__DIRECTIONAL_LIGHT_SHADOW_CASCADE_PARAMETERS__

namespace Hope {
    class DirectionalLightComponent ;

    /**
     * Parameters of the cascade shadow mapping.
     */
    struct CSMParameters {
        /**
         * Light from which shadows are generated.
         */
        DirectionalLightComponent* light = nullptr ;

        /**
         * Maximal distance from the active camera to generate shadows.
         */
        float maxDistance ;

        /**
         * If true, the maximal distance is the far plane distance of the
         * rendering camera.
         */
        bool useCameraFarPlaneDistance = true ;

        /**
         * Resolution of the shadow map.
         * Size of the framebuffer and viewport to render the scene from the
         * light point of view.
         */
        uint32_t resolution ;

        /**
         * Amount of cascades.
         */
        uint8_t amountCascades ;
    } ;
}

#endif
