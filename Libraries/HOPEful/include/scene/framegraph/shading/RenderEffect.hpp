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
            std::map<RenderPassID, std::shared_ptr<API::RenderPass>> m_renderPasses ;

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
             * Check if the render effect has a render pass corresponding the
             * provided ID.
             */
            bool hasRenderPass(const RenderPassID passID) const {
                return (m_renderPasses.count(passID) == 1) ;
            }

            /**
             * Get a render pass.
             * @return  The render pass having the provided ID if available;
             *          nullptr otherwise.
             */
            std::shared_ptr<API::RenderPass> renderPass(const RenderPassID passID) const {
                if (hasRenderPass(passID)) {
                    return m_renderPasses.at(passID) ;
                }

                return nullptr ;
            }
    } ;
}

#endif
