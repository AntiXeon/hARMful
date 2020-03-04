#ifndef __HOPE__DIFFUSE_NORMAL_SPECULAR_MATERIAL__
#define __HOPE__DIFFUSE_NORMAL_SPECULAR_MATERIAL__

#include <utils/Platform.hpp>

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
            std::unique_ptr<API::TextureImage2D> m_diffuse = nullptr ;

            /**
             * Normal map.
             */
            std::unique_ptr<API::TextureImage2D> m_normal = nullptr ;

            /**
             * Normal map.
             */
            std::unique_ptr<API::TextureImage2D> m_specular = nullptr ;

            /**
             * Shininess color.
             */
            float m_shininess ;

        public:
            /**
             * Create a DiffuseNormalSpecularMaterialComponent.
             */
            exported DiffuseNormalSpecularMaterialComponent() ;

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
             * Set the diffuse map.
             */
            exported void setDiffuseMap(std::unique_ptr<API::TextureImage2D> diffuse) {
                m_diffuse = std::move(diffuse) ;
            }

            /**
             * Set the normal map.
             */
            exported void setNormalMap(std::unique_ptr<API::TextureImage2D> normal) {
                m_normal = std::move(normal) ;
            }

            /**
             * Set the specular map.
             */
            exported void setSpecularMap(std::unique_ptr<API::TextureImage2D> specular) {
                m_specular = std::move(specular) ;
            }

            /**
             * Set the shininess of the material.
             */
            exported void setShininess(const float shininess) {
                m_shininess = std::clamp(
                    shininess,
                    BlinnPhongMaterialComponent::MinimumShininessClamp,
                    BlinnPhongMaterialComponent::MaximumShininessClamp
                ) ;
            }

            /**
             * Get the ambient color.
             */
            exported Color ambient() const {
                return m_ambient ;
            }

            /**
             * Get the diffuse texture.
             */
            exported const API::TextureImage2D* diffuseMap() const {
                return m_diffuse.get() ;
            }

            /**
             * Get the normal map.
             */
            exported const API::TextureImage2D* normalMap() const {
                return m_normal.get() ;
            }

            /**
             * Get the specular map.
             */
            exported const API::TextureImage2D* specularMap() const {
                return m_specular.get() ;
            }

            /**
             * Get the shininess of the material.
             */
            exported float shininess() const {
                return m_shininess ;
            }

        protected:
            /**
             * Setup the shader for the forward rendering pass.
             */
            exported void setupForwardShader() override ;

            /**
             * Setup the shader for the deferred rendering pass.
             */
            exported void setupDeferredShader() override ;

        private:
            /**
             * Set up the Uniforms of the current material.
             */
            void setupUniforms() ;
    } ;
}

#endif
