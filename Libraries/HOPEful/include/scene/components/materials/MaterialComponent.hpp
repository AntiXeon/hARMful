#ifndef __HOPE__ABSTRACT_MATERIAL__
#define __HOPE__ABSTRACT_MATERIAL__

#include <scene/components/Component.hpp>
#include <scene/framegraph/shading/RenderEffect.hpp>
#include <scene/framegraph/shading/ShaderValue.hpp>
#include <map>
#include <string>

namespace Hope {
    /**
     * A material is applied to a 3D object to define how it is rendered.
     */
    class MaterialComponent : public Component {
        private:
            /**
             * Name of the default parameters used for uniform values of the
             * shaders.
             */
            static const std::string ModelMatrixParamName ;
            static const std::string ViewMatrixParamName ;
            static const std::string ProjectionMatrixParamName ;
            static const std::string ModelViewMatrixParamName ;
            static const std::string ViewProjectionMatrixParamName ;
            static const std::string MVPMatrixParamName ;
            static const std::string InverseModelMatrixParamName ;
            static const std::string InverseViewMatrixParamName ;
            static const std::string InverseProjectionMatrixParamName ;
            static const std::string InverseModelViewMatrixParamName ;
            static const std::string InverseViewProjectionMatrixParamName ;
            static const std::string InverseMVPMatrixParamName ;
            static const std::string ModelNormalMatrixParamName ;
            static const std::string ModelViewNormalMatrixParamName ;
            static const std::string ViewportMatrixParamName ;
            static const std::string InverseViewportMatrixParamName ;
            static const std::string AspectRatioParamName ;
            static const std::string TimeParamName ;
            static const std::string EyePositionParamName ;

            /**
             * Name of the lighting related uniform values of the shaders.
             */
            static const std::string DirectionalLightParamName ;
            static const std::string PointLightParamName ;
            static const std::string SpotLightParamName ;
            static const std::string HemisphereLightParamName ;

            static const std::string LightAmbientParamName ;
            static const std::string LightDiffuseParamName ;
            static const std::string LightSpecularParamName ;
            static const std::string LightDirectionParamName ;

            static const unsigned short AmountUniformNames = 19 ;
            static const std::string UniformNames[AmountUniformNames] ;

            // /**
            //  * All the default uniforms.
            //  */
            // std::shared_ptr<Hope::ShaderUniform> m_modelMatrix = nullptr ;
            // std::shared_ptr<Hope::ShaderUniform> m_viewMatrix = nullptr ;
            // std::shared_ptr<Hope::ShaderUniform> m_projectionMatrix = nullptr ;
            // std::shared_ptr<Hope::ShaderUniform> m_modelViewMatrix = nullptr ;
            // std::shared_ptr<Hope::ShaderUniform> m_viewProjectionMatrix = nullptr ;
            // std::shared_ptr<Hope::ShaderUniform> m_mvpMatrix = nullptr ;
            // std::shared_ptr<Hope::ShaderUniform> m_inverseModelMatrix = nullptr ;
            // std::shared_ptr<Hope::ShaderUniform> m_inverseViewMatrix = nullptr ;
            // std::shared_ptr<Hope::ShaderUniform> m_inverseProjectionMatrix = nullptr ;
            // std::shared_ptr<Hope::ShaderUniform> m_inverseModelViewMatrix = nullptr ;
            // std::shared_ptr<Hope::ShaderUniform> m_inverseViewProjectionMatrix = nullptr ;
            // std::shared_ptr<Hope::ShaderUniform> m_inverseMVPMatrix = nullptr ;
            // std::shared_ptr<Hope::ShaderUniform> m_modelNormalMatrix = nullptr ;
            // std::shared_ptr<Hope::ShaderUniform> m_modelViewNormalMatrix = nullptr ;
            // std::shared_ptr<Hope::ShaderUniform> m_viewportMatrix = nullptr ;
            // std::shared_ptr<Hope::ShaderUniform> m_inverseViewportMatrix = nullptr ;
            // std::shared_ptr<Hope::ShaderUniform> m_aspectRatio = nullptr ;
            // std::shared_ptr<Hope::ShaderUniform> m_time = nullptr ;
            // std::shared_ptr<Hope::ShaderUniform> m_eyePosition = nullptr ;

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
             * Add a shader uniform value.
             * It is sent to the shader as a uniform value.
             * Some usual values are already sent to the shaders.
             */
            void addShaderUniform(const std::shared_ptr<Hope::ShaderUniform> uniform) ;

            /**
             * Remove a shader ubniform.
             */
            void removeShaderUniform(const std::shared_ptr<Hope::ShaderUniform> uniform) ;

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
    } ;
}

#endif
