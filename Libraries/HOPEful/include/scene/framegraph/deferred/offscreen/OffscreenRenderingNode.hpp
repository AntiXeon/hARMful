#ifndef __HOPE__OFFSCREEN_RENDERING__
#define __HOPE__OFFSCREEN_RENDERING__

#include <utils/Platform.hpp>

#include <scene/FrameGraphNode.hpp>
#include <scene/framegraph/deferred/offscreen/OffscreenRenderingNode.hpp>
#include <scene/components/materials/MaterialComponent.hpp>
#include <memory>

namespace Hope {
    /**
     * Framegraph node to perform offscreen rendering.
     */
    class OffscreenRenderingNode : public FrameGraphNode {
        private:
            /**
             * Material bearing the shader program to use for performing the
             * rendering.
             */
            std::unique_ptr<MaterialComponent> m_material = nullptr ;

        public:
            /**
             * Create a new OffscreenRenderingNode instance.
             * @param   material    Material bearing the shader program to use
             *                      for performing the rendering.
             */
            exported OffscreenRenderingNode(
                std::unique_ptr<MaterialComponent> material,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Material bearing the shader program to use for performing the
             * rendering.
             */
            exported MaterialComponent* material() const {
                return m_material.get() ;
            }

        protected:
            /**
             * Accept the visitor.
             */
            exported void specificAccept(IFrameGraphVisitor* visitor) ;
    } ;
}

#endif
