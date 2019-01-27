#ifndef __HOPE__IFRAMEGRAPHVISITOR__
#define __HOPE__IFRAMEGRAPHVISITOR__

#include <scene/SceneTypes.hpp>

namespace Hope {
    class ActiveCamera ;
    class FrustumCulling ;
    class Viewport ;

    /**
     * Interface for the Visitor design pattern for nodes of the frame graph.
     */
    class IFrameGraphVisitor {
        public:
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
    } ;
}

#endif
