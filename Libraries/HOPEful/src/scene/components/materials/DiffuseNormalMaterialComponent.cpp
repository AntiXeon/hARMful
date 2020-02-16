#include <scene/components/materials/DiffuseNormalMaterialComponent.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <memory>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/460/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Includes.hpp>
    #include <scene/components/materials/shaders/GLSL/460/materials/DiffuseNormalMap.hpp>
    #include <scene/components/materials/shaders/GLSL/460/effects/Shadows.hpp>
#endif

using namespace Hope ;

DiffuseNormalMaterialComponent::DiffuseNormalMaterialComponent()
    : MaterialComponent(),
      m_ambient(Color(0.f, 0.f, 0.f)),
      m_diffuse(nullptr),
      m_normal(nullptr),
      m_specular(Color(1.f, 1.f, 1.f)),
      m_shininess(10.f) {
    setupRendering() ;
    setupUniforms() ;
}

void DiffuseNormalMaterialComponent::updateUniformValues() {
    if (m_diffuse) {
        m_diffuse -> bindUnit(DiffuseMapBinding) ;
    }

    if (m_normal) {
        m_normal -> bindUnit(NormalMapBinding) ;
    }

    uniforms().at(UniformNames::MaterialAmbientUniformName()) -> setVec3(m_ambient.toRGB()) ;
    uniforms().at(UniformNames::MaterialSpecularUniformName()) -> setVec3(m_specular.toRGB()) ;
    uniforms().at(UniformNames::MaterialShininessUniformName()) -> setFloating(m_shininess) ;
}

void DiffuseNormalMaterialComponent::setupUniforms() {
    auto ambientUniform = std::make_unique<Hope::ShaderUniform>() ;
    ambientUniform -> setName(UniformNames::MaterialAmbientUniformName()) ;
    ambientUniform -> setLocation(UniformNames::AmbientLocation) ;
    uniforms().add(std::move(ambientUniform)) ;

    auto specularUniform = std::make_unique<Hope::ShaderUniform>() ;
    specularUniform -> setName(UniformNames::MaterialSpecularUniformName()) ;
    specularUniform -> setLocation(UniformNames::SpecularLocation) ;
    uniforms().add(std::move(specularUniform)) ;

    auto shininessUniform = std::make_unique<Hope::ShaderUniform>() ;
    shininessUniform -> setName(UniformNames::MaterialShininessUniformName()) ;
    shininessUniform -> setLocation(UniformNames::ShininessLocation) ;
    uniforms().add(std::move(shininessUniform)) ;
}

void DiffuseNormalMaterialComponent::setupForwardShader() {
    std::unique_ptr<API::RenderPass> renderPass = std::make_unique<API::RenderPass>(ForwardPassID) ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(DiffuseNormalMapForwardVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesTextureUnitsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ShadowsShadowCalculationModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesAmountLightsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsLightComputeModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsUtilityModuleCode) ;
    shaderProgram -> addFragmentShaderCode(DiffuseNormalMapForwardFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(std::move(renderPass)) ;
}

void DiffuseNormalMaterialComponent::setupDeferredShader() {
    std::unique_ptr<API::RenderPass> renderPass = std::make_unique<API::RenderPass>(DeferredPassID) ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(DiffuseNormalMapDeferredVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsUtilityModuleCode) ;
    shaderProgram -> addFragmentShaderCode(DiffuseNormalMapDeferredFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(std::move(renderPass)) ;
}
