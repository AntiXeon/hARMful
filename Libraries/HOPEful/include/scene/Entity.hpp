#ifndef __HOPE__ENTITY__
#define __HOPE__ENTITY__

#include <utils/Platform.hpp>

#include <scene/SceneTypes.hpp>
#include <memory>
#include <vector>

namespace Hope {

    class Component ;
	class Transform ;

    /**
     * An entity can bear components for many purpose: rendering, sound, logic,
	 * etc.
     */
    class Entity final {
        friend class Scene ;

        private:
            /**
             * If true, the Entity is processed for rendering its content.
             * Otherwise, it is just ignored and all its children as well.
             */
            bool m_isActive = true ;

            /**
             * If true, the Entity can be edited (add/remove Component).
             */
            bool m_isEditable = true ;

            /**
             * If locked, the entity cannot be modified while the application is
             * running. It is useful for static objects in the scene as it
             * increases performances.
             * A components cannot be added or removeed once the application is
             * running.
             */
            bool m_isLocked = false ;

            /**
             * Components attached to the current entity.
             */
            std::vector<std::vector<Component*>> m_components ;

			/**
			 * Link to the transform of the entity.
			 */
			Transform* m_transform = nullptr ;

        public:
            /**
             * Create a new entity instance.
             * @param   transform	Transform of the entity.
             */
            exported Entity(Transform* transform) ;

            /**
             * Destruction of the entity instance.
             */
            exported ~Entity() ;

            /**
             * Add a new component to the current entity.
             * If a component of the same type is already attached to the
             * entity, it is then replaced by this new one.
             * @warning Delete, if necessary, the previous component because it
             *          could lead to memory leaks!
             * @param   component   Component to add.
             * @return  Index of component in the list of its type.
             *          0xFFFFFFFF if the component has not been added.
             */
            exported int32_t addComponent(Component* component) ;

            /**
             * Remove a component from the current entity.
             * @param   component   Component to remove.
             */
            exported void removeComponent(Component* component) ;

            /**
             * Remove a component from the current entity.
             * @param   type    Type of the component to remove.
             * @param   index   Index of the component to remove.
             */
            exported void removeComponent(const ComponentType type, const uint32_t index) {
                Component* toRemove = component(type, index) ;
                removeComponent(toRemove) ;
            }

            /**
             * Remove the components of the provided type.
             * @param   type    Type of the components to remove.
             */
            exported void removeComponents(const ComponentType type) ;

            /**
             * Get a component of the wanted type.
             * @param   type    Type of the component to get.
             * @param   index   Index of the component in the list of components
             *                  of the wanted type.
             * @warning Check the index value with the amountComponents()
             *          method!
             */
            exported Component* component(
                const ComponentType type,
                const uint32_t index = 0
            ) const {
                if (m_components[type].empty()) {
                    return nullptr ;
                }

                return m_components[type][index] ;
            }

            /**
             * Get a component of the wanted type.
             * @param   index   Index of the component in the list of components
             *                  of the wanted type.
             * @warning Check the index value with the amountComponents()
             *          method!
             */
            template<class T>
            T* component(const uint32_t index = 0) const {
                if (m_components[T::ClassType].empty()) {
                    return nullptr ;
                }

                return static_cast<T*>(m_components[T::ClassType][index]) ;
            }

            /**
             * Get the amount of components for the wanted type.
             * @param   type    Type of the components.
             * @return  Amount of components of the wanted type that are
             *          attached to the current entity.
             */
            exported size_t amountComponents(const ComponentType type) const {
                return m_components[type].size() ;
            }

            /**
             * If true, the Entity is processed for rendering its content.
             * Otherwise, it is just ignored and all its children as well.
             */
            exported void setActive(const bool isActive) {
                m_isActive = isActive ;
            }

            /**
             * If true, the Entity is processed for rendering its content.
             * Otherwise, it is just ignored and all its children as well.
             */
            exported bool isActive() const {
                return m_isActive ;
            }

            /**
             * If true, the entity cannot be modified while the application is
             * running.
             */
            exported bool isEditable() const {
                return m_isEditable ;
            }

            /**
             * Set the lock state of the Entity.
             * @warning Setting the Entity locked while the rendering is running
             *          will have no effect.
             */
            exported void setLocked(const bool locked) {
                if (m_isEditable) {
                    m_isLocked = locked ;
                }
            }

            /**
             * If true, the entity cannot be modified while the application is
             * running.
             */
            exported bool isLocked() const {
                return m_isLocked ;
            }

            /**
             * Get the transform of the entity.
             */
            exported const Transform& transform() const {
                return *m_transform ;
            }

            exported Transform& transform() {
                return *m_transform ;
            }

            /**
             * Get the list of the components attached to the current entity.
             */
            exported const std::vector<std::vector<Component*>>& components() const {
                return m_components ;
            }

            // Remove copy/move operations.
            Entity(const Entity& copied) = delete;
            Entity(Entity&& moved) = delete;
            Entity& operator=(const Entity& copied) = delete;
            Entity& operator=(Entity&& moved) = delete;

        private:
            /**
             * Update the Entity state for edition (add/remove Component).
             */
            exported void setRenderState(const bool running) {
                if (running && m_isLocked) {
                    m_isEditable = false ;
                }
            }
    } ;
}

#endif
