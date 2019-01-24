#include <scene/Scene.hpp>

using namespace Hope ;

Scene::Scene() {
    m_root.addComponent(&m_renderConfig) ;
}

Entity& Scene::root() {
    return m_root ;
}

void Scene::setFrameGraphRoot(FrameGraphNode* root) {
    m_renderConfig.setFrameGraphRoot(root) ;
}
