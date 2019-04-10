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
             * Ambient color of the light.
             */
            Color m_ambient ;

            /**
             * Diffuse color of the light.
             */
            Color m_diffuse ;

            /**
             * Specular color of the light.
             */
            Color m_specular ;

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
             * Get the maximal amount of light of the current type that can be
             * handled by the shaders.
             */
            virtual uint8_t maxAmount() = 0 ;

            /**
             * Set the ambient color.
             */
            void setAmbient(const Color& color) {
                m_ambient = color ;
            }

            /**
             * Set the ambient color.
             */
            void setAmbient(const int color) {
                m_ambient = Color(color) ;
            }

            /**
             * Set the ambient color.
             */
            void setAmbient(
                const uint8_t red,
                const uint8_t green,
                const uint8_t blue
            ) {
                m_ambient = Color(red, green, blue, 255) ;
            }

            /**
             * Set the diffuse color.
             */
            void setDiffuse(const Color& color) {
                m_diffuse = color ;
            }

            /**
             * Set the diffuse color.
             */
            void setDiffuse(const int color) {
                m_diffuse = Color(color) ;
            }

            /**
             * Set the diffuse color.
             */
            void setDiffuse(
                const uint8_t red,
                const uint8_t green,
                const uint8_t blue
            ) {
                m_diffuse = Color(red, green, blue, 255) ;
            }

            /**
             * Set the specular color.
             */
            void setSpecular(const Color& color) {
                m_specular = color ;
            }

            /**
             * Set the specular color.
             */
            void setSpecular(const int color) {
                m_specular = Color(color) ;
            }

            /**
             * Set the specular color.
             */
            void setSpecular(
                const uint8_t red,
                const uint8_t green,
                const uint8_t blue
            ) {
                m_specular = Color(red, green, blue, 255) ;
            }

            /**
             * Get the ambient color of the light.
             */
            Color ambient() const {
                return m_ambient ;
            }

            /**
             * Get the diffuse color of the light.
             */
            Color diffuse() const {
                return m_diffuse ;
            }

            /**
             * Get the specular color of the light.
             */
            Color specular() const {
                return m_specular ;
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
