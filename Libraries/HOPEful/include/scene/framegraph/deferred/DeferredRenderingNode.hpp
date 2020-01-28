#ifndef __HOPE__DEFERRED_RENDERING__
#define __HOPE__DEFERRED_RENDERING__

#include <scene/FrameGraphNode.hpp>
#include <scene/framegraph/deferred/FramebufferRenderNode.hpp>

namespace Hope {
    class MaterialComponent ;

    /**
     * Framegraph node to perform deferred rendering.
     */
    class DeferredRenderingNode final : public FrameGraphNode {
        private:
            /**
             * Material bearing the shader program to use for performing
             * deferred rendering.
             */
            MaterialComponent* m_material = nullptr ;

        public:
            /**
             * Create a new DeferredRenderingNode instance.
             * @param   material    Material bearing the shader program to use
             *                      for performing deferred rendering.
             */
            DeferredRenderingNode(
                MaterialComponent* material,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Material bearing the shader program to use for performing
             * deferred rendering.
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
