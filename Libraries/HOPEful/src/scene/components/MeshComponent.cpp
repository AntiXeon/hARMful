#include <HopeAPI.hpp>
#include <scene/components/MeshComponent.hpp>

#ifdef OGL
    #include <scene/ogl/mesh/loader/MeshLoader.hpp>
    #include <scene/ogl/mesh/Mesh.hpp>
#elif defined(VK)
    #error "Unsupported graphics API"
#endif

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
