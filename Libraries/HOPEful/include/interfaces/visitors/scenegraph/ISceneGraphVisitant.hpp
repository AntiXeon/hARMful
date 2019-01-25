#ifndef __HOPE__ISCENEGRAPHVISITANT__
#define __HOPE__ISCENEGRAPHVISITANT__

namespace Hope {
    class ISceneGraphVisitor ;

    /**
     * Interface for the objects that can be handled by an ISceneGraphVisitor.
     */
    class ISceneGraphVisitant {
        public:
            /**
             * Accept the visitor.
             */
            virtual void accept(ISceneGraphVisitor* visitor) = 0 ;
    } ;
}

#endif
