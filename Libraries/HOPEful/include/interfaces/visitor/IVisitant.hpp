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
             * Accept the visitor.
             */
            virtual void accept(IVisitor* visitor) = 0 ;
    } ;
}

#endif
