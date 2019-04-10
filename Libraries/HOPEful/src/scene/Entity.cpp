#include <scene/components/Component.hpp>
#include <scene/Entity.hpp>
#include <algorithm>
#include <cassert>

using namespace Hope ;

Entity::Entity(Entity* parent)
    : Node(parent) {
    m_components.resize(Hope::AmountComponentTypes) ;
}

Entity::~Entity() {
    for (Component* component : m_components) {
        if (component) {
            component -> detach(this) ;

            if (component -> amountAttachedEntities() == 0) {
                delete component ;
            }
        }
    }

    m_components.clear() ;
}

void Entity::addComponent(Component* component) {
    if (!component) {
        return ;
    }

    ComponentType newComponentType = component -> type() ;
    component -> attach(this) ;
    m_components[newComponentType] = component ;
}

void Entity::removeComponent(Component* component) {
    if (!component) {
        return ;
    }

    removeComponent(component -> type()) ;
}

void Entity::removeComponent(const ComponentType type) {
    if (m_components[type]) {
        Component* component = m_components[type] ;
        component -> detach(this) ;
        m_components[type] = nullptr ;
    }
}

Component* Entity::component(const ComponentType type) const {
    return m_components[type] ;
}

void Entity::setActive(const bool isActive) {
    m_isActive = isActive ;
}

bool Entity::isActive() const {
    return m_isActive ;
}

const Transform& Entity::transform() const {
    return m_transform ;
}

Transform& Entity::transform() {
    return m_transform ;
}

std::vector<Component*> Entity::components() const {
    return m_components ;
}
