#ifndef __HOPE__RENDER_CONDITION__
#define __HOPE__RENDER_CONDITION__

#include <utils/Platform.hpp>

#include <scene/Entity.hpp>

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
            exported virtual bool check(const Entity* entity) const {
                return entity -> isActive() ;
            }
    } ;
}

#endif
