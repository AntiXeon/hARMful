#include <scene/components/Component.hpp>
#include <scene/Entity.hpp>
#include <algorithm>
#include <cassert>

#include <iostream>

using namespace Hope ;

Entity::Entity(Entity* parent) : Node(parent) {

}

Entity::~Entity() {
    for (auto const& entry : m_components) {
        Component* component = entry.second ;
        component -> detach(this) ;

        if (component -> amountAttachedEntities() == 0) {
            delete component ;
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

    if (m_components.count(component -> type()) > 0) {
        component -> detach(this) ;
        m_components.erase(component -> type()) ;
    }
}

void Entity::removeComponent(const ComponentType type) {
    if (m_components.count(type) > 0) {
        Component* component = m_components[type] ;
        component -> detach(this) ;
        m_components.erase(type) ;
    }
}

Component* Entity::component(const ComponentType type) const {
    if (m_components.count(type) > 0) {
        return m_components.at(type) ;
    }

    return nullptr ;
}

Transform& Entity::transform() {
    return m_transform ;
}

std::vector<Component*> Entity::components() const {
    std::vector<Component*> output ;

    for (auto const& entry : m_components) {
        output.push_back(entry.second) ;
    }

    return output ;
}
