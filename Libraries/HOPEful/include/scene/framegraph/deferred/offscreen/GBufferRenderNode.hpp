#ifndef __HOPE__GBUFFER_RENDER__
#define __HOPE__GBUFFER_RENDER__

#include <utils/Platform.hpp>

#include <scene/framegraph/deferred/offscreen/base/FramebufferMultisampleRenderNode.hpp>

namespace Hope {
    /**
     * Perform an off-screen render pass using a framebuffer.
     * It is dedicated for built-in materials that support deferred rendering.
     * It automatically sets up the render targets that are required for
     * deferred rendering.
     *
     * Here are the render targets to the framebuffer:
     * - RT0: albedo    (RGBA [RGB: color], [A: unused])
     * - RT1: specular  (RGBA [RGB: color], [A: roughness])
     * - RT2: normal    (ARGB2101010 [RGB: normal], [A: unused])
     * - RT3: position  (ARGB2101010 [RGB: position], [A: unused])
     * - Depth buffer
     */
    class GBufferRenderNode final : public FramebufferMultisampleRenderNode {
        public:
            static const unsigned char AlbedoRenderTarget = 0 ;
            static const unsigned char SpecularRenderTarget = 1 ;
            static const unsigned char NormalRenderTarget = 2 ;
            static const unsigned char DepthRenderTarget = 3 ;

        private:
            static const bool FollowWindowSize = false ;

        public:
            /**
             * Create a new GBufferRenderNode instance.
             * @param   size        Size of the framebuffer.
             */
            exported GBufferRenderNode(
                const Mind::Dimension2Di& size,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Get the multisampling quality (amount of samples).
             */
            exported int multisamplingQuality() const {
                return framebufferMultisample() -> samples() ;
            }

        protected:
            /**
             * Set up the attachments to the framebuffer.
             */
            void setup() override ;
    } ;
}

#endif
