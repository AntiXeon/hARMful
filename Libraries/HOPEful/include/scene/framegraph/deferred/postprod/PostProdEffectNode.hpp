#ifndef __HOPE__POST_PROD_EFFECT_NODE__
#define __HOPE__POST_PROD_EFFECT_NODE__

#include <scene/framegraph/deferred/offscreen/OffscreenRenderingNode.hpp>
#include <scene/framegraph/deferred/offscreen/base/FramebufferRenderNode.hpp>

namespace Hope {
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
             * Render target containing the input picture to apply effect on.
             */
            int* m_inputRenderTarget = nullptr ;

            /**
             * Render target to which the effect result is written.
             */
            int* m_outputRenderTarget = nullptr ;

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
            FramebufferRenderNode* m_input = nullptr ;

        public:
            /**
             * Create a new PostProdEffectNode instance.
             */
            PostProdEffectNode(
                MaterialComponent* material,
                FramebufferRenderNode* input
            ) ;

            /**
             * Get the ID of the input render target.
             */
            int inputRenderTargetID() const {
                return m_inputRenderTarget ? *m_inputRenderTarget : -1 ;
            }

            /**
             * Get the ID of the output render target.
             */
            int outputRenderTargetID() const {
                return m_outputRenderTarget ? *m_outputRenderTarget : -1 ;
            }

        private:
            /**
             * Set the ID of the node when added to a PostProdStepNode.
             */
            void setId(const short id) { m_id = id ; }

            /**
             * Get the ID of the node when added to a PostProdStepNode.
             */
            short id() const { return m_id ; }

            /**
             * Set the render target ID pointers.
             */
            void setRenderTargetsIDs(int& input, int& output) {
                m_inputRenderTarget = &input ;
                m_outputRenderTarget = &output ;
            }

            /**
             * Unset the render target ID pointers.
             */
            void unsetRenderTargetsIDs() {
                m_inputRenderTarget = nullptr ;
                m_outputRenderTarget = nullptr ;
            }

        protected:
            /**
             * Accept the visitor.
             */
            // void specificAccept(IFrameGraphVisitor* visitor) ;
    } ;
}

#endif
