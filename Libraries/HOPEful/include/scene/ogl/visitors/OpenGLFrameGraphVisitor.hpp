#ifndef __HOPE__OPENGL_FRAMEGRAPH_VISITOR__
#define __HOPE__OPENGL_FRAMEGRAPH_VISITOR__

#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>
#include <geometry/dimensions/Dimension2Df.hpp>
#include <geometry/dimensions/Dimension2Di.hpp>
#include <scene/ogl/rendering/OpenGLRenderer.hpp>
#include <scene/framegraph/ProcessedSceneNode.hpp>
#include <scene/framegraph/FrameGraphBranchState.hpp>
#include <scene/framegraph/conditions/RenderConditionAggregator.hpp>
#include <scene/framegraph/cache/ProjectionData.hpp>
#include <scene/framegraph/deferred/framebuffers/base/FramebufferRenderNode.hpp>
#include <scene/framegraph/deferred/effects/EffectData.hpp>
#include <scene/Entity.hpp>
#include <algorithm>
#include <cassert>
#include <list>
#include <map>
#include <stack>
#include <vector>

namespace Hope::GL {
    class UBOSharedData ;

    /**
     * Visitor for processing frame graph nodes.
     */
    class OpenGLFrameGraphVisitor final : public IFrameGraphVisitor {
        private:
            /**
             * Root of the scene graph. May be used by some frame graph nodes
             * to render the scene.
             */
            Hope::Entity* m_sceneRoot = nullptr ;

            /**
             * To know if the window has changed since the last run.
             */
            bool m_hasWindowChanged = true ;

            /**
             * Size of the window.
             */
            Mind::Dimension2Di m_windowSize ;

            /**
             * Data required to correctly compute projection on render step.
             */
            Hope::ProjectionData m_projectionData ;

            /**
             * Renderer to render the scene.
             */
            OpenGLRenderer m_renderer ;

            /**
             * List to store the render conditions of every branch in the frame
             * graph.
             */
            std::list<FrameGraphBranchState> m_aggregators ;

            /**
             * Stack of the nodes that are processed.
             */
            std::stack<Hope::ProcessedSceneNode> m_processedNodes ;

            /**
             * List of effects to apply when rendering the final step of
             * deferred rendering. Some effects are processed in a previous
             * render step and are finally applied to the final render (shadows,
             * ...).
             */
            std::vector<Hope::EffectData*> m_globalEffects ;

        public:
            /**
             * Create an OpenGLFrameGraphVisitor instance.
             */
            OpenGLFrameGraphVisitor() ;

            /**
             * Set the root of the scene graph.
             */
            void setSceneRoot(Hope::Entity* root) ;

            /**
             * Set the window size.
             */
            void setWindowSize(const Mind::Dimension2Df& size) {
                m_windowSize = Mind::Dimension2Di(size.width(), size.height()) ;

                if (m_windowSize.height() < 1) {
                    m_windowSize.setHeight(1) ;
                }

                m_hasWindowChanged = true ;
            }

            /**
             * Get the window size.
             */
            Mind::Dimension2Di windowSize() const {
                return m_windowSize ;
            }

            /**
             * To know if the window has changed since the last frame.
             * If false, many process of the frame graph may be avoided.
             */
            bool hasWindowChanged() const {
                return m_hasWindowChanged ;
            }

            /**
             * Visit a camera node.
             */
            void visit(ActiveCameraNode* node) override ;

            /**
             * Visit a clear buffers node.
             */
            void visit(ClearBuffersNode* node) override ;

            /**
             * Visit a frustum culling node.
             */
            void visit(FrustumCullingNode* node) override ;

            /**
             * Visit a light shadow render node.
             */
            void visit(DirectionalLightShadowNode* node) override ;

            /**
             * Visit an off-screen render node.
             */
            void visit(AbstractFramebufferRenderNode* node) override ;

            /**
             * Visit a layer off-screen render node.
             */
            void visit(LayerFramebufferRenderNode* node) override ;

            /**
             * Visit a node to perform deferred rendering.
             */
            void visit(OffscreenRenderingNode* node) override ;

            /**
             * Visit a node to perform deferred rendering for the final step.
             */
            void visit(FinalStepRenderingNode* node) override ;

            /**
             * Visit a render pass selector node.
             */
            void visit(RenderPassSelectorNode* node) override ;

            /**
             * Visit a viewport node.
             */
            void visit(ViewportNode* node) override ;

            /**
             * Visit a memory barrier node.
             */
            void visit(MemoryBarrierNode* node) override ;

            /**
             * Visit a capability node.
             */
            void visit(RenderCapabilityNode* node) override ;

            /**
             * Visit a node for applying render effect in the framegraph
             * branch(es).
             */
            void visit(EffectApplierNode* node) override ;

            /**
             * Visit a node for applying fog.
             */
            void visit(FogRenderNode* node) override ;

            /**
             * Perform the rendering of the framegraph tree branch that is
             * currently processed.
             */
            void makeRender() override ;

            /**
             * Save the render conditions when a there is a fork in the frame
             * graph. This allows to apply parent conditions to every branch
             * under the parent.
             */
            void backupRenderConditions() override {
                // Copy and push back that copy in the list. So that, the copy can be
                // modified while the original still the same and can be reused for the
                // other branch of the frame graph.
                m_aggregators.push_back(m_aggregators.back()) ;
            }

            /**
             * Prepare the next frame rendering.
             */
            void nextFrame() {
                m_hasWindowChanged = false ;

                // Create a new aggregator for the new frame rendering.
                assert(m_aggregators.size() == 0) ;
                m_aggregators.push_back(FrameGraphBranchState()) ;

                // Clear the global effects for the next frame.
                m_globalEffects.clear() ;
            }


            // Remove copy/move operations.
            virtual ~OpenGLFrameGraphVisitor() = default ;
            OpenGLFrameGraphVisitor(const OpenGLFrameGraphVisitor& copied) = delete;
            OpenGLFrameGraphVisitor(OpenGLFrameGraphVisitor&& moved) = delete;
            OpenGLFrameGraphVisitor& operator=(const OpenGLFrameGraphVisitor& copied) = delete;
            OpenGLFrameGraphVisitor& operator=(OpenGLFrameGraphVisitor&& moved) = delete;

        private:
            /**
             * Parse the render graph to get all the components of the scene
             * that need to be parsed and processed as an all.
             */
            void parseSceneGraph() ;

            /**
             * Update the camera settings (clear color, uniforms, etc).
             */
            void updateCameraSettings() ;
    } ;
}

#endif
