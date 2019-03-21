#ifndef __HOPE__RENDER_EFFECT__
#define __HOPE__RENDER_EFFECT__

#include <scene/framegraph/shading/ShaderValue.hpp>
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
             * List of shader attributes.
             */
            std::set<std::shared_ptr<Hope::ShaderAttribute>> m_shaderAttribs ;

            /**
             * Available techniques in the effect.
             */
            std::set<std::shared_ptr<RenderTechnique>> m_techniques ;

        public:
            /**
             * Add a shader attribute.
             * It is sent to the shader as a uniform value.
             * Some usual values are already sent to the shaders.
             */
            void addShaderAttribute(const std::shared_ptr<Hope::ShaderAttribute> attrib) ;

            /**
             * Remove a shader attribute.
             */
            void removeShaderAttribute(const std::shared_ptr<Hope::ShaderAttribute> attrib) ;

            /**
             * Get the shader attributes.
             */
            std::set<std::shared_ptr<Hope::ShaderAttribute>> shaderAttributes() const {
                return m_shaderAttribs ;
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
