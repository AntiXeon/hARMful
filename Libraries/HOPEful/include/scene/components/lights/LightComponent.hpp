#ifndef __HOPE__BASE_LIGHT_COMPONENT__
#define __HOPE__BASE_LIGHT_COMPONENT__

#include <utils/Platform.hpp>

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
             * Component class type.
             */
            static const ComponentType ClassType = LightComponentType ;

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

            /**
             * To know if the light parameters have changed.
             */
            bool m_hasChanged = true ;

        public:
            /**
             * Create a new LightComponent.
             */
            exported LightComponent(const Type type) ;

            /**
             * To know if the component can be shared by several entities.
             * @return  false, the light cannot be shared.
             */
            exported bool isShareable() const override {
                return false ;
            }

            /**
             * To know if the component can be removed from its entity(-ies).
             * @return  true, the component can be removed.
             */
            exported bool isRemovable() const override {
                return true ;
            }

            /**
             * To know if several components of the current type can be beared
             * by a single entity.
             * @return  false, an entity cannot bear several LightComponent.
             */
            exported bool isStackable() const override {
                return false ;
            }

            /**
             * Set the color.
             */
            exported void setColor(const Color& color) {
                m_color = color ;
                signalChange() ;
            }

            /**
             * Set the color.
             */
            exported void setColor(const int color) {
                m_color = Color(color) ;
                signalChange() ;
            }

            /**
             * Set the color.
             */
            exported void setColor(
                const uint8_t red,
                const uint8_t green,
                const uint8_t blue
            ) {
                m_color = Color(red, green, blue, 255) ;
                signalChange() ;
            }

            /**
             * Set the power.
             */
            exported void setPower(const float power) {
                m_power = power ;
                signalChange() ;
            }

            /**
             * Set the generation of specular on or off.
             */
            exported void setSpecularGenerated(const bool generated) {
                m_generateSpecular = generated ;
                signalChange() ;
            }

            /**
             * Get the color of the light.
             */
            exported const Color& color() const {
                return m_color ;
            }

            /**
             * Get the power of the light.
             */
            exported float power() const {
                return m_power ;
            }

            /**
             * To know if the light generates a specular.
             */
            exported bool generateSpecular() const {
                return m_generateSpecular ;
            }

            /**
             * Get the type of the light.
             */
            exported Type lightType() const {
                return m_type ;
            }

            /**
             * Get the position of the light.
             */
            exported Mind::Vector3f position() const ;

            /**
             * To know if the lamp has changed.
             */
            exported bool hasChanged() const {
                return m_hasChanged ;
            }

            /**
             * Clear any change signal in the light.
             */
            exported void clearChange() {
                m_hasChanged = false ;
            }

        protected:
            /**
             * Signal any change in light parameters.
             */
            exported void signalChange() {
                m_hasChanged = true ;
            }
    } ;
}

#endif
