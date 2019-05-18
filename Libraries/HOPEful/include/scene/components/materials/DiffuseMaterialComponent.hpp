#ifndef __HOPE__DIFFUSE_MATERIAL__
#define __HOPE__DIFFUSE_MATERIAL__

#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/components/materials/BlinnPhongMaterialComponent.hpp>
#include <scene/common/Color.hpp>
#include <algorithm>
#include <string>
#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/textures/Texture2D.hpp>
    namespace API = Hope::GL ;
#endif

namespace Hope {
    /**
     * A diffuse material uses a diffuse texture to decorate the objets.
     */
    class DiffuseMaterialComponent : public MaterialComponent {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = MaterialComponentType ;

        private:
            /**
             * Binding of the diffuse map.
             */
            static const unsigned short DiffuseMapBinding = 0 ;

            /**
             * Ambient color.
             */
            Color m_ambient ;

            /**
             * Diffuse texture.
             */
            const API::Texture2D* m_diffuse ;

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
             * Create a DiffuseMaterialComponent.
             */
            DiffuseMaterialComponent() ;

            /**
             * Destruction of the DiffuseMaterialComponent.
             */
            virtual ~DiffuseMaterialComponent() ;

            /**
             * Update the uniform values before the processing of the material
             * component.
             */
            void updateUniformValues(const RenderPassID passID) override ;

            /**
             * Set the ambient color.
             */
            void setAmbient(const Color& ambient) {
                m_ambient = ambient ;
            }

            /**
             * Set the diffuse texture.
             */
            void setDiffuseMap(const API::Texture2D* diffuse) {
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
                    BlinnPhongMaterialComponent::MinimumShininessClamp,
                    BlinnPhongMaterialComponent::MaximumShininessClamp
                ) ;
            }

            /**
             * Get the ambient color.
             */
            Color ambient() const {
                return m_ambient ;
            }

            /**
             * Get the diffuse texture.
             */
            const API::Texture2D* diffuseMap() const {
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
             * Setup the forward render pass.
             */
            void setupForwardRenderPass() override ;

            /**
             * Setup the diffuse render pass (used by deferred rendering, ...).
             */
            void setupAlbedoRenderPass() override {
                useAlbedoMapPass() ;
            }

            /**
             * Setup the normal render pass (used by deferred rendering, ...).
             */
            void setupNormalRenderPass() override {
                useGeometryNormalPass() ;
            }

            /**
             * Setup the specular render pass (used by deferred rendering, ...).
             */
            void setupSpecularRenderPass() override {
                useSpecularColorPass() ;
            }

        private:
            /**
             * Set up the Uniforms of the current material.
             */
            void setupUniforms() ;
    } ;
}

#endif
