#ifndef __HOPE__IFRAMEGRAPHVISITOR__
#define __HOPE__IFRAMEGRAPHVISITOR__

#include <scene/SceneTypes.hpp>

namespace Hope {
    class ActiveCameraNode ;
    class ClearBuffersNode ;
    class FrustumCullingNode ;
    class DirectionalLightShadowNode ;
    class FramebufferRenderNode ;
    class LayerFramebufferRenderNode ;
    class DeferredRenderingNode ;
    class FinalStepRenderingNode ;
    class RenderPassSelectorNode ;
    class ViewportNode ;
    class MemoryBarrierNode ;
    class RenderCapabilityNode ;
    class EffectApplierNode ;

    /**
     * Interface for the Visitor design pattern for nodes of the frame graph.
     */
    class IFrameGraphVisitor {
        public:
            /**
             * Visit a camera node.
             */
            virtual void visit(ActiveCameraNode* node) = 0 ;

            /**
             * Visit a clear buffers node.
             */
            virtual void visit(ClearBuffersNode* node) = 0 ;

            /**
             * Visit a frustum culling node.
             */
            virtual void visit(FrustumCullingNode* node) = 0 ;

            /**
             * Visit a light shadow render node.
             */
            virtual void visit(DirectionalLightShadowNode* node) = 0 ;

            /**
             * Visit an off-screen render node.
             */
            virtual void visit(FramebufferRenderNode* node) = 0 ;

            /**
             * Visit a layer off-screen render node.
             */
            virtual void visit(LayerFramebufferRenderNode* node) = 0 ;

            /**
             * Visit a node to perform deferred rendering.
             */
            virtual void visit(DeferredRenderingNode* node) = 0 ;

            /**
             * Visit a node to perform deferred rendering for the final step.
             */
            virtual void visit(FinalStepRenderingNode* node) = 0 ;

            /**
             * Visit a render pass selector node.
             */
            virtual void visit(RenderPassSelectorNode* node) = 0 ;

            /**
             * Visit a viewport node.
             */
            virtual void visit(ViewportNode* node) = 0 ;

            /**
             * Visit a memory barrier node.
             */
            virtual void visit(MemoryBarrierNode* node) = 0 ;

            /**
             * Visit a capability node.
             */
            virtual void visit(RenderCapabilityNode* node) = 0 ;

            /**
             * Visit a node for applying render effect in the framegraph
             * branch(es).
             */
            virtual void visit(EffectApplierNode* node) = 0 ;

            /**
             * Perform the rendering of the framegraph tree branch that is
             * currently processed.
             */
            virtual void makeRender() = 0 ;

            /**
             * Save the render conditions when a there is a fork in the frame
             * graph. This allows to apply parent conditions to every branch
             * under the parent.
             */
            virtual void backupRenderConditions() = 0 ;
    } ;
}

#endif
