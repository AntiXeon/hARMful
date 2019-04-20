#include <scene/SceneCache.hpp>
#include <scene/components/lights/LightComponent.hpp>
#include <scene/components/lights/DirectionalLightComponent.hpp>
#include <scene/components/lights/PointLightComponent.hpp>

using namespace Hope ;

void SceneCache::registerLight(LightComponent* light) {
    switch (light -> type()) {
        case LightComponent::Type::Directional:
        {
            auto dirLight = reinterpret_cast<DirectionalLightComponent*>(light) ;
            m_directionalLights.insert(dirLight) ;
            break ;
        }

        case LightComponent::Type::Point:
        {
            auto pointLight = reinterpret_cast<PointLightComponent*>(light) ;
            m_pointLights.insert(pointLight) ;
            break ;
        }

        default:
            break ;
    }
}

void SceneCache::deregisterLight(LightComponent* light) {
    switch (light -> type()) {
        case LightComponent::Type::Directional:
        {
            auto dirLight = reinterpret_cast<DirectionalLightComponent*>(light) ;
            m_directionalLights.erase(dirLight) ;
            break ;
        }

        case LightComponent::Type::Point:
        {
            auto pointLight = reinterpret_cast<PointLightComponent*>(light) ;
            m_pointLights.erase(pointLight) ;
            break ;
        }

        default:
            break ;
    }
}

std::set<DirectionalLightComponent*> SceneCache::directionalLights() const {
    return m_directionalLights ;
}

std::set<PointLightComponent*> SceneCache::pointLights() const {
    return m_pointLights ;
}
