#ifndef __HOPE__DEFERRED_RENDERING__
#define __HOPE__DEFERRED_RENDERING__

#include <scene/FrameGraphNode.hpp>
#include <scene/framegraph/deferred/FramebufferRenderNode.hpp>

namespace Hope {
    class MaterialComponent ;

    /**
     * Framegraph node dedicated to display only a quad to display the result of
     * deferred rendering from a framegraph.
     */
    class DeferredRenderingNode final : public FrameGraphNode {
        private:
            /**
             * Material bearing the shader program to use for performing the
             * deferred shading.
             */
            MaterialComponent* m_material = nullptr ;

        public:
            /**
             * Create a new DeferredRenderingNode instance.
             * @param   material    Material bearing the shader program to use
             *                      for performing the deferred shading.
             */
            DeferredRenderingNode(
                MaterialComponent* material,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Material bearing the shader program to use for performing the
             * deferred shading.
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
