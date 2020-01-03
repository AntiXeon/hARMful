#include <scene/components/materials/MaterialComponent.hpp>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/450/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/450/effects/Shadows.hpp>
    #include <scene/components/materials/shaders/GLSL/450/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/450/modules/Includes.hpp>
    #include <scene/components/materials/shaders/GLSL/450/DeferredPasses.hpp>

    #include <scene/ogl/rendering/capabilities/FaceCulling.hpp>
#endif

using namespace Hope ;

const UniformNames MaterialComponent::Uniforms ;

MaterialComponent::MaterialComponent()
    : Component(ClassType) {
    setupDirectionalLightDepthMapShader() ;
}

void MaterialComponent::setAlphaBlendingMode(const AlphaBlendingMode mode) {
    m_alphaBlend = mode ;
    // More to do on default render passes (forward/deferred)...
}

void MaterialComponent::setShadowMode(const ShadowMode mode) {
    m_shadowMode = mode ;
    // More to do on directional shadow render pass...
}

void MaterialComponent::setupRendering() {
    // Setup shaders for the different rendering passes.
    setupForwardShader() ;
    setupDeferredShader() ;
}

void MaterialComponent::setupDirectionalLightDepthMapShader() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>(DirectionalShadowPassID) ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;

    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(ShadowsDirLightShadowsVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ShadowsDirLightShadowsFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(renderPass) ;
}
