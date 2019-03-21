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
             * List of shader attributes.
             */
            std::set<std::shared_ptr<Hope::ShaderAttribute>> m_shaderAttribs ;

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
             * Get the used API.
             */
            GraphicsAPI api() const {
                return m_apiParameters.api ;
            }

            /**
             * Get the major version of the used API.
             */
            int apiMajorVersion() const {
                return m_apiParameters.majorVersion ;
            }

            /**
             * Get the minor version of the used API.
             */
            int apiMinorVersion() const {
                return m_apiParameters.minorVersion ;
            }

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
            std::set<std::shared_ptr<Hope::ShaderAttribute>> shaderAttributes() const {
                return m_shaderAttribs ;
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
