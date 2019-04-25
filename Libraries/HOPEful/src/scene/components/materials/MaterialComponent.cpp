#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/components/lights/DirectionalLightComponent.hpp>
#include <scene/components/lights/PointLightComponent.hpp>
#include <scene/framegraph/ProcessedSceneNode.hpp>
#include <scene/framegraph/RenderRequiredData.hpp>
#include <scene/Entity.hpp>
#include <scene/SceneCache.hpp>
#include <utils/StringExt.hpp>

using namespace Hope ;

const UniformNames MaterialComponent::Uniforms ;

MaterialComponent::MaterialComponent()
    : Component(Hope::MaterialComponentType) {}
