#ifndef __BANE_ENTITY__
#define __BANE_ENTITY__

#include <utils/IDObject.hpp>
#include <cstdint>
#include <mutex>
#include <unordered_set>
#include <stdexcept>
#include <string>

namespace Bane {
    /**
     * Obscur ID type of an Entity.
     */
    class Entity final : public Doom::IDObject {
        friend class EntityFactory ;

        private:
            /**
             * Create a new invalid Entity.
             */
            Entity(): Doom::IDObject() { }

            /**
             * Create a new Entity with a given ID.
             * Only the Entity classes must be able to create
             * an Entity.
             */
            Entity(const uint32_t id): Doom::IDObject(id) { }

        public:
            /**
             * Test if two Entity IDs are equal.
             */
            inline bool operator==(const Entity& other) const {
                return id() == other.id() ;
            }

            /**
             * Test if two Entity IDs are different.
             */
            inline bool operator!=(const Entity& other) const {
                return id() != other.id() ;
            }

            /**
             * Convert the current ID to string representation.
             */
            inline operator std::string() const {
                return "EntityID #" + std::to_string(id()) ;
            }
    } ;
}

#endif
