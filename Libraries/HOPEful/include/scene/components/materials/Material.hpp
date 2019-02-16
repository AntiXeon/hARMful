#ifndef __HOPE__ABSTRACT_MATERIAL__
#define __HOPE__ABSTRACT_MATERIAL__

#include <scene/components/Component.hpp>
#include <scene/framegraph/shading/RenderEffect.hpp>
#include <scene/framegraph/shading/ShaderParameter.hpp>

namespace Hope {
    /**
     * A material is applied to a 3D object to define how it is rendered.
     */
    class Material : public Component {
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
             * All the default parameters.
             */
            std::shared_ptr<Hope::ShaderParameter> m_modelMatrix = nullptr ;
            std::shared_ptr<Hope::ShaderParameter> m_viewMatrix = nullptr ;
            std::shared_ptr<Hope::ShaderParameter> m_projectionMatrix = nullptr ;
            std::shared_ptr<Hope::ShaderParameter> m_modelViewMatrix = nullptr ;
            std::shared_ptr<Hope::ShaderParameter> m_viewProjectionMatrix = nullptr ;
            std::shared_ptr<Hope::ShaderParameter> m_mvpMatrix = nullptr ;
            std::shared_ptr<Hope::ShaderParameter> m_inverseModelMatrix = nullptr ;
            std::shared_ptr<Hope::ShaderParameter> m_inverseViewMatrix = nullptr ;
            std::shared_ptr<Hope::ShaderParameter> m_inverseProjectionMatrix = nullptr ;
            std::shared_ptr<Hope::ShaderParameter> m_inverseModelViewMatrix = nullptr ;
            std::shared_ptr<Hope::ShaderParameter> m_inverseViewProjectionMatrix = nullptr ;
            std::shared_ptr<Hope::ShaderParameter> m_inverseMVPMatrix = nullptr ;
            std::shared_ptr<Hope::ShaderParameter> m_modelNormalMatrix = nullptr ;
            std::shared_ptr<Hope::ShaderParameter> m_modelViewNormalMatrix = nullptr ;
            std::shared_ptr<Hope::ShaderParameter> m_viewportMatrix = nullptr ;
            std::shared_ptr<Hope::ShaderParameter> m_inverseViewportMatrix = nullptr ;
            std::shared_ptr<Hope::ShaderParameter> m_aspectRatio = nullptr ;
            std::shared_ptr<Hope::ShaderParameter> m_time = nullptr ;
            std::shared_ptr<Hope::ShaderParameter> m_eyePosition = nullptr ;

            /**
             * Effect of the material.
             */
            RenderEffect m_effect ;

            /**
             * List of shader parameters.
             */
            std::set<std::shared_ptr<Hope::ShaderParameter>> m_shaderParams ;

        public:
            /**
             * Create a Material.
             */
            Material() ;

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
             * Get the shader parameters.
             */
            std::set<std::shared_ptr<Hope::ShaderParameter>> shaderParameters() const {
                return m_shaderParams ;
            }

        protected:
            /**
             * Add a shader parameter.
             * It is sent to the shader as a uniform value.
             * Some usual values are already sent to the shaders.
             */
            void addShaderParameter(const std::shared_ptr<Hope::ShaderParameter> param) ;

            /**
             * Remove a shader parameter.
             */
            void removeShaderParameter(const std::shared_ptr<Hope::ShaderParameter> param) ;

        private:
            /**
             * Set up the default parameters (for uniform values in shaders).
             * The values are updated just before the component accepts the
             * rendering visitor.
             * @see     accept(ISceneGraphVisitor* visitor)
             * @see     updateParameterValues()
             */
            void setupDefaultParameters() ;

            /**
             * Update the parameter values before the processing of the material
             * component.
             */
            void updateParameterValues(ISceneGraphVisitor* visitor) ;
    } ;
}

#endif
