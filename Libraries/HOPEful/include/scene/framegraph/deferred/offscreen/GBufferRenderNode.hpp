#ifndef __HOPE__GBUFFER_RENDER__
#define __HOPE__GBUFFER_RENDER__

#include <utils/Platform.hpp>

#include <scene/framegraph/deferred/offscreen/base/FramebufferRenderNode.hpp>

namespace Hope {
    /**
     * Perform an off-screen render pass using a framebuffer.
     * It is dedicated for built-in materials that support deferred rendering.
     * It automatically sets up the render targets that are required for
     * deferred rendering.
     *
     * Here are the render targets to the framebuffer:
     * - RT0: albedo + metalness	(RGBA [RGB: albedo], [A: metalness])
     * - RT1: emissive + roughness  (RGBA [RGB: emissive], [A: roughness])
     * - RT2: AO    				(RGBA [R: AO], [GBA: unused])
     * - RT3: normal  				(ARGB2101010 [RGB: normal], [A: unused])
     * - Depth buffer
     */
    class GBufferRenderNode final : public FramebufferRenderNode {
        public:
            static const unsigned char AlbedoMetalnessRenderTarget = 0 ;
            static const unsigned char EmissiveRoughnessRenderTarget = 1 ;
            static const unsigned char AORenderTarget = 2 ;
            static const unsigned char NormalRenderTarget = 3 ;
			static const unsigned char DepthRenderTarget = 4 ;

        private:
            static const bool FollowWindowSize = true ;

        public:
            /**
             * Create a new GBufferRenderNode instance.
             * @param   size        Size of the framebuffer.
             */
            exported GBufferRenderNode(
                const Mind::Dimension2Di& size,
                FrameGraphNode* parent = nullptr
            ) ;

        protected:
            /**
             * Set up the attachments to the framebuffer.
             */
            exported void setup() override ;
    } ;
}

#endif
