#ifndef __BANE_COMPONENTFACTORY__
#define __BANE_COMPONENTFACTORY__

#include <cassert>
#include <cstdint>
#include <memory>
#include <map>
#include <vector>
#include <stdexcept>
#include "Component.hpp"
#include "BANEStrings.hpp"

namespace Bane {
    /**
     * Factory to generate and destroy Component instances.
     */
    class ComponentFactory {
        private:
            /**
             * List of unique pointers on Components, for internal use only.
             */
            std::vector<std::unique_ptr<Component>> m_components ;

            /**
             * List of Components for easy sharing.
             */
            std::vector<Component*> m_componentsPtr ;

            /**
             * Association of an Entity value to its Components.
             */
            std::map<uint32_t, std::vector<Component*>> m_entityComponents ;

        public:
            /**
             * Create a new Component instance and store it in the
             * ComponentFactory.
             */
            virtual Component* create(const Entity& entity) = 0 ;

            /**
             * Delete the Component instances bearing the entity and remove them
             * from the ComponentFactory.
             */
            void remove(const Entity& entity) ;

            /**
             * Get the amount of Components for all Entities.
             */
            size_t countComponents() const {
                return m_components.size() ;
            }

            /**
             * Get all the Components from all Entities.
             */
            const std::vector<Component*>& components() const {
                return m_componentsPtr ;
            }

            /**
             * Get all the Components attached to an Entity.
             * @warning Never try to delete the pointers!
             */
            std::vector<Component*> components(const Entity& entity) const ;

        private:
            /**
             * Class invariant.
             */
            bool invariant() {
                return m_components.size() == m_componentsPtr.size() ;
            }
    } ;
}

#endif
