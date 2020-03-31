#ifndef __HOPE__DIFFUSE_MATERIAL__
#define __HOPE__DIFFUSE_MATERIAL__

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
            exported static const unsigned short DiffuseMapBinding = 0 ;

            /**
             * Ambient color.
             */
            Color m_ambient ;

            /**
             * Diffuse texture.
             */
            std::unique_ptr<API::TextureImage2D> m_diffuse ;

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
            exported DiffuseMaterialComponent() ;

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
             * Set the diffuse texture.
             */
            exported void setDiffuseMap(std::unique_ptr<API::TextureImage2D> diffuse) {
                m_diffuse = std::move(diffuse) ;
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
            exported void setupUniforms() ;
    } ;
}

#endif
