#ifndef __HOPE__PHONG_MATERIAL__
#define __HOPE__PHONG_MATERIAL__

#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/common/Color.hpp>
#include <string>

namespace Hope {
    /**
     * A Phong material is composed of three main values: diffuse color, ambient
     * color and specular color + intensity.
     * It is a basic shader to put color on objects.
     */
    class PhongMaterialComponent : public MaterialComponent {
        private:
            /**
             * Shininess values.
             */
            static const float MinimumShininessClamp ;
            static const float MaximumShininessClamp ;


            /**
             * Name of the ambient color uniform in the shader.
             */
            static const std::string AmbientUniformName ;

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
             * Uniform of the ambient color (vec4). The object can emit some
             * color even without light.
             */
            std::shared_ptr<Hope::ShaderUniform> m_ambientUniform = nullptr ;

            /**
             * Uniform of the diffuse color (vec4). The color the material
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

        public:
            /**
             * Create a PhongMaterialComponent.
             */
            PhongMaterialComponent() ;

            /**
             * Set the ambient color.
             */
            void setAmbient(const Color& ambient) ;

            /**
             * Set the diffuse color.
             */
            void setDiffuse(const Color& diffuse) ;

            /**
             * Set the specular color.
             */
            void setSpecular(const Color& specular) ;

            /**
             * Set the shininess of the material.
             */
            void setShininess(const float shininess) ;

            /**
             * Get the ambient color.
             */
            Color ambient() const ;

            /**
             * Get the diffuse color.
             */
            Color diffuse() const ;

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

        protected:
            /**
             * Update the values of additional uniforms.
             */
            void updateAdditionalUniformValues(ISceneGraphVisitor* visitor) override ;
    } ;
} ;

#endif
