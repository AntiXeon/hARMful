#ifndef __HOPE__POINT_LIGHT_COMPONENT__
#define __HOPE__POINT_LIGHT_COMPONENT__

#include <utils/Platform.hpp>

#include <scene/components/lights/LightComponent.hpp>
#include <algorithm>

namespace Hope {
    /**
     * A point light sends light in a all directions but on a limited distance.
     */
    class PointLightComponent final : public LightComponent {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = LightComponentType ;

        private:
            /**
             * Distance of the light effect.
             */
            float m_distance ;

            /**
             * Linear attenuation of the light.
             */
            float m_linearAttenuation ;

            /**
             * Quadratic attenuation of the light.
             */
            float m_quadraticAttenuation ;

        public:
            /**
             * Create a new PointLightComponent instance.
             */
            exported PointLightComponent() ;

            /**
             * Set the distance of the light effect.
             */
            exported void setDistance(const float distance) {
                m_distance = distance ;
                signalChange() ;
            }

            /**
             * Set the linear attenuation of the light effect. It is set between
             * 0 and 1.
             */
            exported void setLinearAttenuation(const float attenuation) {
                m_linearAttenuation = std::clamp(attenuation, 0.f, 1.f) ;
                signalChange() ;
            }

            /**
             * Set the quadratic attenuation of the light effect. It is set
             * between 0 and 1.
             */
            exported void setQuadraticAttenuation(const float attenuation) {
                m_quadraticAttenuation = std::clamp(attenuation, 0.f, 1.f) ;
                signalChange() ;
            }

            /**
             * Get the distance of the light effect.
             */
            exported float distance() const {
                return m_distance ;
            }

            /**
             * Get the linear attenuation of the light effect.
             */
            exported float linearAttenuation() const {
                return m_linearAttenuation ;
            }

            /**
             * Get the quadratic attenuation of the light effect.
             */
            exported float quadraticAttenuation() const {
                return m_quadraticAttenuation ;
            }
    } ;
}

#endif
