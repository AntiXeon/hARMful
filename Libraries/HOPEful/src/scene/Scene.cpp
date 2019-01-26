#include <scene/Scene.hpp>

using namespace Hope ;
using namespace Hope::GL ;

Scene::Scene() {
    m_root.addComponent(&m_renderConfig) ;
}

void Scene::render() {
    // Execute the frame graph processing for rendering the scene.
    FrameGraphNode* fgRoot = m_renderConfig.root() ;
    fgRoot -> accept(&m_frameGraphVisitor) ;
}

Entity& Scene::root() {
    return m_root ;
}

void Scene::setFrameGraphRoot(FrameGraphNode* root) {
    root -> setSceneGraphRoot(&m_root) ;
    m_renderConfig.setFrameGraphRoot(root) ;
}
