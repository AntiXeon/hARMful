#include <scene/Scene.hpp>

using namespace Hope ;
using namespace Hope::GL ;

Scene::Scene()
    : m_root(new Entity()),
      m_renderConfig(new RenderConfiguration()) {
    m_root -> addComponent(m_renderConfig) ;
    m_root -> setRenderData(&m_renderData) ;

    m_frameGraphVisitor.setSceneRoot(m_root) ;
}

Scene::~Scene() {
    delete m_root ;
}

void Scene::render() {
    // Execute the frame graph processing for rendering the scene.
    FrameGraphNode* fgRoot = m_renderConfig -> root() ;
    fgRoot -> accept(&m_frameGraphVisitor) ;
    m_frameGraphVisitor.nextFrame() ;
}

Entity* Scene::root() {
    return m_root ;
}

void Scene::setFrameGraphRoot(FrameGraphNode* root) {
    root -> setSceneGraphRoot(m_root) ;
    m_renderConfig -> setFrameGraphRoot(root) ;
}
