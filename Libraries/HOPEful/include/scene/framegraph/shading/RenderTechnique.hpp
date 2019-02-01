#ifndef __HOPE__RENDER_TECHNIQUE__
#define __HOPE__RENDER_TECHNIQUE__

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/RenderPass.hpp>
    namespace API = Hope::GL ;
#endif

namespace Hope {
    /**
     * Define the render technique that is used to render an object.
     * Select the graphics API and its version to do so.
     */
    class RenderTechnique final {
        public:
            /**
             * Available graphics API for rendering.
             */
            enum class GraphicsAPI : char {
                OpenGL
                // Vulkan,
                // DirectX
            } ;

        private:
            struct GraphicsAPIParameters {
                /**
                 * The graphicsAPI that is used to render the scene.
                 */
                GraphicsAPI api = RenderTechnique::GraphicsAPI::OpenGL ;

                /**
                 * Major version number.
                 */
                int majorVersion ;

                /**
                 * Minor version number.
                 */
                int minorVersion ;

            } ;

            /**
             * Parameter of the grahics API.
             */
            GraphicsAPIParameters m_apiParameters ;

            /**
             * List of the options.
             */
            std::set<std::shared_ptr<Hope::FilterOption>> m_options ;

            /**
             * List of shader parameters.
             */
            std::set<std::shared_ptr<Hope::ShaderParameter>> m_shaderParams ;

            /**
             * List of shader parameters.
             */
            std::set<std::shared_ptr<API::RenderPass>> m_renderPasses ;

        public:
            /**
             * Set the graphics API.
             */
            void setAPI(
                const GraphicsAPI api,
                const int majorVersion,
                const int minorVersion
            ) ;

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
             * Add a render pass.
             */
            void addRenderPass(const std::shared_ptr<API::RenderPass> pass) ;

            /**
             * Remove a render pass.
             */
            void removeRenderPass(const std::shared_ptr<API::RenderPass> pass) ;

            /**
             * Get the render passes.
             */
            std::set<std::shared_ptr<API::RenderPass>> renderPasses() const {
                return m_renderPasses ;
            }
    } ;
}

#endif
