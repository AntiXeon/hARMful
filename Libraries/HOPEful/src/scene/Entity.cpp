#include <scene/Entity.hpp>
#include <scene/Transform.hpp>
#include <scene/components/Component.hpp>
#include <algorithm>
#include <cassert>

using namespace Hope ;

Entity::Entity(Transform* transform)
 	: m_transform(transform) {
    m_components.resize(AmountComponentTypes) ;
}

Entity::~Entity() {
    for (int componentType = MaterialComponentType ; componentType != LastComponentType ; ++componentType) {
        removeComponents(componentType) ;
    }

    m_components.clear() ;
}

int32_t Entity::addComponent(const std::shared_ptr<Component>& component) {
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
        int32_t lastComponentIndex = static_cast<int32_t>(m_components[newComponentType].size() - 1) ;
        return lastComponentIndex ;
    }
    else {
        const int32_t UniqueComponentIndex = 0 ;

        // Replace the lone component.
        m_components[newComponentType][UniqueComponentIndex] = component ;
        return UniqueComponentIndex ;
    }
}

void Entity::removeComponent(const ComponentType type, const uint32_t index) {
    std::weak_ptr<Component> toRemove ;

    if (m_components[type].size() > 0) {
        toRemove = m_components[type][index] ;
        removeComponent(toRemove) ;
    }
}

void Entity::removeComponents(const ComponentType type) {
    if (!m_isEditable) {
        return ;
    }

    if (m_components[type].size() > 0) {
        std::vector<std::shared_ptr<Component>>& components = m_components[type] ;

        for (std::shared_ptr<Component>& component : components) {
            component -> detach(this) ;
        }

        components.clear() ;
    }
}

Component* Entity::component(
    const ComponentType type,
    const uint32_t index
) const {
    if (m_components[type].empty()) {
        return nullptr ;
    }

    return m_components[type][index].get() ;
}

void Entity::removeComponent(const std::weak_ptr<Component>& wkComponent) {
    if (auto component = wkComponent.lock()) {
        if (!component) {
            return ;
        }

        if (component -> isRemovable()) {
            bool isDetached = component -> detach(this) ;

            if (!isDetached) {
                return ;
            }

            ComponentType componentType = component -> type() ;
            std::vector<std::shared_ptr<Component>>& components = m_components[componentType] ;
            auto position = std::find(components.begin(), components.end(), component) ;
            components.erase(position) ;
        }
    }
}

void Entity::setRenderState(const bool running) {
    if (running && m_isLocked) {
        m_isEditable = false ;
    }
}
