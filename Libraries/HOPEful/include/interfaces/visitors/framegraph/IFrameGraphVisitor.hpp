#ifndef __HOPE__IFRAMEGRAPHVISITOR__
#define __HOPE__IFRAMEGRAPHVISITOR__

#include <utils/Platform.hpp>

#include <scene/SceneTypes.hpp>

namespace Hope {
    class Transform ;
    class ActiveCameraNode ;
    class ClearBuffersNode ;
    class FrustumCullingNode ;
    class DirectionalLightShadowNode ;
    class AbstractFramebufferRenderNode ;
    class LayerFramebufferRenderNode ;
    class OffscreenRenderingNode ;
    class ShadingStepNode ;
    class RenderPassSelectorNode ;
    class ViewportNode ;
    class MemoryBarrierNode ;
    class RenderCapabilityNode ;
    class EffectApplierNode ;
    class FogRenderNode ;

    /**
     * Interface for the Visitor design pattern for nodes of the frame graph.
     */
    class IFrameGraphVisitor {
        public:
            /**
             * Set the root of the scene graph.
             */
            exported virtual void setSceneRoot(Transform* root) = 0 ;

            /**
             * Visit a camera node.
             */
            exported virtual void visit(ActiveCameraNode* node) = 0 ;

            /**
             * Visit a clear buffers node.
             */
            exported virtual void visit(ClearBuffersNode* node) = 0 ;

            /**
             * Visit a frustum culling node.
             */
            exported virtual void visit(FrustumCullingNode* node) = 0 ;

            /**
             * Visit a light shadow render node.
             */
            exported virtual void visit(DirectionalLightShadowNode* node) = 0 ;

            /**
             * Visit an off-screen render node.
             */
            exported virtual void visit(AbstractFramebufferRenderNode* node) = 0 ;

            /**
             * Visit a layer off-screen render node.
             */
            exported virtual void visit(LayerFramebufferRenderNode* node) = 0 ;

            /**
             * Visit a node to perform deferred rendering.
             */
            exported virtual void visit(OffscreenRenderingNode* node) = 0 ;

            /**
             * Visit a node to perform deferred rendering for the shading step.
             */
            exported virtual void visit(ShadingStepNode* node) = 0 ;

            /**
             * Visit a render pass selector node.
             */
            exported virtual void visit(RenderPassSelectorNode* node) = 0 ;

            /**
             * Visit a viewport node.
             */
            exported virtual void visit(ViewportNode* node) = 0 ;

            /**
             * Visit a memory barrier node.
             */
            exported virtual void visit(MemoryBarrierNode* node) = 0 ;

            /**
             * Visit a capability node.
             */
            exported virtual void visit(RenderCapabilityNode* node) = 0 ;

            /**
             * Visit a node for applying render effect in the framegraph
             * branch(es).
             */
            exported virtual void visit(EffectApplierNode* node) = 0 ;

            /**
             * Visit a node for applying fog.
             */
            exported virtual void visit(FogRenderNode* node) = 0 ;

            /**
             * Perform the rendering of the framegraph tree branch that is
             * currently processed.
             */
            exported virtual void makeRender() = 0 ;

            /**
             * Save the render conditions when a there is a fork in the frame
             * graph. This allows to apply parent conditions to every branch
             * under the parent.
             */
            exported virtual void backupRenderConditions() = 0 ;
    } ;
}

#endif
