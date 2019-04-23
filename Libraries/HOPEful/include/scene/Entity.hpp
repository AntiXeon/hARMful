#ifndef __HOPE__ENTITY__
#define __HOPE__ENTITY__

#include <scene/Node.hpp>
#include <scene/SceneTypes.hpp>
#include <scene/Transform.hpp>
#include <scene/SceneCache.hpp>
#include <memory>
#include <vector>

namespace Hope {

    class Component ;

    /**
     * An entity is a node that can bear components for many purpose: rendering,
     * sound, logic, etc.
     */
    class Entity: public Node {
        friend class Scene ;

        private:
            /**
             * If true, the Entity is processed for rendering its content.
             * Otherwise, it is just ignored and all its children as well.
             */
            bool m_isActive = true ;

            /**
             * Transform of the entity.
             */
            Transform m_transform ;

            /**
             * Components attached to the current entity.
             */
            std::vector<std::vector<Component*>> m_components ;

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
             * Remove the components of the provided type.
             * @param   type    Type of the components to remove.
             */
            void removeComponents(const ComponentType type) ;

            /**
             * Get a component of the wanted type.
             * @param   type    Type of the component to get.
             * @param   index   Index of the component in the list of components
             *                  of the wanted type.
             * @warning Check the index value with the amountComponents()
             *          method!
             */
            Component* component(
                const ComponentType type,
                const uint8_t index = 0
            ) const {
                return m_components[type][index] ;
            }

            /**
             * Get the amount of components for the wanted type.
             * @param   type    Type of the components.
             * @return  Amount of components of the wanted type that are
             *          attached to the current entity.
             */
            size_t amountComponents(const ComponentType type) const {
                return m_components[type].size() ;
            }

            /**
             * If true, the Entity is processed for rendering its content.
             * Otherwise, it is just ignored and all its children as well.
             */
            void setActive(const bool isActive) {
                m_isActive = isActive ;
            }

            /**
             * If true, the Entity is processed for rendering its content.
             * Otherwise, it is just ignored and all its children as well.
             */
            bool isActive() const {
                return m_isActive ;
            }

            /**
             * Get the transform of the entity.
             */
            const Transform& transform() const {
                return m_transform ;
            }

            Transform& transform() {
                return m_transform ;
            }

            /**
             * Get the list of the components attached to the current entity.
             */
            const std::vector<std::vector<Component*>>& components() const {
                return m_components ;
            }

            // Remove copy/move operations.
            Entity(const Entity& copied) = delete;
            Entity(Entity&& moved) = delete;
            Entity& operator=(const Entity& copied) = delete;
            Entity& operator=(Entity&& moved) = delete;
    } ;
}

#endif
