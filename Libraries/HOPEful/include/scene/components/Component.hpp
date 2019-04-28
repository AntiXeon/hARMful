#ifndef __HOPE__COMPONENT__
#define __HOPE__COMPONENT__

#include <scene/SceneTypes.hpp>
#include <cstddef>
#include <vector>

namespace Hope {

    class Entity ;

    /**
     * Base class for all components that can be linked to entities.
     */
    class Component {
        friend class Entity ;

        private:
            /**
             * Entities the component is attached to.
             */
            std::vector<Entity*> m_entities ;

            /**
             * Type of the component.
             */
            ComponentType m_type ;

        public:
            /**
             * Create a new component instance.
             * @param   type    Type of the component.
             */
            Component(const ComponentType type) ;

            /**
             * Destruction of the component instance.
             */
            virtual ~Component() ;

            /**
             * To know if the component can be shared by several entities.
             * @return  true if the component can be shared by several entities;
             *          false otherwise.
             */
            virtual bool isShareable() const = 0 ;

            /**
             * To know if the component can be removed from its entity(-ies).
             * @return  true if the component can be removed; false otherwise.
             */
            virtual bool isRemovable() const = 0 ;

            /**
             * To know if several components of the current type can be beared
             * by a single entity.
             * @return  true if an entity can bear several component of the
             *          current type; false otherwise.
             */
            virtual bool isStackable() const = 0 ;

            /**
             * Get the type of the component.
             */
            ComponentType type() const ;

            /**
             * To know how many entities are attached to the current component.
             * @return  Amount of attached entities to the current component.
             */
            size_t amountAttachedEntities() const ;

            /**
             * Get the entities that bear the current component.
             * @param   entities    Output the entities.
             */
            void entities(std::vector<Entity*>& entities) const ;

            /**
             * Get the first entity bearing this component.
             */
            Entity* firstEntity() const ;

            // Remove copy/move operations.
            Component(const Component& copied) = delete;
            Component(Component&& moved) = delete;
            Component& operator=(const Component& copied) = delete;
            Component& operator=(Component&& moved) = delete;

        private:
            /**
             * Attach the component to the provided entity.
             * @param   entity  Entity to attach the component to.
             */
            void attach(Entity* entity) ;

            /**
             * Detach the component from its entity.
             * @param   entity  Entity to detach the component from.
             */
            void detach(Entity* entity) ;

        protected:
            /**
             * Action to performed when the component is attached to an
             * entity.
             * @param   entity  Entity to attach the component to.
             */
            virtual void onAttach(Entity* entity) ;

            /**
             * Action to perform when the component is detached from its entity.
             * @param   entity  Entity to detach the component from.
             */
            virtual void onDetach(Entity* entity) ;
    } ;
}

#endif
