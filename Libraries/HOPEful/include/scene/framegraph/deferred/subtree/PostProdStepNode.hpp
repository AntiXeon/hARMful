#ifndef __HOPE__POST_PROD_STEP_NODE__
#define __HOPE__POST_PROD_STEP_NODE__

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/framebuffers/Framebuffer.hpp>
    namespace API = Hope::GL ;
#endif

#include <scene/FrameGraphNode.hpp>
#include <vector>

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
            static const unsigned char PostProdRenderTargetOne = 2 ;
            static const unsigned char PostProdRenderTargetTwo = PostProdRenderTargetOne + 1 ;

        private:
            /**
             * Use two render targets that are swapped while post-prod effects
             * are applied (ping-pong).
             */
            int m_pingpongInputTarget = PostProdRenderTargetOne ;

            /**
             * Use two render targets that are swapped while post-prod effects
             * are applied (ping-pong).
             */
            int m_pingpongOutputTarget = PostProdRenderTargetTwo ;

            /**
             * Framebuffer containing the render targets in which the shading
             * result of deferred rendering has been performed, ambient
             * occlusion has (optionnaly) been computed, etc.
             */
            API::Framebuffer* m_shadingFBO = nullptr ;

            /**
             * Framebuffer in which the post-production rendering is output.
             */
            API::Framebuffer* m_outputFBO = nullptr ;

            /**
             * Root node for all post-prod effects.
             */
            FrameGraphNode* m_effectsRoot = nullptr ;

            /**
             * All the post-prod effect to apply.
             */
            std::vector<PostProdEffectNode*> m_effects ;

        public:
            /**
             * Create a new PostProdStepNode instance.
             * @param   shadingFBO  Framebuffer in which the shading result
             *                      of deferred rendering has been performed.
             * @param   outputFBO   Framebuffer in which the post-production
             *                      rendering is output.
             */
            PostProdStepNode(
                API::Framebuffer* shadingFBO,
                API::Framebuffer* outputFBO,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Add a post-prod effect.
             */
            void addEffect(PostProdEffectNode* node) ;

            /**
             * Remove a post-prod effect.
             * @warning     The node is only removed from the list. Its data are
             *              not destroyed though.
             */
            void removeEffect(PostProdEffectNode* node) ;
    } ;
}

#endif
