#include <scene/components/materials/deferred/GBufferQuadMaterialComponent.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <memory>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/460/Modules.hpp>
	#include <scene/components/materials/shaders/GLSL/460/modules/Includes.hpp>
	#include <scene/components/materials/shaders/GLSL/460/modules/Structures.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Functions.hpp>
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
    framebuffer -> bindUnitColor(GBufferRenderNode::AlbedoMetalnessRenderTarget) ;
    framebuffer -> bindUnitColor(GBufferRenderNode::EmissiveRoughnessRenderTarget) ;
    framebuffer -> bindUnitColor(GBufferRenderNode::AORenderTarget) ;
	framebuffer -> bindUnitColor(GBufferRenderNode::NormalRenderTarget) ;
    framebuffer -> bindUnitDepth(GBufferRenderNode::DepthRenderTarget) ;
    uniforms(ForwardPassID).at(UniformNames::MSAAQualityUniformName()) -> setInteger(m_gBuffer -> multisamplingQuality()) ;
}

void GBufferQuadMaterialComponent::setupUniforms() {
    auto msaaQualityUniform = std::make_unique<Hope::ShaderUniform>() ;
    msaaQualityUniform -> setName(UniformNames::MSAAQualityUniformName()) ;
    msaaQualityUniform -> setLocation(MSAAQualityUniformLocation) ;
    uniforms(ForwardPassID).add(std::move(msaaQualityUniform)) ;
}

void GBufferQuadMaterialComponent::setupForwardShader() {
    std::unique_ptr<API::RenderPass> renderPass = std::make_unique<API::RenderPass>(ForwardPassID) ;
    API::ShaderProgram* shaderProgram = renderPass -> shaderProgram() ;

    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(DeferredRenderingShadingVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesTextureUnitsModuleCode) ;
	shaderProgram -> addFragmentShaderCode(IncludesAmountLightsModuleCode) ;
	shaderProgram -> addFragmentShaderCode(StructuresMaterialsModuleCode) ;
	shaderProgram -> addFragmentShaderCode(StructuresLightsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ShadowsShadowCalculationModuleCode) ;
	shaderProgram -> addFragmentShaderCode(FunctionsUtilityModuleCode) ;
	shaderProgram -> addFragmentShaderCode(FunctionsPbrComputeModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsLightComputeModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsFogModuleCode) ;
    shaderProgram -> addFragmentShaderCode(DeferredRenderingShadingPbrFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(std::move(renderPass)) ;
}
