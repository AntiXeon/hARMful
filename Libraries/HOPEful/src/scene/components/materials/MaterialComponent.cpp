#include <scene/components/materials/MaterialComponent.hpp>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/450/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/450/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/450/modules/Includes.hpp>
    #include <scene/components/materials/shaders/GLSL/450/DeferredPasses.hpp>
#endif

using namespace Hope ;

const UniformNames MaterialComponent::Uniforms ;

MaterialComponent::MaterialComponent()
    : Component(ClassType) {}

void MaterialComponent::setupRendering() {
    // Setup shaders for the different rendering passes.
    setupForwardShader() ;
    setupDeferredShader() ;
}
