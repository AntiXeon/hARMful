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
    for (std::vector<Component*> componentList : m_components) {
        for (Component* component : componentList) {
            if (component) {
                component -> detach(this) ;

                if (component -> amountAttachedEntities() == 0) {
                    delete component ;
                }
            }
        }
    }

    m_components.clear() ;
}

void Entity::addComponent(Component* component) {
    if (!component) {
        return ;
    }

    component -> attach(this) ;
    ComponentType newComponentType = component -> type() ;

    if (component -> isStackable() || m_components[newComponentType].size() == 0) {
        // Stack the components.
        m_components[newComponentType].push_back(component) ;
    }
    else {
        // Replace the lone component.
        m_components[newComponentType][0] = component ;
    }
}

void Entity::removeComponent(Component* component) {
    if (!component) {
        return ;
    }

    if (component -> isRemovable()) {
        component -> detach(this) ;

        ComponentType componentType = component -> type() ;
        std::vector<Component*>& components = m_components[componentType] ;
        auto position = std::find(components.begin(), components.end(), component) ;
        components.erase(position) ;
    }
}

void Entity::removeComponents(const ComponentType type) {
    if (m_components[type].size() > 0) {
        std::vector<Component*>& components = m_components[type] ;

        for (Component* component : components) {
            component -> detach(this) ;
        }

        components.clear() ;
    }
}
