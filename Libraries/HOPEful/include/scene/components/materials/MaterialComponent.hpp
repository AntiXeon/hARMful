#ifndef __HOPE__ABSTRACT_MATERIAL__
#define __HOPE__ABSTRACT_MATERIAL__

#include <scene/components/Component.hpp>
#include <scene/framegraph/shading/RenderEffect.hpp>
#include <scene/framegraph/shading/ShaderValue.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <map>
#include <string>

#include <HopeAPI.hpp>

#ifdef OGL
    namespace API = Hope::GL ;
#endif

namespace Hope {
    /**
     * A material is applied to a 3D object to define how it is rendered.
     */
    class MaterialComponent : public Component {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = MaterialComponentType ;

        private:
            /**
             * Names of the uniform variables.
             */
            static const UniformNames Uniforms ;

            /**
             * Effect of the material.
             */
            RenderEffect m_effect ;

            /**
             * List of shader uniforms.
             */
            std::map<std::string, std::shared_ptr<Hope::ShaderUniform>> m_shaderUniforms ;

        public:
            /**
             * Create a MaterialComponent.
             */
            MaterialComponent() ;

            /**
             * Update the uniform values before the processing of the material
             * component.
             */
            virtual void updateUniformValues() = 0 ;

            /**
             * To know if the component can be shared by several entities.
             * @return  true as it can be shared among several objects that are
             *          rendered the same way.
             */
            bool isShareable() const override {
                return true ;
            }

            /**
             * To know if the component can be removed from its entity(-ies).
             * @return  false, the component cannot be removed.
             */
            bool isRemovable() const override {
                return false ;
            }

            /**
             * To know if several components of the current type can be beared
             * by a single entity.
             * @return  true, an entity can bear several MaterialComponent.
             */
            bool isStackable() const override {
                return true ;
            }

            /**
             * Check if the material has a render pass corresponding the
             * provided ID.
             */
            bool hasRenderPass(const RenderPassID passID) const {
                return m_effect.hasRenderPass(passID) ;
            }

            /**
             * Get a render pass.
             * @return  The render pass having the provided ID if available;
             *          nullptr otherwise.
             */
            std::shared_ptr<API::RenderPass> renderPass(const RenderPassID passID) const {
                return m_effect.renderPass(passID) ;
            }

            /**
             * Get the shader uniforms.
             */
            std::map<std::string, std::shared_ptr<Hope::ShaderUniform>> shaderUniforms() const {
                return m_shaderUniforms ;
            }

        protected:
            /**
             * Get the effect of the material.
             */
            RenderEffect& effect() {
                return m_effect ;
            }

            /**
             * Add a shader uniform value.
             * It is sent to the shader as a uniform value.
             * Some usual values are already sent to the shaders.
             */
            void addShaderUniform(const std::shared_ptr<Hope::ShaderUniform> uniform) {
                m_shaderUniforms[uniform -> name()] = uniform ;
            }

            /**
             * Remove a shader ubniform.
             */
            void removeShaderUniform(const std::shared_ptr<Hope::ShaderUniform> uniform) {
                m_shaderUniforms.erase(uniform -> name()) ;
            }

            /**
             * Get the uniform with the given name.
             */
            std::shared_ptr<Hope::ShaderUniform> uniform(const std::string& name) {
                return m_shaderUniforms[name] ;
            }

            /**
             * Setup the render passes of the material.
             */
            void setupRendering() ;

            /**
             * Setup the shader for the forward rendering pass.
             */
            virtual void setupForwardShader() = 0 ;

            /**
             * Setup the shader for the deferred rendering pass.
             */
            virtual void setupDeferredShader() = 0 ;

        private:
            /**
             * Set up the shader for the depth map used to generate the shadow
             * map of a directional light.
             */
            void setupDirectionalLightDepthMapShader() ;
    } ;
}

#endif
