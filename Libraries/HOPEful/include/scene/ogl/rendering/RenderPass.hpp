#ifndef __HOPE__GL_RENDER_PASS__
#define __HOPE__GL_RENDER_PASS__

#include <scene/framegraph/shading/FilterOption.hpp>
#include <scene/framegraph/shading/ShaderValue.hpp>
#include <scene/ogl/rendering/glsl/ShaderProgram.hpp>
#include <scene/ogl/rendering/capabilities/Capability.hpp>
#include <set>
#include <memory>

namespace Hope::GL {

    /**
     * Represents a shader program execution as a single render pass.
     */
    class RenderPass final {
        private:
            /**
             * List of the options.
             */
            std::set<std::shared_ptr<Hope::FilterOption>> m_options ;

            /**
             * List of shader parameters.
             */
            std::map<std::string, std::shared_ptr<Hope::ShaderAttribute>> m_shaderAttribs ;

            /**
             * List of graphics API capabilities.
             */
            std::set<std::shared_ptr<Hope::GL::Capability>> m_capabilities ;

            /**
             * The shader program that is executed in the current render pass.
             */
            std::shared_ptr<ShaderProgram> m_shaderProgram ;

        public:
            /**
             * Create a render pass.
             */
            RenderPass() ;

            /**
             * Add a filter option.
             * If a FilterOption is set in the framegraph branch and that at
             * least one of them matches in the current render pass, the entity
             * may be rendered. If no option matches in the current render pass,
             * the entity cannot be rendered (neither its children).
             *
             * If there is a FilterOption in the framegraph but no one in the
             * current render pass, the entity is discarded from rendering (and
             * its children as well).
             */
            void addFilterOption(const std::shared_ptr<Hope::FilterOption> option) ;

            /**
             * Remove a filter option.
             */
            void removeFilterOption(const std::shared_ptr<Hope::FilterOption> option) ;

            /**
             * Get the filter options.
             */
            std::set<std::shared_ptr<Hope::FilterOption>> filterOptions() const {
                return m_options ;
            }

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
            std::map<std::string, std::shared_ptr<Hope::ShaderAttribute>> shaderAttributes() const {
                return m_shaderAttribs ;
            }

            /**
             * Add a graphics API capability.
             */
            void addCapability(const std::shared_ptr<Hope::GL::Capability> capability) ;

            /**
             * Remove a graphics API capability.
             */
            void removeCapability(const std::shared_ptr<Hope::GL::Capability> capability) ;

            /**
             * Get the used capabilities.
             */
            std::set<std::shared_ptr<Hope::GL::Capability>> capabilities() const {
                return m_capabilities ;
            }

            /**
             * Get the shader program.
             */
            std::shared_ptr<ShaderProgram> shaderProgram() const {
                return m_shaderProgram ;
            }
    } ;
}

#endif
