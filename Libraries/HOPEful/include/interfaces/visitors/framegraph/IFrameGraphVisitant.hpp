#ifndef __HOPE__IFRAMEGRAPHVISITANT__
#define __HOPE__IFRAMEGRAPHVISITANT__

namespace Hope {
    class IFrameGraphVisitor ;

    /**
     * Interface for the objects that can be handled by an IFrameGraphVisitant.
     */
    class IFrameGraphVisitant {
        public:
            /**
             * Accept the visitor.
             */
            virtual void accept(IFrameGraphVisitor* visitor) = 0 ;
    } ;
}

#endif
