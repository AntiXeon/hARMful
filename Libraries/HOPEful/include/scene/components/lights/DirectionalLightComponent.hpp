#ifndef __HOPE__DIRECTIONAL_LIGHT_COMPONENT__
#define __HOPE__DIRECTIONAL_LIGHT_COMPONENT__

#include <utils/Platform.hpp>

#include <scene/components/lights/LightComponent.hpp>

namespace Hope {
    /**
     * A directional light sends light in a single direction. It is useful for
     * representing the sun/moon light for example.
     */
    class DirectionalLightComponent final : public LightComponent {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = LightComponentType ;

        private:
            /**
             * Direction of the light.
             */
            Mind::Vector3f m_direction ;

        public:
            /**
             * Create a new DirectionalLightComponent.
             */
            exported DirectionalLightComponent() ;

            /**
             * Set the direction of the light.
             */
            exported void setDirection(const Mind::Vector3f& direction) {
                m_direction = direction ;
                m_direction.normalize() ;
                signalChange() ;
            }

            /**
             * Set the direction of the light.
             */
            exported void setDirection(const float x, const float y, const float z) {
                m_direction = Mind::Vector3f(x, y, z) ;
                signalChange() ;
            }

            /**
             * Get the direction of the light.
             */
            exported const Mind::Vector3f& direction() const {
                return m_direction ;
            }
    } ;
}

#endif
