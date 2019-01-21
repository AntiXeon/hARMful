#include <HopeAPI.hpp>
#include <scene/components/MeshComponent.hpp>
#include <scene/SceneTypes.hpp>

using namespace Hope ;

MeshComponent::MeshComponent(const std::string& meshFile)
    : Component(Hope::MeshComponent) {
    API::MeshLoader loader(meshFile) ;
    m_mesh = loader.mesh() ;
}

bool MeshComponent::isShareable() const {
    return true ;
}
