#include <HopeAPI.hpp>
#include <scene/components/MeshComponent.hpp>
#include <scene/SceneTypes.hpp>
#include <interfaces/visitor/IVisitor.hpp>

using namespace Hope ;

MeshComponent::MeshComponent(const std::string& meshFile)
    : Component(Hope::MeshComponentType) {
    API::MeshLoader loader(meshFile) ;
    m_mesh = loader.mesh() ;
}

void MeshComponent::accept(IVisitor* visitor) {
    FrameID currentFrame = visitor -> currentFrameID() ;

    if (lastFrame() < currentFrame) {
        visitor -> visit(this) ;
        updateLastFrame(currentFrame) ;
    }
}

bool MeshComponent::isShareable() const {
    return true ;
}
