#ifndef __HOPE__POST_PROD_EFFECT_NODE__
#define __HOPE__POST_PROD_EFFECT_NODE__

#include <utils/Platform.hpp>

#include <scene/framegraph/deferred/offscreen/OffscreenRenderingNode.hpp>
#include <scene/framegraph/deferred/offscreen/base/FramebufferRenderNode.hpp>

namespace Hope {
    class IFrameGraphVisitor ;

    /**
     * Framegraph node to compute a post-prod effect.
     */
    class PostProdEffectNode : public OffscreenRenderingNode {
        friend class PostProdStepNode ;

        private:
            /**
             * Default ID value when a PostProdEffectNode is not inserted into a
             * PostProdStepNode effects list.
             */
            static const short DefaultID = -1 ;

            /**
             * ID of the node when added to a PostProdStepNode.
             * If the node is not added to a PostProdStepNode, its ID is defined
             * to -1.
             */
            short m_id = DefaultID ;

            /**
             * Framebuffer node used as input to apply the effect on the texture
             * it contains.
             */
            FramebufferRenderNode* m_framebufferNode = nullptr ;

        public:
            /**
             * Create a new PostProdEffectNode instance.
             */
            exported PostProdEffectNode(
                std::unique_ptr<MaterialComponent> material,
                FramebufferRenderNode* framebufferNode
            ) ;

        private:
            /**
             * Set the ID of the node when added to a PostProdStepNode.
             */
            exported void setId(const short id) { m_id = id ; }

            /**
             * Get the ID of the node when added to a PostProdStepNode.
             */
            exported short id() const { return m_id ; }

        protected:
            /**
             * Blit framebuffers content (input and output) for the next process
             * on them.
             */
            exported void postAccept() override ;
    } ;
}

#endif
