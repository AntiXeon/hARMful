#ifndef __HOPE__BASE_LIGHT_COMPONENT__
#define __HOPE__BASE_LIGHT_COMPONENT__

#include <scene/components/Component.hpp>
#include <scene/common/Color.hpp>
#include <geometry/points/Point3Df.hpp>

namespace Hope {
    /**
     * Base class for lights.
     */
    class LightComponent : public Component {
        public:
            /**
             * Possible light types.
             */
            enum class Type {
                Directional,
                Point,
                Spot
            } ;

        private:
            /**
             * Type of the light.
             */
            Type m_type ;

            /**
             * Color of the light.
             */
            Color m_color ;

            /**
             * Power of the light.
             */
            float m_power ;

            /**
             * To know if the light generates a specular.
             */
            bool m_generateSpecular ;

        public:
            /**
             * Create a new LightComponent.
             */
            LightComponent(const Type type) ;

            /**
             * No need to be visited!
             */
            void accept(ISceneGraphVisitor*) override { /* Do nothing! */ }

            /**
             * To know if the component can be shared by several entities.
             * @return  false, the light cannot be shared.
             */
            bool isShareable() const override {
                return false ;
            }

            /**
             * Set the color.
             */
            void setColor(const Color& color) {
                m_color = color ;
            }

            /**
             * Set the color.
             */
            void setColor(const int color) {
                m_color = Color(color) ;
            }

            /**
             * Set the color.
             */
            void setColor(
                const uint8_t red,
                const uint8_t green,
                const uint8_t blue
            ) {
                m_color = Color(red, green, blue, 255) ;
            }

            /**
             * Set the power.
             */
            void setPower(const float power) {
                m_power = power ;
            }

            /**
             * Set the generation of specular on or off.
             */
            void setSpecularGenerated(const bool generated) {
                m_generateSpecular = generated ;
            }

            /**
             * Get the color of the light.
             */
            Color color() const {
                return m_color ;
            }

            /**
             * Get the power of the light.
             */
            float power() const {
                return m_power ;
            }

            /**
             * To know if the light generates a specular.
             */
            bool generateSpecular() const {
                return m_generateSpecular ;
            }

            /**
             * Get the type of the light.
             */
            Type type() const {
                return m_type ;
            }

            /**
             * Get the position of the light.
             */
            Mind::Vector3f position() const ;
    } ;
}

#endif
