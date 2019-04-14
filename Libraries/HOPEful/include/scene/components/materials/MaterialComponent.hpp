#ifndef __HOPE__ABSTRACT_MATERIAL__
#define __HOPE__ABSTRACT_MATERIAL__

#include <scene/components/Component.hpp>
#include <scene/framegraph/shading/RenderEffect.hpp>
#include <scene/framegraph/shading/ShaderValue.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <map>
#include <string>

namespace Hope {
    /**
     * A material is applied to a 3D object to define how it is rendered.
     */
    class MaterialComponent : public Component {
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
             * List of shader parameters.
             */
            std::map<std::string, std::shared_ptr<Hope::ShaderAttribute>> m_shaderAttribs ;

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
             * Accept the visitor.
             */
            void accept(ISceneGraphVisitor* visitor) override ;

            /**
             * To know if the component can be shared by several entities.
             * @return  true as it can be shared among several objects that are
             *          rendered the same way.
             */
            bool isShareable() const override ;

            /**
             * Get the effect of the material.
             */
            RenderEffect& effect() ;

            /**
             * Get the shader attributes.
             */
            std::map<std::string, std::shared_ptr<Hope::ShaderAttribute>> shaderAttributes() const {
                return m_shaderAttribs ;
            }

            /**
             * Get the shader uniforms.
             */
            std::map<std::string, std::shared_ptr<Hope::ShaderUniform>> shaderUniforms() const {
                return m_shaderUniforms ;
            }

        protected:
            /**
             * Add a shader attribute.
             */
            void addShaderAttribute(const std::shared_ptr<Hope::ShaderAttribute> attrib) ;

            /**
             * Remove a shader attribute.
             */
            void removeShaderAttribute(const std::shared_ptr<Hope::ShaderAttribute> attrib) ;

            /**
             * Get the attribute with the given name.
             */
            std::shared_ptr<Hope::ShaderAttribute> attribute(const std::string& name) {
                return m_shaderAttribs[name] ;
            }

            /**
             * Add a shader uniform value.
             * It is sent to the shader as a uniform value.
             * Some usual values are already sent to the shaders.
             */
            void addShaderUniform(const std::shared_ptr<Hope::ShaderUniform> uniform) ;

            /**
             * Remove a shader ubniform.
             */
            void removeShaderUniform(const std::shared_ptr<Hope::ShaderUniform> uniform) ;

            /**
             * Get the uniform with the given name.
             */
            std::shared_ptr<Hope::ShaderUniform> uniform(const std::string& name) {
                return m_shaderUniforms[name] ;
            }

        private:
            /**
             * Set up the default uniform values.
             * The values are updated just before the component accepts the
             * rendering visitor.
             * @see     accept(ISceneGraphVisitor* visitor)
             * @see     updateParameterValues()
             */
            void setupDefaultUniforms() ;

            /**
             * Update the uniform values before the processing of the material
             * component.
             */
            void updateUniformValues(ISceneGraphVisitor* visitor) ;

        protected:
            /**
             * Update the values of additional uniforms.
             */
            virtual void updateAdditionalUniformValues(ISceneGraphVisitor*) {}
    } ;
}

#endif
