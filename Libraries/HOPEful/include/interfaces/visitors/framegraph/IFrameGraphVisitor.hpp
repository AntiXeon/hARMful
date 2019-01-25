#ifndef __HOPE__IFRAMEGRAPHVISITOR__
#define __HOPE__IFRAMEGRAPHVISITOR__

#include <scene/SceneTypes.hpp>
#include <HopeAPI.hpp>

#ifdef OGL
    namespace API = Hope::GL ;
#endif

namespace Hope {
    class API::ActiveCamera ;
    class API::FrustumCulling ;
    class API::Viewport ;

    /**
     * Interface for the Visitor design pattern for nodes of the frame graph.
     */
    class ISceneGraphVisitor {
        public:
            /**
             * Get the current frame ID while visiting.
             */
            virtual FrameID currentFrameID() const = 0 ;

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
