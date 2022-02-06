#include "ecs/entity/EntityFactory.hpp"

using namespace Bane ;

Entity EntityFactory::create() {
    auto newEntity = Entity::Generate() ;
    m_entities.emplace(newEntity) ;
    return newEntity ;
}

void EntityFactory::remove(Entity& entity) {
    if (contains(entity)) {
        m_entities.erase(entity.id()) ;
        Entity::Free(entity) ;
    }
}
