#ifndef __HOPE__RENDER_CONDITION__
#define __HOPE__RENDER_CONDITION__

namespace Hope {
    /**
     * Render condition.
     */
    class RenderCondition {
        public:
            /**
             * Check if the condition is respected for the provided entity of
             * the scene graph.
             */
            virtual bool check(const Entity* entity) = 0 ;
    } ;
}

#endif
