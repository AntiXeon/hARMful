#include <scene/Scene.hpp>
#include <utils/LogSystem.hpp>
#include <HOPEStrings.hpp>

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
    if (!m_isPrepared) {
        auto logWeakPtr = Doom::LogSystem::GetInstance() ;
        Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;

        auto logSharedPtr = logWeakPtr.lock() ;
        if (logSharedPtr) {
            logSharedPtr -> writeLine(level, Texts::Scene_NotPrepared) ;
        }

        exit(EXIT_FAILURE) ;
    }

    // Execute the frame graph processing for rendering the scene.
    FrameGraphNode* fgRoot = m_renderConfig -> root() ;
    fgRoot -> accept(m_frameGraphVisitor) ;
    m_frameGraphVisitor -> nextFrame() ;
}

void Scene::lockEntities(const bool state) {
    m_isPrepared = state ;
    lockEntity(m_root, state) ;
}

void Scene::setFrameGraphRoot(FrameGraphNode* root) {
    root -> setSceneGraphRoot(m_root) ;
    m_renderConfig -> setFrameGraphRoot(root) ;
}

void Scene::lockEntity(Entity* entity, const bool state) {
    entity -> setRenderState(state) ;

    auto& children = entity -> children() ;
    for (Node* child : children) {
        Entity* entityChild = static_cast<Entity*>(child) ;
        lockEntity(entityChild, state) ;
    }
}
