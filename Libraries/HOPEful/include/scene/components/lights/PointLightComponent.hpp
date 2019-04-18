#ifndef __HOPE__POINT_LIGHT_COMPONENT__
#define __HOPE__POINT_LIGHT_COMPONENT__

#include <scene/components/lights/LightComponent.hpp>

namespace Hope {
    /**
     * A point light sends light in a all directions but on a limited distance.
     */
    class PointLightComponent final : public LightComponent {
        private:
            /**
             * Distance of the light effect.
             */
            float m_distance ;

        public:
            /**
             * Create a new PointLightComponent instance.
             */
            PointLightComponent() ;

            /**
             * Set the distance of the light effect.
             */
            void setDistance(const float distance) ;

            /**
             * Get the distance of the light effect.
             */
            float distance() const {
                return m_distance ;
            }
    } ;
}

#endif
