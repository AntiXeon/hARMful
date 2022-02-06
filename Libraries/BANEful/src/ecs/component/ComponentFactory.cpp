#include "ecs/component/ComponentFactory.hpp"

using namespace Bane ;

// Component* ComponentFactory::create(const Entity& entity) {
//     assert(invariant()) ;
//
//     if (!entity.isValid()) {
//         throw std::runtime_error(BANEStrings::Errors::ECS_Component_InvalidEntity) ;
//     }
//
//     auto newComponent = std::make_unique<ComponentClass>(entity) ;
//     uint32_t newComponentID = newComponent -> id() ;
//     auto it = m_components.begin() ;
//     m_components.insert(it + newComponentID, std::move(newComponent)) ;
//
//     auto newComponentPtr = m_components[newComponentID].get() ;
//     auto itPtr = m_componentsPtr.begin() ;
//     m_componentsPtr.insert(itPtr + newComponentID, newComponentPtr) ;
//
//     m_entityComponents[entity.id()].push_back(m_componentsPtr) ;
//
//     assert(invariant()) ;
//
//     return newComponentPtr ;
// }

void ComponentFactory::remove(const Entity& entity) {
    assert(invariant()) ;

    if (m_entityComponents.count(entity.id()) != 0) {
        auto& componentList = m_entityComponents[entity.id()] ;

        for (auto& component: componentList) {
            uint32_t componentID = component -> id() ;

            if (m_componentsPtr.size() > componentID) {
                m_componentsPtr[componentID] = nullptr ;
                m_components[componentID] = nullptr ;
            }
        }

        m_entityComponents.erase(entity.id()) ;
    }

    assert(invariant()) ;
}

std::vector<Component*> ComponentFactory::components(const Entity& entity) const {
    if (m_entityComponents.count(entity.id()) != 0) {
        return m_entityComponents.at(entity.id()) ;
    }

    return std::vector<Component*>() ;
}
