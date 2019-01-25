#ifndef __HOPE__IFRAMEGRAPHVISITOR__
#define __HOPE__IFRAMEGRAPHVISITOR__

#include <scene/SceneTypes.hpp>
#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/framegraph/ActiveCamera.hpp>
    #include <scene/ogl/framegraph/FrustumCulling.hpp>
    #include <scene/ogl/framegraph/Viewport.hpp>
#endif

namespace Hope {
    /**
     * Interface for the Visitor design pattern for nodes of the frame graph.
     */
    class IFrameGraphVisitor {
        public:
            /**
             * Visit a camera node.
             */
            virtual void visit(API::ActiveCamera* node) = 0 ;

            /**
             * Visit a frustum culling node.
             */
            virtual void visit(API::FrustumCulling* node) = 0 ;

            /**
             * Visit a viewport node.
             */
            virtual void visit(API::Viewport* node) = 0 ;
    } ;
}

#endif
