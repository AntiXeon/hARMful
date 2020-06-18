#include <scene/components/materials/deferred/ShadingDeferredRenderMaterialComponent.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <files/images/readers/ImageMemoryReader.hpp>
#include <resources/BrdfLUT.hpp>
#include <memory>

#ifdef OGL
    #include <scene/ogl/textures/formats/WrapModes.hpp>
    #include <scene/ogl/textures/formats/FilterModes.hpp>
    #include <scene/components/materials/shaders/GLSL/460/Modules.hpp>
	#include <scene/components/materials/shaders/GLSL/460/modules/Includes.hpp>
	#include <scene/components/materials/shaders/GLSL/460/modules/Structures.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/460/effects/Shadows.hpp>
    #include <scene/components/materials/shaders/GLSL/460/DeferredRendering.hpp>
#endif

using namespace Hope ;

std::unique_ptr<API::TextureImage2D> ShadingDeferredRenderMaterialComponent::BrdfLUT = nullptr ;

ShadingDeferredRenderMaterialComponent::ShadingDeferredRenderMaterialComponent(
    const GBufferRenderNode* gBuffer,
    const API::EnvironmentMap* envMap
)
: MaterialComponent(),
  m_gBuffer(gBuffer) {
    setupForwardShader() ;
    setupUniforms() ;

    if (envMap) {
        m_specularMap = envMap -> specularMap() ;
        m_irradianceMap = envMap -> irradianceMap() ;
    }

    if (!BrdfLUT) {
        auto rawImage = Spite::ImageMemoryReader::Read(getBrdfLUTFile().buffer(), true) ;
        BrdfLUT = std::make_unique<API::TextureImage2D>(rawImage, true) ;
        BrdfLUT -> setWrapModes({ API::ClampToEdge, API::ClampToEdge }) ;
        BrdfLUT -> setFiltering(API::Linear, API::Linear) ;
    }
}

void ShadingDeferredRenderMaterialComponent::updateUniformValues() {
    const API::Framebuffer* framebuffer = m_gBuffer -> framebuffer() ;
    framebuffer -> bindUnitColor(GBufferRenderNode::AlbedoMetalnessRenderTarget) ;
    framebuffer -> bindUnitColor(GBufferRenderNode::EmissiveRoughnessRenderTarget) ;
    framebuffer -> bindUnitColor(GBufferRenderNode::AORenderTarget) ;
	framebuffer -> bindUnitColor(GBufferRenderNode::NormalRenderTarget) ;
    framebuffer -> bindUnitDepth(GBufferRenderNode::DepthRenderTarget) ;
    uniforms(ForwardPassID).at(UniformNames::MSAAQualityUniformName()) -> setInteger(m_gBuffer -> multisamplingQuality()) ;
    uniforms(ForwardPassID).at(UniformNames::MaterialExposureUniformName()) -> setFloating(m_exposure) ;

    float reflectionLOD = static_cast<float>(m_specularMap -> mipmapLevel() - 1) ;
    uniforms(ForwardPassID).at(UniformNames::MaterialReflectionLODUniformName()) -> setFloating(reflectionLOD) ;

    if (m_irradianceMap && m_specularMap) {
        BrdfLUT -> bindUnit(BrdfLUTBinding) ;
        m_irradianceMap -> bindUnit(IrradianceBinding) ;
        m_specularMap -> bindUnit(SpecularBinding) ;
    }
}

void ShadingDeferredRenderMaterialComponent::setExposure(const float exposure) {
    m_exposure = exposure ;
}

void ShadingDeferredRenderMaterialComponent::setupUniforms() {
    generateUniform(
        ForwardPassID,
        UniformNames::MSAAQualityUniformName(),
        MSAAQualityUniformLocation
    ) ;

    generateUniform(
        ForwardPassID,
        UniformNames::MaterialExposureUniformName(),
        ExposureUniformLocation
    ) ;

    generateUniform(
        ForwardPassID,
        UniformNames::MaterialReflectionLODUniformName(),
        ReflectionLODUniformLocation
    ) ;

    generateUniform(
        ForwardPassID,
        UniformNames::MaterialEnvSpecularUniformName(),
        SpecularBinding
    ) ;

    generateUniform(
        ForwardPassID,
        UniformNames::MaterialEnvIrradianceUniformName(),
        IrradianceBinding
    ) ;

    generateUniform(
        ForwardPassID,
        UniformNames::MaterialBrdfLUTUniformName(),
        BrdfLUTBinding
    ) ;
}

void ShadingDeferredRenderMaterialComponent::setupForwardShader() {
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
