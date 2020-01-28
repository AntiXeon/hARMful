#ifndef __HOPE__OFFSCREEN_RENDERING__
#define __HOPE__OFFSCREEN_RENDERING__

#include <scene/FrameGraphNode.hpp>
#include <scene/framegraph/deferred/offscreen/base/FramebufferRenderNode.hpp>

namespace Hope {
    class MaterialComponent ;

    /**
     * Framegraph node to perform offscreen rendering.
     */
    class OffscreenRenderingNode final : public FrameGraphNode {
        private:
            /**
             * Material bearing the shader program to use for performing the
             * rendering.
             */
            MaterialComponent* m_material = nullptr ;

        public:
            /**
             * Create a new OffscreenRenderingNode instance.
             * @param   material    Material bearing the shader program to use
             *                      for performing the rendering.
             */
            OffscreenRenderingNode(
                MaterialComponent* material,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Material bearing the shader program to use for performing the
             * rendering.
             */
            MaterialComponent* material() const {
                return m_material ;
            }

        protected:
            /**
             * Accept the visitor.
             */
            void specificAccept(IFrameGraphVisitor* visitor) ;
    } ;
}

#endif
