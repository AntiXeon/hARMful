#include <scene/components/Component.hpp>
#include <scene/Entity.hpp>
#include <algorithm>
#include <cassert>

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

SceneRenderData* Entity::renderData() const {
    return m_renderData ;
}

void Entity::setRenderData(SceneRenderData* data) {
    m_renderData = data ;

    const std::vector<Node*>& childrenNodes = children() ;
    for (Node* childNode : childrenNodes) {
        Entity* childEntity = static_cast<Entity*>(childNode) ;

        if (childEntity) {
            // Update scene render data by reattaching components.
            for (auto const& entry : m_components) {
                Component* component = entry.second ;
                component -> detach(this) ;
                component -> attach(this) ;
            }

            // Update every child of the current node.
            childEntity -> setRenderData(m_renderData) ;
        }
    }
}

void Entity::setActive(const bool isActive) {
    m_isActive = isActive ;
}

bool Entity::isActive() const {
    return m_isActive ;
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

void Entity::onChildAdded(Node* newChild) {
    Entity* childEntity = static_cast<Entity*>(newChild) ;
    childEntity -> setRenderData(m_renderData) ;
}

void Entity::onChildRemoved(Node* child) {
    Entity* childEntity = static_cast<Entity*>(child) ;
    childEntity -> setRenderData(nullptr) ;
}
