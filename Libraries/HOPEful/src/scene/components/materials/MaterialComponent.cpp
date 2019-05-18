#include <scene/components/materials/MaterialComponent.hpp>

using namespace Hope ;

const UniformNames MaterialComponent::Uniforms ;

MaterialComponent::MaterialComponent()
    : Component(ClassType) {}

void MaterialComponent::setupRendering() {
    // Forward rendering pass.
    setupForwardRenderPass() ;

    // Deferred rendering passes.
    setupAlbedoRenderPass() ;
    setupNormalRenderPass() ;
    setupSpecularRenderPass() ;
    setupPositionRenderPass() ;
}
