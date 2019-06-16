#include <scene/components/materials/deferred/GBufferQuadMaterialComponent.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <scene/framegraph/deferred/GBufferRenderNode.hpp>
#include <memory>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/450/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/450/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/450/modules/Includes.hpp>
    #include <scene/components/materials/shaders/GLSL/450/effects/Shadows.hpp>
    #include <scene/components/materials/shaders/GLSL/450/DeferredRendering.hpp>
#endif

using namespace Hope ;

GBufferQuadMaterialComponent::GBufferQuadMaterialComponent(const OffScreenRenderNode* gBuffer)
    : MaterialComponent(),
      m_gBuffer(gBuffer) {
    setupForwardShader() ;
    setupUniforms() ;
}

void GBufferQuadMaterialComponent::updateUniformValues() {
    const API::Framebuffer2D* framebuffer = m_gBuffer -> framebuffer() ;
    framebuffer -> bindUnitColor(GBufferRenderNode::AlbedoRenderTarget) ;
    framebuffer -> bindUnitColor(GBufferRenderNode::SpecularRenderTarget) ;
    framebuffer -> bindUnitColor(GBufferRenderNode::NormalRenderTarget) ;
    framebuffer -> bindUnitDepth(GBufferRenderNode::DepthRenderTarget) ;
}

void GBufferQuadMaterialComponent::setupUniforms() {
    std::shared_ptr<Hope::ShaderUniform> albedoUniform = std::make_shared<Hope::ShaderUniform>() ;
    albedoUniform -> setName(UniformNames::MaterialGBufferAlbedoUniformName()) ;
    addShaderUniform(albedoUniform) ;

    std::shared_ptr<Hope::ShaderUniform> specularUniform = std::make_shared<Hope::ShaderUniform>() ;
    specularUniform -> setName(UniformNames::MaterialGBufferSpecularUniformName()) ;
    addShaderUniform(specularUniform) ;

    std::shared_ptr<Hope::ShaderUniform> normalUniform = std::make_shared<Hope::ShaderUniform>() ;
    normalUniform -> setName(UniformNames::MaterialGBufferNormalUniformName()) ;
    addShaderUniform(normalUniform) ;

    std::shared_ptr<Hope::ShaderUniform> depthUniform = std::make_shared<Hope::ShaderUniform>() ;
    depthUniform -> setName(UniformNames::MaterialGBufferDepthUniformName()) ;
    addShaderUniform(depthUniform) ;
}

void GBufferQuadMaterialComponent::setupForwardShader() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>(ForwardPassID) ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(DeferredRenderingFinalVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesTextureUnitsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ShadowsShadowCalculationModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesAmountLightsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsUtilityModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsLightComputeModuleCode) ;
    shaderProgram -> addFragmentShaderCode(DeferredRenderingFinalFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(renderPass) ;
}
