#ifndef __HOPE__DIFFUSE_NORMAL_MATERIAL__
#define __HOPE__DIFFUSE_NORMAL_MATERIAL__

#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/components/materials/PhongMaterialComponent.hpp>
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
     * A diffuse and normal material uses a diffuse texture to decorate the
     * objets and a normal map to fake details with a lightweight geometry.
     */
    class DiffuseNormalMaterialComponent : public MaterialComponent {
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
            const API::Texture2D* m_diffuse = nullptr ;

            /**
             * Normal map.
             */
            const API::Texture2D* m_normal = nullptr ;

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
             * Destruction of the DiffuseNormalMaterialComponent.
             */
            virtual ~DiffuseNormalMaterialComponent() ;

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
                    PhongMaterialComponent::MinimumShininessClamp,
                    PhongMaterialComponent::MaximumShininessClamp
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

        private:
            /**
             * Set up the Uniforms of the current material.
             */
            void setupUniforms() ;

            /**
             * Set up the material rendering (techniques, shaders, ...).
             */
            void setupRendering() ;
    } ;
}

#endif
