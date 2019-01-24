#ifndef __HOPE__IVISITOR__
#define __HOPE__IVISITOR__

#include <scene/SceneTypes.hpp>

namespace Hope {
    class CameraComponent ;
    class MeshComponent ;
    class RenderConfiguration ;

    /**
     * Interface for the Visitor design pattern.
     */
    class IVisitor {
        public:
            /**
             * Get the current frame ID while visiting.
             */
            virtual FrameID currentFrameID() const = 0 ;

            /**
             * Visit a camera component.
             */
            virtual void visit(Hope::CameraComponent* component) = 0 ;

            /**
             * Visit a mesh component.
             */
            virtual void visit(Hope::MeshComponent* component) = 0 ;

            /**
             * Visit a render configuration component.
             */
            virtual void visit(Hope::RenderConfiguration* component) = 0 ;
    } ;
}

#endif
