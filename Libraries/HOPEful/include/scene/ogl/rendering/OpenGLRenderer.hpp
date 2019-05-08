#ifndef __HOPE__GL_RENDERER__
#define __HOPE__GL_RENDERER__

#include <scene/ogl/rendering/RenderPass.hpp>
#include <scene/ogl/visitors/cache/GeometryData.hpp>

namespace Hope::GL {
    /**
     * Render the scene.
     */
    class OpenGLRenderer final {
        public:
            /**
             * Render the scene.
             */
            void render(std::vector<GeometryData>& dataList) ;

        private:
            /**
             * Use a material component.
             * @return  The capabilities of the render pass that is used in the
             *          material.
             */
            std::shared_ptr<API::RenderPass> useMaterial(const Hope::MaterialComponent* component) ;

            /**
             * Enable the capabilities of the render pass that is used.
             */
            void enableCapabilities(const std::shared_ptr<API::RenderPass>& renderPass) {
                auto capabilities = renderPass -> capabilities() ;
                for (const std::shared_ptr<Hope::GL::Capability>& capability : capabilities) {
                    capability -> apply() ;
                }
            }

            /**
             * Disable the capabilities of the render pass that is used.
             */
            void disableCapabilities(const std::shared_ptr<API::RenderPass>& renderPass) {
                auto capabilities = renderPass -> capabilities() ;
                for (const std::shared_ptr<Hope::GL::Capability>& capability : capabilities) {
                    capability -> remove() ;
                }
            }
    } ;
}

#endif
