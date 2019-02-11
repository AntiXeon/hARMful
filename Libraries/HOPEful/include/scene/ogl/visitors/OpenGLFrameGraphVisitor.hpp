#ifndef __HOPE__OPENGL_FRAMEGRAPH_VISITOR__
#define __HOPE__OPENGL_FRAMEGRAPH_VISITOR__

#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>
#include <geometry/dimensions/Dimension2Df.hpp>
#include <scene/ogl/visitors/OpenGLRenderVisitor.hpp>
#include <scene/framegraph/conditions/RenderConditionAggregator.hpp>
#include <scene/framegraph/ProcessedSceneNode.hpp>
#include <scene/Entity.hpp>
#include <algorithm>
#include <list>
#include <map>
#include <stack>
#include <cassert>

namespace Hope::GL {

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
            Mind::Dimension2Df m_windowSize ;

            /**
             * Visitor that can be used for some frame graph nodes when
             * rendering the scene.
             */
            std::map<Hope::FrameGraphNode*, OpenGLRenderVisitor> m_renderVisitors ;

            /**
             * The OpenGLRenderVisitor that is in use in the currently processed
             - framegraph branch.
             */
            OpenGLRenderVisitor* m_activeOpenGLRenderVisitor = nullptr ;

            /**
             * List to store the render conditions of every branch in the frame
             * graph.
             */
            std::list<Hope::RenderConditionAggregator> m_aggregators ;

            /**
             * Stack of the nodes that are processed.
             */
            std::stack<Hope::ProcessedSceneNode> m_processedNodes ;

        public:
            /**
             * Create an OpenGLFrameGraphVisitor instance.
             */
            OpenGLFrameGraphVisitor() ;

            /**
             * Create a new branch.
             */
            void createNewBranch(Hope::FrameGraphNode* fgNode) override ;

            /**
             * Set the root of the scene graph.
             */
            void setSceneRoot(Hope::Entity* root) ;

            /**
             * Set the window size.
             */
            void setWindowSize(const Mind::Dimension2Df& size) {
                m_windowSize = size ;

                if (m_windowSize.height() < 1.f) {
                    m_windowSize.setHeight(1.f) ;
                }

                m_hasWindowChanged = true ;
            }

            /**
             * Get the window size.
             */
            Mind::Dimension2Df windowSize() const {
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
            void visit(ActiveCamera* node) override ;

            /**
             * Visit a frustum culling node.
             */
            void visit(FrustumCulling* node) override ;

            /**
             * Visit a viewport node.
             */
            void visit(Viewport* node) override ;

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
            void backupRenderConditions() override ;

            /**
             * Prepare the next frame rendering.
             */
            void nextFrame() {
                m_hasWindowChanged = false ;
                m_activeOpenGLRenderVisitor -> startNewFrame() ;

                // Create a new aggregator for the new frame rendering.
                assert(m_aggregators.size() == 0) ;
                RenderConditionAggregator defaultAggregator ;
                m_aggregators.push_back(defaultAggregator) ;
            }

        private:
            /**
             * Render the provided entity. Recursive method.
             */
            void renderGraph() ;
    } ;
}

#endif
