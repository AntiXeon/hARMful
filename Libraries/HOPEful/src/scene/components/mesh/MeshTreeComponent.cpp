#include <HopeAPI.hpp>
#include <HOPEStrings.hpp>
#include <scene/Entity.hpp>
#include <scene/components/mesh/MeshTreeComponent.hpp>

using namespace Hope ;

MeshTreeComponent::MeshTreeComponent(const std::string& meshFile)
    : Component(ClassType),
      m_source(meshFile) {}

void MeshTreeComponent::onAttach(Entity* entity) {
    if (!m_loader.meshRoot()) {
        m_loader.load(m_source, &(entity -> transform())) ;
    }
    else {
        Hope::Transform* meshRootTransform = m_loader.meshRoot() ;
        meshRootTransform -> setParent(&(entity -> transform())) ;
    }
}

void MeshTreeComponent::onDetach(Entity*) {
    if (m_loader.meshRoot()) {
        Hope::Transform* meshRootTransform = m_loader.meshRoot() ;
        meshRootTransform -> setParent(nullptr) ;
    }
}
