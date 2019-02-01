#ifndef __HOPE__RENDER_EFFECT__
#define __HOPE__RENDER_EFFECT__

#include <scene/framegraph/shading/ShaderParameter.hpp>
#include <scene/framegraph/shading/RenderTechnique.hpp>
#include <memory>
#include <set>

namespace Hope {
    /**
     * Shading effect.
     */
    class RenderEffect final {
        private:
            /**
             * List of shader parameters.
             */
            std::set<std::shared_ptr<Hope::ShaderParameter>> m_shaderParams ;

            /**
             * Available techniques in the effect.
             */
            std::set<std::shared_ptr<RenderTechnique>> m_techniques ;

        public:
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
             * Add a render technique.
             */
            void addTechnique(const std::shared_ptr<RenderTechnique> technique) ;

            /**
             * Remove a render technique.
             */
            void removeTechnique(const std::shared_ptr<RenderTechnique> technique) ;

            /**
             * Get the render techniques.
             */
            std::set<std::shared_ptr<RenderTechnique>> techniques() const {
                return m_techniques ;
            }
    } ;
}

#endif
