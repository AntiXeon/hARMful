#ifndef __HOPE__POST_PROD_STEP_NODE__
#define __HOPE__POST_PROD_STEP_NODE__

#include <utils/Platform.hpp>

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/framebuffers/Framebuffer.hpp>
    namespace API = Hope::GL ;
#endif

#include <scene/FrameGraphNode.hpp>
#include <memory>
#include <unordered_set>

namespace Hope {
    class PostProdEffectNode ;

    /**
     * Framegraph node that is used to apply post-prod effects.
     */
    class PostProdStepNode final : public FrameGraphNode {
        public:
            /**
             * Use two render targets that are swapped while post-prod effects
             * are applied (ping-pong).
             */
            static const unsigned char PostProdRenderTarget = 2 ;

        private:
            /**
             * Framebuffer containing the render targets in which the shading
             * result of deferred rendering has been performed, ambient
             * occlusion has (optionnaly) been computed, etc.
             */
            API::Framebuffer* m_framebuffer = nullptr ;

            /**
             * Root node for all post-prod effects.
             */
            std::unique_ptr<FrameGraphNode> m_effectsRoot = nullptr ;

            /**
             * All the post-prod effect to apply.
             */
            std::unordered_set<PostProdEffectNode*> m_effects ;

        public:
            /**
             * Create a new PostProdStepNode instance.
             * @param   framebuffer Framebuffer containing the render targets in
             *                      which the shading result of deferred
             *                      rendering has been performed, ambient
             *                      occlusion has (optionnaly) been computed,
             *                      etc.
             */
            exported PostProdStepNode(
                API::Framebuffer* framebuffer,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Add a post-prod effect.
             */
            exported void addEffect(PostProdEffectNode* node) ;

            /**
             * Remove a post-prod effect.
             * @warning     The node is only removed from the list. Its data are
             *              not destroyed though.
             */
            exported void removeEffect(PostProdEffectNode* node) ;

        protected:
            /**
             * Accept the visitor.
             */
            void specificAccept(IFrameGraphVisitor*) ;
    } ;
}

#endif
