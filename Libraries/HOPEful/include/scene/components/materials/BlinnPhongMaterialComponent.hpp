#ifndef __HOPE__BLINN_PHONG_MATERIAL__
#define __HOPE__BLINN_PHONG_MATERIAL__

#include <utils/Platform.hpp>

#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/common/Color.hpp>
#include <algorithm>
#include <string>

namespace Hope {
    /**
     * A Blinn-Phong material is composed of three main values: diffuse color,
     * ambient color and specular color + intensity.
     * It is a basic shader to put color on objects.
     */
    class BlinnPhongMaterialComponent : public MaterialComponent {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = MaterialComponentType ;

            /**
             * Shininess values.
             */
            static const float MinimumShininessClamp ;
            static const float MaximumShininessClamp ;

        private:
            /**
             * Ambient color.
             */
            Color m_ambient ;

            /**
             * Diffuse color.
             */
            Color m_diffuse ;

            /**
             * Specular color.
             */
            Color m_specular ;

            /**
             * Shininess color.
             */
            float m_shininess ;

        public:
            /**
             * Create a BlinnPhongMaterialComponent.
             */
            exported BlinnPhongMaterialComponent() ;

            /**
             * Update the uniform values before the processing of the material
             * component.
             */
            exported void updateUniformValues() override ;

            /**
             * Set the ambient color.
             */
            exported void setAmbient(const Color& ambient) {
                m_ambient = ambient ;
            }

            /**
             * Set the diffuse color.
             */
            exported void setDiffuse(const Color& diffuse) {
                m_diffuse = diffuse ;
            }

            /**
             * Set the specular color.
             */
            exported void setSpecular(const Color& specular) {
                m_specular = specular ;
            }

            /**
             * Set the shininess of the material.
             */
            exported void setShininess(const float shininess) {
                m_shininess = std::clamp(
                    shininess,
                    MinimumShininessClamp,
                    MaximumShininessClamp
                ) ;
            }

            /**
             * Get the ambient color.
             */
            exported Color ambient() const {
                return m_ambient ;
            }

            /**
             * Get the diffuse color.
             */
            exported Color diffuse() const {
                return m_diffuse ;
            }

            /**
             * Get the specular color.
             */
            exported Color specular() const {
                return m_specular ;
            }

            /**
             * Get the shininess of the material.
             */
            exported float shininess() const {
                return m_shininess ;
            }

        private:
            /**
             * Set up the Uniforms of the current material.
             */
            exported void setupUniforms() ;

        protected:
            /**
             * Setup the shader for the forward rendering pass.
             */
            exported void setupForwardShader() override ;

            /**
             * Setup the shader for the deferred rendering pass.
             */
            exported void setupDeferredShader() override ;
    } ;
} ;

#endif
