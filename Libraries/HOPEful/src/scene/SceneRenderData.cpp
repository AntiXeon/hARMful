#include <scene/SceneRenderData.hpp>
#include <scene/components/lights/Light.hpp>

using namespace Hope ;

void SceneRenderData::addLight(Light* light) {
    m_lights.insert(light) ;
}

void SceneRenderData::removeLight(Light* light) {
    m_lights.erase(light) ;
}

std::set<Light*> SceneRenderData::lights() const {
    return m_lights ;
}
