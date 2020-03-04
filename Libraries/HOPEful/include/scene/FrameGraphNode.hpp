#ifndef __HOPE__FRAMEGRAPH_NODE__
#define __HOPE__FRAMEGRAPH_NODE__

#include <utils/Platform.hpp>

#include <string>
#include <vector>
#include <interfaces/visitors/framegraph/IFrameGraphVisitant.hpp>

namespace Hope {

    class Entity ;

    /**
     * Base of nodes for the frame graph.
     * The frame graph can be used to make rendering passes, layers, post-prod
     * effects, etc.
     * The FrameGraphNode is usually not used as is in a frame graph as it does
     * nothing. However it can interesting to create a group of nodes in a
     * hierarchy.
     */
    class FrameGraphNode : public IFrameGraphVisitant {
        friend class Scene ;

        private:
            /**
             * Parent node.
             */
            FrameGraphNode* m_parent = nullptr ;

            /**
             * Children of the current node.
             */
            std::vector<FrameGraphNode*> m_children ;

            /**
             * Root entity of the scene.
             */
            Entity* m_sceneGraphRoot = nullptr ;

            /**
             * If true, the node allows the rendering of the framegraph branch
             * in which it is. If false, it prevents the rendering step.
             * The default value is true.
             */
            bool m_renderingStepEnabled = true ;

        public:
            /**
             * Create a new node instance.
             * @param   parent  Parent node of the new one.
             */
            exported FrameGraphNode(FrameGraphNode* parent = nullptr) ;

            /**
             * Destruction of the node instance.
             */
            exported virtual ~FrameGraphNode() ;

            /**
             * Accept the visitor.
             */
            exported void accept(IFrameGraphVisitor* visitor) override {
                specificAccept(visitor) ;
                generalAccept(visitor) ;
                postAccept() ;
            }

            /**
             * Set the parent of the current node.
             */
            exported void setParent(FrameGraphNode* parent) ;

            /**
             * Get the parent of the current node.
             */
            exported const FrameGraphNode* parent() const ;

            /**
             * Get the list of children.
             */
            exported const std::vector<FrameGraphNode*>& children() const ;

            /**
             * If true, the node allows the rendering of the framegraph branch
             * in which it is. If false, it prevents the rendering step.
             */
            exported bool renderingStepEnabled() const {
                return m_renderingStepEnabled ;
            }

            // Remove copy/move operations.
            FrameGraphNode(const FrameGraphNode& copied) = delete;
            FrameGraphNode(FrameGraphNode&& moved) = delete;
            FrameGraphNode& operator=(const FrameGraphNode& copied) = delete;
            FrameGraphNode& operator=(FrameGraphNode&& moved) = delete;

        protected:
            /**
             * If true, the node allows the rendering of the framegraph branch
             * in which it is. If false, it prevents the rendering step.
             */
            exported void setRenderingStepEnabled(const bool enabled) {
                m_renderingStepEnabled = enabled ;
            }

            /**
             * Specific implementation for visitors.
             */
            exported virtual void specificAccept(IFrameGraphVisitor* /*visitor*/) {}

            /**
             * Do something just after the node as been visited.
             */
            exported virtual void postAccept() {}

            /**
             * Root of the scene graph.
             */
            exported Entity* sceneRoot() ;

        private:
            /**
             * General method for accepting visitors.
             */
            exported void generalAccept(IFrameGraphVisitor* visitor) ;

            /**
             * Set the root entity of the scene graph.
             */
            exported void setSceneGraphRoot(Entity* root) ;

            /**
             * Add a child.
             * @param   newChild    Child node to add to the children list.
             * @return  true on success; false otherwise.
             */
            exported bool addChild(FrameGraphNode* newChild) ;

            /**
             * Remove a child.
             * @param   child       Child node to remove from the children list.
             * @return  true on success; false otherwise.
             */
            exported bool removeChild(FrameGraphNode* child) ;
    };
}

#endif
