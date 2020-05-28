#include <scene/Scene.hpp>
#include <scene/Entity.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>
#include <utils/LogSystem.hpp>
#include <HOPEStrings.hpp>

using namespace Hope ;

Scene::Scene(std::shared_ptr<IFrameGraphVisitor> visitor)
    : m_root(std::make_unique<Transform>()),
      m_renderConfig(std::make_unique<RenderConfiguration>()),
      m_frameGraphVisitor(visitor) {
    m_root -> entity() -> addComponent(m_renderConfig.get()) ;
    m_frameGraphVisitor -> setSceneRoot(m_root.get()) ;
}

void Scene::render() {
    if (!m_isPrepared) {
        Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;
        Doom::LogSystem::WriteLine(level, Texts::Scene_NotPrepared) ;
        exit(EXIT_FAILURE) ;
    }

    // Execute the frame graph processing for rendering the scene.
    FrameGraphNode* fgRoot = m_renderConfig -> root() ;
    fgRoot -> accept(m_frameGraphVisitor.get()) ;
}

void Scene::lockEntities(const bool state) {
    m_isPrepared = state ;
    lockEntity(m_root.get(), state) ;
}

void Scene::setFrameGraphRoot(FrameGraphNode* root) {
    root -> setSceneGraphRoot(m_root.get() ) ;
    m_renderConfig -> setFrameGraphRoot(root) ;
}

void Scene::lockEntity(Transform* transform, const bool state) {
    transform -> entity() -> setRenderState(state) ;

    auto children = transform -> children() ;
    for (Node* child : children) {
        Transform* transformChild = static_cast<Transform*>(child) ;
        lockEntity(transformChild, state) ;
    }
}
