#include <HopeAPI.hpp>
#include <HOPEStrings.hpp>
#include <scene/Entity.hpp>
#include <scene/components/mesh/MeshTreeComponent.hpp>

using namespace Hope ;

MeshTreeComponent::MeshTreeComponent(const std::string& meshFile)
    : Component(Hope::MeshTreeComponentType),
      m_source(meshFile) {}

void MeshTreeComponent::onAttach(Entity* entity) {
    if (!m_loader.meshRoot()) {
        m_loader.load(m_source, entity) ;
    }
    else {
        Hope::Entity* meshRootEntity = m_loader.meshRoot() ;
        meshRootEntity -> setParent(entity) ;
    }
}

void MeshTreeComponent::onDetach(Entity*) {
    if (m_loader.meshRoot()) {
        Hope::Entity* meshRootEntity = m_loader.meshRoot() ;
        meshRootEntity -> setParent(nullptr) ;
    }
}
