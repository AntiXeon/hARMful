#ifndef __HOPE__BLINN_PHONG_MATERIAL__
#define __HOPE__BLINN_PHONG_MATERIAL__

#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/common/Color.hpp>
#include <algorithm>
#include <string>
#include <iostream>

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
            BlinnPhongMaterialComponent() ;

            /**
             * Update the uniform values before the processing of the material
             * component.
             */
            void updateUniformValues(const RenderPassID passID) override ;

            void end(const RenderPassID) override {}

            /**
             * Set the ambient color.
             */
            void setAmbient(const Color& ambient) {
                m_ambient = ambient ;
            }

            /**
             * Set the diffuse color.
             */
            void setDiffuse(const Color& diffuse) {
                m_diffuse = diffuse ;
            }

            /**
             * Set the specular color.
             */
            void setSpecular(const Color& specular) {
                m_specular = specular ;
            }

            /**
             * Set the shininess of the material.
             */
            void setShininess(const float shininess) {
                m_shininess = std::clamp(
                    shininess,
                    MinimumShininessClamp,
                    MaximumShininessClamp
                ) ;
            }

            /**
             * Get the ambient color.
             */
            Color ambient() const {
                return m_ambient ;
            }

            /**
             * Get the diffuse color.
             */
            Color diffuse() const {
                return m_diffuse ;
            }

            /**
             * Get the specular color.
             */
            Color specular() const {
                return m_specular ;
            }

            /**
             * Get the shininess of the material.
             */
            float shininess() const {
                return m_shininess ;
            }

        protected:
            /**
             * Setup the default render pass (used by forward rendering, ...).
             */
            void setupDefaultRenderPass() override ;

            /**
             * Setup the diffuse render pass (used by deferred rendering, ...).
             */
            void setupDiffuseRenderPass() override ;

            /**
             * Setup the normal render pass (used by deferred rendering, ...).
             */
            void setupNormalRenderPass() override ;

            /**
             * Setup the position render pass (used by deferred rendering, ...).
             */
            void setupSpecularRenderPass() override ;

        private:
            /**
             * Set up the Uniforms of the current material.
             */
            void setupUniforms() ;
    } ;
} ;

#endif
