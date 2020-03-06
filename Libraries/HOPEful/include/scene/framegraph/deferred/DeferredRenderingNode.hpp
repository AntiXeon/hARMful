#ifndef __HOPE__DEFERRED_RENDERING__
#define __HOPE__DEFERRED_RENDERING__

#include <utils/Platform.hpp>

#include <scene/framegraph/deferred/offscreen/OffscreenRenderingNode.hpp>
#include <scene/framegraph/deferred/effects/ao/SSAORenderNode.hpp>
#include <scene/framegraph/deferred/offscreen/GBufferRenderNode.hpp>
#include <scene/framegraph/deferred/offscreen/base/FramebufferRenderNode.hpp>
#include <scene/framegraph/deferred/subtree/ShadingStepNode.hpp>
#include <scene/framegraph/deferred/subtree/PostProdStepNode.hpp>
#include <scene/framegraph/deferred/subtree/DisplayStepNode.hpp>
#include <scene/framegraph/deferred/postprod/AOApplyEffectNode.hpp>
#include <memory>

namespace Hope {
    /**
     * Framegraph node to perform deferred rendering.
     * It uses a framebuffer containing several temporary results for applying
     * the different steps of the deferred rendering.
     * It does not use multisampling textures but can receive
     * precomputed multisampled pictures.
     */
    class DeferredRenderingNode final : public FrameGraphNode {
        private:
            static const bool FollowWindowSize = true ;

            /**
             * G-Buffer used for the rendering (shading, SSAO, ...).
             */
            GBufferRenderNode* m_gBuffer = nullptr ;

            /**
             * Compute SSAO from the G-Buffer content (depth, normals).
             */
            std::unique_ptr<SSAORenderNode> m_computeSSAONode = nullptr ;

            /**
             * Node to apply ambient occlusion on shaded result.
             */
            std::unique_ptr<AOApplyEffectNode> m_aoApplyNode = nullptr ;

            /**
             * Framebuffer node in which the deferred rendering is performed.
             */
            std::unique_ptr<FramebufferRenderNode> m_framebufferNode = nullptr ;

            /**
             * Compute the shading from a G-Buffer node. It applies
             * multisampling as well in rendering so that the resulting texture
             * does not need to enable multisample.
             */
            std::unique_ptr<ShadingStepNode> m_shadingNode = nullptr ;

            /**
             * Apply post-prod effects.
             */
            std::unique_ptr<PostProdStepNode> m_postProdNode = nullptr ;

            /**
             * Node to display the result on screen.
             */
            std::unique_ptr<DisplayStepNode> m_displayStepNode = nullptr ;

        public:
            /**
             * Create a new DeferredRenderingNode instance.
             * @param   gBuffer     G-Buffer used for the rendering (shading,
             *                      SSAO, ...).
             * @param   windowSize  If true, the size of the framebuffer follows
             *                      the size of the window. If false, the size
             *                      of the framebuffer is fixed.
             */
            exported DeferredRenderingNode(
                GBufferRenderNode* gBuffer,
                FrameGraphNode* parent = nullptr
            ) ;

        private:
            /**
             * Set up the framebuffer for deferred rendering.
             */
            exported void setupFramebuffer() ;
    } ;
}

#endif
