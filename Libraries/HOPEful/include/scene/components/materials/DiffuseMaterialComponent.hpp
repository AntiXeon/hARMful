#ifndef __HOPE__DIFFUSE_MATERIAL__
#define __HOPE__DIFFUSE_MATERIAL__

#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/common/Color.hpp>
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
        private:
            /**
             * Binding of the diffuse map.
             */
            static const unsigned short DiffuseMapBinding = 0 ;

            /**
             * Shininess values.
             */
            static const float MinimumShininessClamp ;
            static const float MaximumShininessClamp ;

            /**
             * Name of the diffuse color uniform in the shader.
             */
            static const std::string DiffuseUniformName ;

            /**
             * Name of the specular color uniform in the shader.
             */
            static const std::string SpecularUniformName ;

            /**
             * Name of the shininess uniform in the shader.
             */
            static const std::string ShininessUniformName ;

            /**
             * Uniform of the diffuse map (sampler2D). The color the material
             * does not absorb, that is the color we see when there is a light.
             */
            std::shared_ptr<Hope::ShaderUniform> m_diffuseUniform = nullptr ;

            /**
             * Uniform of the specular color (vec4). The lights can produce a
             * shiny spot on the material.
             */
            std::shared_ptr<Hope::ShaderUniform> m_specularUniform = nullptr ;

            /**
             * Uniform of the shininess (float). The more it is shiny, the
             * more the specular spot is little but intense as metal for
             * instance.
             * On the contrary, lower shininess values will provide a bigger
             * specular spot on the object surface but less intense, like a
             * rough surface.
             */
            std::shared_ptr<Hope::ShaderUniform> m_shininessUniform = nullptr ;

            /**
             * Diffuse map.
             */
            const API::Texture2D* m_diffuseMap = nullptr ;

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
            void updateUniformValues() override ;

            /**
             * Set the diffuse color.
             */
            void setDiffuse(const API::Texture2D* diffuse) ;

            /**
             * Set the specular color.
             */
            void setSpecular(const Color& specular) ;

            /**
             * Set the shininess of the material.
             */
            void setShininess(const float shininess) ;

            /**
             * Get the diffuse texture.
             */
            const API::Texture2D* diffuse() const ;

            /**
             * Get the specular color.
             */
            Color specular() const ;

            /**
             * Get the shininess of the material.
             */
            float shininess() const ;

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
