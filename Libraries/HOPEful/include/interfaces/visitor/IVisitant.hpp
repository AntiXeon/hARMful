#ifndef __HOPE__IVISITANT__
#define __HOPE__IVISITANT__

namespace Hope {
    class IVisitor ;

    /**
     * Interface for the objects that can be handled by an IVisitor.
     */
    class IVisitant {
        public:
            /**
             * Visit a camera component.
             */
            virtual void accept(IVisitor* component) = 0 ;
    } ;
}

#endif
