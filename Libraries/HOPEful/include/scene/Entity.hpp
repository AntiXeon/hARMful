#ifndef __HOPE__ENTITY__
#define __HOPE__ENTITY__

#include <scene/Node.hpp>
#include <scene/SceneTypes.hpp>
#include <scene/Transform.hpp>
#include <scene/SceneRenderData.hpp>
#include <memory>
#include <map>

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
            std::map<ComponentType, Component*> m_components ;

            /**
             * Render data shared with the scene.
             */
            std::shared_ptr<SceneRenderData> m_renderData = nullptr ;

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
             * If true, the Entity is processed for rendering its content.
             * Otherwise, it is just ignored and all its children as well.
             */
            void setActive(const bool isActive) ;

            /**
             * If true, the Entity is processed for rendering its content.
             * Otherwise, it is just ignored and all its children as well.
             */
            bool isActive() const ;

            /**
             * Get the transform of the entity.
             */
            Transform& transform() ;

            /**
             * Get the list of the components attached to the current entity.
             */
            std::vector<Component*> components() const ;

            /**
             * Get the scene render data.
             */
            std::shared_ptr<SceneRenderData>& renderData() const ;

            // Remove copy/move operations.
            Entity(const Entity& copied) = delete;
            Entity(Entity&& moved) = delete;
            Entity& operator=(const Entity& copied) = delete;
            Entity& operator=(Entity&& moved) = delete;

        private:
            /**
             * Set the scene render data.
             */
            void setRenderData(const std::shared_ptr<SceneRenderData>& data) ;

        protected:
            /**
             * Additional action to perform when a child is added.
             */
            void onChildAdded(Node* newChild) override ;

            /**
             * Additional action to perform when a child is removed.
             */
            void onChildRemoved(Node* child) override ;
    } ;
}

#endif
