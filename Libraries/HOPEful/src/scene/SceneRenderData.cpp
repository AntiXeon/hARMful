#include <scene/SceneRenderData.hpp>
#include <scene/components/lights/LightComponent.hpp>
#include <scene/components/lights/DirectionalLightComponent.hpp>

using namespace Hope ;

void SceneRenderData::addLight(LightComponent* light) {
    //m_lights.insert(light) ;

    if (light -> type() == LightComponent::Type::Directional) {
        auto dirLight = reinterpret_cast<DirectionalLightComponent*>(light) ;
        m_directionalLights.push_back(dirLight) ;
    }
}

void SceneRenderData::removeLight(LightComponent* light) {
    //m_lights.erase(light) ;

    if (light -> type() == LightComponent::Type::Directional) {
        m_directionalLights.pop_back() ;
    }
}

std::vector<DirectionalLightComponent*> SceneRenderData::directionalLights() const {
    return m_directionalLights ;
}
