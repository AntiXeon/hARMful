#ifndef __HOPE__ENTITY__
#define __HOPE__ENTITY__

#include <scene/Node.hpp>
#include <scene/SceneTypes.hpp>
#include <memory>
#include <vector>

namespace Hope {

    class Component ;

    /**
     * An entity is a node that can bear components for many purpose: rendering,
     * sound, logic, etc.
     */
    class Entity: public Node {
        private:
            /**
             * Components attached to the current entity.
             */
            std::vector<Component*> m_components ;

        public:
            /**
             * Create a new entity instance.
             * @param   parent  Parent entity of the new one.
             */
            Entity(Entity* parent = nullptr) ;

            /**
             * Destruction of the entity instance.
             */
            virtual ~Entity() ;

            /**
             * Add a new component to the current entity.
             * If a component of the same type is already attached to the
             * entity, it is then replaced by this new one.
             * @warning Delete, if necessary, the previous component because it
             *          could lead to memory leaks!
             * @param   component   Component to add.
             */
            void addComponent(Component* component) ;

            /**
             * Remove a component from the current entity.
             * @param   component   Component to remove.
             */
            void removeComponent(Component* component) ;

            /**
             * Remove the component of the provided type.
             * @param   type    Type of the component to remove.
             */
            void removeComponent(const ComponentType type) ;

            /**
             * Get a component of the specified type.
             * @param   type    Type of the component to remove.
             * @return  The component of the wanted type if found; nullptr
                        otherwise.
             */
            Component* component(const ComponentType type) const ;

            /**
             * Get the list of the components attached to the current entity.
             */
            const std::vector<Component*>& components() const ;

            // Remove copy/move operations.
            Entity(const Entity& copied) = delete;
            Entity(Entity&& moved) = delete;
            Entity& operator=(const Entity& copied) = delete;
            Entity& operator=(Entity&& moved) = delete;

        private:
            /**
             * Find the position of the component of given type.
             * @param   type    Type of the component to find the position in
             *                  the list of components.
             * @return  The iterator at the position of the wanted component;
             *          end iterator if not found.
             */
            std::vector<Component*>::iterator find(const ComponentType type) ;
    } ;
}

#endif
