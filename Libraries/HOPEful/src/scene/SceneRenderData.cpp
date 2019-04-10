#include <scene/SceneRenderData.hpp>
#include <scene/components/lights/LightComponent.hpp>
#include <scene/components/lights/DirectionalLightComponent.hpp>

using namespace Hope ;

void SceneRenderData::registerLight(LightComponent* light) {
    switch (light -> type()) {
        case LightComponent::Type::Directional:
        {
            auto dirLight = reinterpret_cast<DirectionalLightComponent*>(light) ;
            m_directionalLights.insert(dirLight) ;
        }

        default:
            break ;
    }
}

void SceneRenderData::deregisterLight(LightComponent* light) {
    switch (light -> type()) {
        case LightComponent::Type::Directional:
        {
            auto dirLight = reinterpret_cast<DirectionalLightComponent*>(light) ;
            m_directionalLights.erase(dirLight) ;
        }

        default:
            break ;
    }
}

std::set<DirectionalLightComponent*> SceneRenderData::directionalLights() const {
    return m_directionalLights ;
}
