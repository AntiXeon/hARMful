#ifndef __HOPE__IFRAMEGRAPHVISITOR__
#define __HOPE__IFRAMEGRAPHVISITOR__

#include <scene/SceneTypes.hpp>

namespace Hope {
    class FrameGraphNode ;
    class ActiveCamera ;
    class FrustumCulling ;
    class Viewport ;

    /**
     * Interface for the Visitor design pattern for nodes of the frame graph.
     */
    class IFrameGraphVisitor {
        public:
            /**
             * Create a new branch.
             */
            virtual void createNewBranch(FrameGraphNode* fgNode) = 0 ;

            /**
             * Visit a camera node.
             */
            virtual void visit(ActiveCamera* node) = 0 ;

            /**
             * Visit a frustum culling node.
             */
            virtual void visit(FrustumCulling* node) = 0 ;

            /**
             * Visit a viewport node.
             */
            virtual void visit(Viewport* node) = 0 ;

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
