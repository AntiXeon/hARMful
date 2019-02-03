#include <HopeAPI.hpp>
#include <HOPEStrings.hpp>
#include <scene/components/MeshComponent.hpp>
#include <scene/SceneTypes.hpp>
#include <interfaces/visitors/scenegraph/ISceneGraphVisitor.hpp>
#include <utils/LogSystem.hpp>
#include <cassert>

using namespace Hope ;

MeshComponent::MeshComponent(const std::string& meshFile)
    : Component(Hope::MeshComponentType) {
    API::MeshLoader loader(meshFile) ;
    m_mesh = loader.mesh() ;

    if (!m_mesh) {
        std::string errorLog = Texts::Mesh_NotLoaded + meshFile ;

        // Write the error in the log.
        auto logWeakPtr = Doom::LogSystem::GetInstance() ;
        auto logSharedPtr = logWeakPtr.lock() ;
        if (logSharedPtr) {
            Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;
            logSharedPtr -> writeLine(level, errorLog) ;
        }

        assert(m_mesh != nullptr) ;
    }
}

void MeshComponent::accept(ISceneGraphVisitor* visitor) {
    FrameID currentFrame = visitor -> currentFrameID() ;

    if (lastFrame() < currentFrame) {
        visitor -> visit(this) ;
        updateLastFrame(currentFrame) ;
    }
}

bool MeshComponent::isShareable() const {
    return true ;
}
