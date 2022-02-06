#ifndef __BANE_SYSTEMPROCESSING__
#define __BANE_SYSTEMPROCESSING__

#include <functional>
#include <list>
#include <map>
#include "ecs/component/ComponentFactory.hpp"
#include "ecs/entity/Entity.hpp"

namespace Bane {
    class System ;

    /**
     * Class for processing the components of a System.
     * Components (and factory) are hard-defined in inherited classes to avoid
     * template-related issues in architecture. BTW, there is no need to have
     * them right here so this is not a big deal.
     */
    class SystemProcessing {
        public:
            /**
             * Do something when an entity is removed.
             */
            virtual void onDelete([[maybe_unused]] Entity* entity) {}

            /**
             * Perform the Components processing.
             */
            virtual std::list<Entity> run(
                const std::map<std::string, System*> linkedSystems,
                const uint32_t fromIndex,
                const uint32_t toIndex
            ) = 0;
    } ;
}

#endif
