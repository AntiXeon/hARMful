#include <scene/components/materials/MaterialComponent.hpp>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/450/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/450/effects/Shadows.hpp>
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
    setupDirectionalLightDepthMapShader() ;
}

void MaterialComponent::setupDirectionalLightDepthMapShader() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>(DirectionalShadowPassID) ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(ShadowsDirLightShadowsVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ShadowsDirLightShadowsFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(renderPass) ;
}
