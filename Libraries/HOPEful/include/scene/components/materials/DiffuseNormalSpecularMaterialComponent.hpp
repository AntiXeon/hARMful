#ifndef __HOPE__DIFFUSE_NORMAL_SPECULAR_MATERIAL__
#define __HOPE__DIFFUSE_NORMAL_SPECULAR_MATERIAL__

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
     * A diffuse, normal and specular material uses a diffuse texture to
     * decorate the objets, a normal map to fake details with a lightweight
     * geometry and a specular map to adjust the light effect according to the
     * matter it represents.
     */
    class DiffuseNormalSpecularMaterialComponent : public MaterialComponent {
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
             * Binding of the normal map.
             */
            static const unsigned short NormalMapBinding = 1 ;

            /**
             * Binding of the specular map.
             */
            static const unsigned short SpecularMapBinding = 2 ;

            /**
             * Ambient color.
             */
            Color m_ambient ;

            /**
             * Diffuse map.
             */
            const API::Texture2D* m_diffuse = nullptr ;

            /**
             * Normal map.
             */
            const API::Texture2D* m_normal = nullptr ;

            /**
             * Normal map.
             */
            const API::Texture2D* m_specular = nullptr ;

            /**
             * Shininess color.
             */
            float m_shininess ;

        public:
            /**
             * Create a DiffuseNormalSpecularMaterialComponent.
             */
            DiffuseNormalSpecularMaterialComponent() ;

            /**
             * Destruction of the DiffuseNormalSpecularMaterialComponent.
             */
            virtual ~DiffuseNormalSpecularMaterialComponent() ;

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
             * Set the diffuse map.
             */
            void setDiffuseMap(const API::Texture2D* diffuse) {
                m_diffuse = diffuse ;
            }

            /**
             * Set the normal map.
             */
            void setNormalMap(const API::Texture2D* normal) {
                m_normal = normal ;
            }

            /**
             * Set the specular map.
             */
            void setSpecularMap(const API::Texture2D* specular) {
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
             * Get the normal map.
             */
            const API::Texture2D* normalMap() const {
                return m_normal ;
            }

            /**
             * Get the specular map.
             */
            const API::Texture2D* specularMap() const {
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
                useNormalMapPass() ;
            }

            /**
             * Setup the specular render pass (used by deferred rendering, ...).
             */
            void setupSpecularRenderPass() override {
                useSpecularMapPass() ;
            }

        private:
            /**
             * Set up the Uniforms of the current material.
             */
            void setupUniforms() ;
    } ;
}

#endif
