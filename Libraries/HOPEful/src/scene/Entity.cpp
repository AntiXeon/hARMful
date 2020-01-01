#include <scene/components/Component.hpp>
#include <scene/Entity.hpp>
#include <algorithm>
#include <cassert>

using namespace Hope ;

Entity::Entity(Entity* parent) : Node(parent) {
    m_components.resize(AmountComponentTypes) ;
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

int32_t Entity::addComponent(Component* component) {
    const int32_t FailAddIndex = -1 ;

    if (!component) {
        return FailAddIndex ;
    }

    bool isAttached = component -> attach(this) ;
    ComponentType newComponentType = component -> type() ;

    if (!isAttached) {
        return FailAddIndex ;
    }

    if (component -> isStackable() || m_components[newComponentType].size() == 0) {
        // Stack the components.
        m_components[newComponentType].push_back(component) ;
        int32_t lastComponentIndex = m_components[newComponentType].size() - 1 ;
        return lastComponentIndex ;
    }
    else {
        const int32_t UniqueComponentIndex = 0 ;

        // Replace the lone component.
        m_components[newComponentType][UniqueComponentIndex] = component ;
        return UniqueComponentIndex ;
    }
}

void Entity::removeComponent(Component* component) {
    if (!component) {
        return ;
    }

    if (component -> isRemovable()) {
        bool isDetached = component -> detach(this) ;

        if (!isDetached) {
            return ;
        }

        ComponentType componentType = component -> type() ;
        std::vector<Component*>& components = m_components[componentType] ;
        auto position = std::find(components.begin(), components.end(), component) ;
        components.erase(position) ;
    }
}

void Entity::removeComponents(const ComponentType type) {
    if (!m_isEditable) {
        return ;
    }

    if (m_components[type].size() > 0) {
        std::vector<Component*>& components = m_components[type] ;

        for (Component* component : components) {
            component -> detach(this) ;
        }

        components.clear() ;
    }
}
