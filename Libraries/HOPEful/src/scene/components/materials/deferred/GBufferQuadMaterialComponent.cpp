#include <scene/components/materials/deferred/GBufferQuadMaterialComponent.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <memory>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/460/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Includes.hpp>
    #include <scene/components/materials/shaders/GLSL/460/effects/Shadows.hpp>
    #include <scene/components/materials/shaders/GLSL/460/DeferredRendering.hpp>
#endif

using namespace Hope ;

GBufferQuadMaterialComponent::GBufferQuadMaterialComponent(const GBufferRenderNode* gBuffer)
    : MaterialComponent(),
      m_gBuffer(gBuffer) {
    setupForwardShader() ;
    setupUniforms() ;
}

void GBufferQuadMaterialComponent::updateUniformValues() {
    const API::Framebuffer* framebuffer = m_gBuffer -> framebuffer() ;
    framebuffer -> bindUnitColor(GBufferRenderNode::AlbedoRenderTarget) ;
    framebuffer -> bindUnitColor(GBufferRenderNode::SpecularRenderTarget) ;
    framebuffer -> bindUnitColor(GBufferRenderNode::NormalRenderTarget) ;
    framebuffer -> bindUnitDepth(GBufferRenderNode::DepthRenderTarget) ;
    uniform(UniformNames::MSAAQualityUniformName()) -> setInteger(m_gBuffer -> multisamplingQuality()) ;
}

void GBufferQuadMaterialComponent::setupUniforms() {
    auto msaaQualityUniform = std::make_unique<Hope::ShaderUniform>() ;
    msaaQualityUniform -> setName(UniformNames::MSAAQualityUniformName()) ;
    msaaQualityUniform -> setLocation(MSAAQualityUniformLocation) ;
    addShaderUniform(std::move(msaaQualityUniform)) ;
}

void GBufferQuadMaterialComponent::setupForwardShader() {
    std::unique_ptr<API::RenderPass> renderPass = std::make_unique<API::RenderPass>(ForwardPassID) ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(DeferredRenderingShadingVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesTextureUnitsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ShadowsShadowCalculationModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesAmountLightsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsUtilityModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsLightComputeModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsFogModuleCode) ;
    shaderProgram -> addFragmentShaderCode(DeferredRenderingShadingFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(std::move(renderPass)) ;
}
