#include <scene/ogl/components/MeshComponent.hpp>
#include <scene/ogl/mesh/loader/MeshLoader.hpp>
#include <scene/ogl/mesh/Mesh.hpp>
#include <scene/SceneTypes.hpp>

using namespace Hope::GL ;

MeshComponent::MeshComponent(const std::string& meshFile)
    : Component(Hope::MeshComponent) {
    MeshLoader loader(meshFile) ;
    m_mesh = loader.mesh() ;
}

bool MeshComponent::isShareable() const {
    return true ;
}
