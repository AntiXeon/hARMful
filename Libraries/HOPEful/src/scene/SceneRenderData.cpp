#include <scene/SceneRenderData.hpp>
#include <scene/components/lights/LightComponent.hpp>

using namespace Hope ;

void SceneRenderData::addLight(LightComponent* light) {
    m_lights.insert(light) ;
}

void SceneRenderData::removeLight(LightComponent* light) {
    m_lights.erase(light) ;
}

std::set<LightComponent*> SceneRenderData::lights() const {
    return m_lights ;
}
