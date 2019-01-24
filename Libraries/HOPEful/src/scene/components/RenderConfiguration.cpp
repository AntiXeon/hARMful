#include <scene/components/RenderConfiguration.hpp>
#include <scene/SceneTypes.hpp>
#include <interfaces/visitor/IVisitor.hpp>

using namespace Hope ;

RenderConfiguration::RenderConfiguration()
    : Component(Hope::RenderConfigurationType) {}

void RenderConfiguration::accept(IVisitor* visitor) {
    FrameID currentFrame = visitor -> currentFrameID() ;

    if (lastFrame() < currentFrame) {
        visitor -> visit(this) ;
        updateLastFrame(currentFrame) ;
    }
}

bool RenderConfiguration::isShareable() const {
    return false ;
}
