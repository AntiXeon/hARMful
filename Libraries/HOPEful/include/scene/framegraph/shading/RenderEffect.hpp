#ifndef __HOPE__RENDER_EFFECT__
#define __HOPE__RENDER_EFFECT__

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/RenderPass.hpp>
    namespace API = Hope::GL ;
#endif

#include <map>
#include <memory>
#include <set>
#include <string>

namespace Hope {
    /**
     * Shading effect.
     */
    class RenderEffect final {
        private:
            /**
             * List of shader parameters.
             */
            std::set<std::shared_ptr<API::RenderPass>> m_renderPasses ;

        public:
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
