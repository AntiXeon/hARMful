#include <scene/components/materials/MaterialComponent.hpp>
#include <cassert>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/460/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/460/effects/Shadows.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Includes.hpp>
#endif

using namespace Hope ;

const UniformNames MaterialComponent::Uniforms ;

MaterialComponent::MaterialComponent(const bool drawShadow)
    : Component(ClassType) {
    m_settings.setRenderEffect(&m_effect) ;

    if (drawShadow) {
        setupDirectionalLightDepthMapShader() ;
    }
}

void MaterialComponent::setupRendering() {
    // Setup shaders for the different rendering passes.
    setupForwardShader() ;
    setupDeferredShader() ;
}

void MaterialComponent::setupDirectionalLightDepthMapShader() {
    std::unique_ptr<API::RenderPass> renderPass = std::make_unique<API::RenderPass>(DirectionalShadowPassID) ;
    API::ShaderProgram* shaderProgram = renderPass -> shaderProgram() ;

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

    effect().addRenderPass(std::move(renderPass)) ;
}
