#ifndef __HOPE__DIFFUSE_NORMAL_MATERIAL__
#define __HOPE__DIFFUSE_NORMAL_MATERIAL__

#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/components/materials/BlinnPhongMaterialComponent.hpp>
#include <scene/common/Color.hpp>
#include <algorithm>
#include <memory>
#include <string>


#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/textures/TextureImage2D.hpp>
    namespace API = Hope::GL ;
#endif

namespace Hope {
    /**
     * A diffuse and normal material uses a diffuse texture to decorate the
     * objets and a normal map to fake details with a lightweight geometry.
     */
    class DiffuseNormalMaterialComponent : public MaterialComponent {
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
             * Ambient color.
             */
            Color m_ambient ;

            /**
             * Diffuse map.
             */
            std::unique_ptr<API::TextureImage2D> m_diffuse = nullptr ;

            /**
             * Normal map.
             */
            std::unique_ptr<API::TextureImage2D> m_normal = nullptr ;

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
             * Create a DiffuseNormalMaterialComponent.
             */
            DiffuseNormalMaterialComponent() ;

            /**
             * Update the uniform values before the processing of the material
             * component.
             */
            void updateUniformValues() override ;

            /**
             * Set the ambient color.
             */
            void setAmbient(const Color& ambient) {
                m_ambient = ambient ;
            }

            /**
             * Set the diffuse map.
             */
            void setDiffuseMap(std::unique_ptr<API::TextureImage2D> diffuse) {
                m_diffuse = std::move(diffuse) ;
            }

            /**
             * Set the normal map.
             */
            void setNormalMap(std::unique_ptr<API::TextureImage2D> normal) {
                m_normal = std::move(normal) ;
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
            const API::TextureImage2D* diffuseMap() const {
                return m_diffuse.get() ;
            }

            /**
             * Get the normal map.
             */
            const API::TextureImage2D* normalMap() const {
                return m_normal.get() ;
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
             * Setup the shader for the forward rendering pass.
             */
            void setupForwardShader() override ;

            /**
             * Setup the shader for the deferred rendering pass.
             */
            void setupDeferredShader() override ;

        private:
            /**
             * Set up the Uniforms of the current material.
             */
            void setupUniforms() ;
    } ;
}

#endif
