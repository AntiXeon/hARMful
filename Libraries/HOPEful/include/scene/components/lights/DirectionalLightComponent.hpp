#ifndef __HOPE__DIRECTIONAL_LIGHT_COMPONENT__
#define __HOPE__DIRECTIONAL_LIGHT_COMPONENT__

#include <scene/components/lights/LightComponent.hpp>

namespace Hope {
    /**
     * A directional light sends light in a single direction. It is useful for
     * representing the sun/moon light for example.
     */
    class DirectionalLightComponent final : public LightComponent {
        private:
            /**
             * Direction of the light.
             */
            Mind::Vector3f m_direction ;

        public:
            /**
             * Create a new DirectionalLightComponent.
             */
            DirectionalLightComponent() ;

            /**
             * Get the maximal amount of directional lights in shader programs.
             */
            uint8_t maxAmount() override {
                return 1 ;
            }

            /**
             * Set the direction of the light.
             */
            void setDirection(const Mind::Vector3f& direction) {
                m_direction = direction ;
            }

            /**
             * Set the direction of the light.
             */
            void setDirection(const float x, const float y, const float z) {
                m_direction = Mind::Vector3f(x, y, z) ;
            }

            /**
             * Get the direction of the light.
             */
            Mind::Vector3f direction() {
                return m_direction ;
            }
    } ;
}

#endif
