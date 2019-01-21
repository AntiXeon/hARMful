#ifndef __HOPE__IVISITOR__
#define __HOPE__IVISITOR__

namespace Hope {
    class CameraComponent ;
    class MeshComponent ;

    /**
     * Interface for the Visitor design pattern.
     */
    class IVisitor {
        public:
            /**
             * Visit a camera component.
             */
            virtual void visit(CameraComponent* component) = 0 ;

            /**
             * Visit a mesh component.
             */
            virtual void visit(MeshComponent* component) = 0 ;
    } ;
}

#endif
