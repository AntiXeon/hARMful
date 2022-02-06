#ifndef __BANE_ENTITYFACTORY__
#define __BANE_ENTITYFACTORY__

#include <cstdint>
#include <unordered_set>
#include "Entity.hpp"

namespace Bane {
    /**
     * Factory to generate and destroy Entity instances.
     */
    class EntityFactory final {
        private:
            /**
             * List if the Entity values created by this factory.
             */
            std::unordered_set<uint32_t> m_entities ;

        public:
            /**
             * Create a new Entity instance and store it in the EntityFactory.
             * @return The newly created Entity.
             */
            Entity create() ;

            /**
             * Delete an Entity instance and remove it from the EntityFactory.
             * @param entity The Entity to delete.
             */
            void remove(Entity& entity) ;

            /**
             * Check if the given Entity exists.
             * @param entity Entity to test the existence.
             * @return true if the Entity value is stored; false otherwise.
             */
            inline bool contains(const Entity& entity) {
                return m_entities.count(entity.id()) != 0 ;
            }
    } ;
}

#endif
