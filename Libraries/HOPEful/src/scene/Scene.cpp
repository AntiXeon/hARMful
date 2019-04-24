#include <scene/Scene.hpp>

using namespace Hope ;
using namespace Hope::GL ;

Scene::Scene()
    : m_root(new Entity()),
      m_renderConfig(new RenderConfiguration()) {
    m_root -> addComponent(m_renderConfig) ;
    m_frameGraphVisitor = new OpenGLFrameGraphVisitor() ;
    m_frameGraphVisitor -> setSceneRoot(m_root) ;
}

Scene::~Scene() {
    delete m_root ;
    delete m_frameGraphVisitor ;
}

void Scene::render() {
    // Execute the frame graph processing for rendering the scene.
    FrameGraphNode* fgRoot = m_renderConfig -> root() ;
    fgRoot -> accept(m_frameGraphVisitor) ;
    m_frameGraphVisitor -> nextFrame() ;
}

void Scene::setFrameGraphRoot(FrameGraphNode* root) {
    root -> setSceneGraphRoot(m_root) ;
    m_renderConfig -> setFrameGraphRoot(root) ;
}
