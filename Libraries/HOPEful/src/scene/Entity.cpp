#include <scene/Component.hpp>
#include <scene/Entity.hpp>
#include <scene/Transform.hpp>
#include <algorithm>
#include <cassert>

namespace Hope {
    Entity::Entity(Entity* parent) : Node(parent) {

    }

    Entity::~Entity() {
        for (Component* component : m_components) {
            component -> detach(this) ;

            if (component -> amountAttachedEntities() == 0) {
                delete component ;
            }
        }

        m_components.clear() ;
    }

    void Entity::addComponent(Component* component) {
        ComponentType newComponentType = component -> type() ;
        auto existingComponentPos = find(newComponentType) ;

        if (existingComponentPos != m_components.end()) {
            // Here we have found a component with the same type, so we detach
            // the previous component before adding the new one.
            removeComponent((*existingComponentPos)) ;
        }

        m_components.push_back(component) ;
    }

    void Entity::removeComponent(Component* component) {
        auto posComponent = std::find(m_components.begin(), m_components.end(), component) ;

        component -> detach(this) ;
        m_components.erase(posComponent) ;
    }

    void Entity::removeComponent(const ComponentType type) {
        auto posComponent = find(type) ;

        (*posComponent) -> detach(this) ;
        m_components.erase(posComponent) ;
    }

    Component* Entity::component(const ComponentType type) const {
        auto it = m_components.begin() ;

        // Replace the component of the given type by the new one if necessary.
        for (; it != m_components.end() ; ++it) {
            if (((*it) -> type()) == type) {
                return (*it) ;
            }
        }

        return nullptr ;
    }

    Transform& Entity::transform() {
        return m_transform ;
    }

    const std::vector<Component*>& Entity::components() const {
        return m_components ;
    }

    std::vector<Component*>::iterator Entity::find(const ComponentType type) {
        auto it = m_components.begin() ;

        // Replace the component of the given type by the new one if necessary.
        for (; it != m_components.end() ; ++it) {
            if (((*it) -> type()) == type) {
                return it ;
            }
        }

        return m_components.end() ;
    }
}
