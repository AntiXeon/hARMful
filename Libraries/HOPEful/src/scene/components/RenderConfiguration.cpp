#include <scene/components/RenderConfiguration.hpp>
#include <scene/SceneTypes.hpp>
#include <interfaces/visitors/scenegraph/ISceneGraphVisitor.hpp>

using namespace Hope ;

RenderConfiguration::RenderConfiguration()
    : Component(Hope::RenderConfigurationType) {}

bool RenderConfiguration::isShareable() const {
    return false ;
}
