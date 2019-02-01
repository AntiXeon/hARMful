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
             * Effect of the material.
             */
            RenderEffect m_effect ;

            /**
             * List of shader parameters.
             */
            std::set<std::shared_ptr<Hope::ShaderParameter>> m_shaderParams ;

        public:
            /**
             * Get the effect of the material.
             */
            const RenderEffect* effect() const {
                return &m_effect ;
            }

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

            /**
             * Get the shader parameters.
             */
            std::set<std::shared_ptr<Hope::ShaderParameter>> shaderParameters() const {
                return m_shaderParams ;
            }

            /**
             * To know if the component can be shared by several entities.
             * @return  true as it can be shared among several objects that are
             *          rendered the same way.
             */
            bool isShareable() const override {
                return true ;
            }
    } ;
}

#endif
