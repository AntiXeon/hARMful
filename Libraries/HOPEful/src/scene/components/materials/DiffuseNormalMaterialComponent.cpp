#include <scene/components/materials/DiffuseNormalMaterialComponent.hpp>
#include <scene/components/materials/shaders/GLSL/450/Modules.hpp>
#include <scene/components/materials/shaders/GLSL/450/modules/Functions.hpp>
#include <scene/components/materials/shaders/GLSL/450/modules/Includes.hpp>
#include <scene/components/materials/shaders/GLSL/450/materials/DiffuseNormalMap.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <memory>

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

DiffuseNormalMaterialComponent::~DiffuseNormalMaterialComponent() {
    delete m_diffuse ;
    delete m_normal ;
}

void DiffuseNormalMaterialComponent::updateUniformValues() {
    if (m_diffuse) {
        m_diffuse -> activate(DiffuseMapBinding) ;
        m_diffuse -> bind() ;
        uniform(UniformNames::MaterialDiffuseUniformName()) -> setInteger(DiffuseMapBinding) ;
    }

    if (m_normal) {
        m_normal -> activate(NormalMapBinding) ;
        m_normal -> bind() ;
        uniform(UniformNames::MaterialNormalUniformName()) -> setInteger(NormalMapBinding) ;
    }

    uniform(UniformNames::MaterialAmbientUniformName()) -> setVec3(m_ambient.toRGB()) ;
    uniform(UniformNames::MaterialSpecularUniformName()) -> setVec3(m_specular.toRGB()) ;
    uniform(UniformNames::MaterialShininessUniformName()) -> setFloating(m_shininess) ;
}

void DiffuseNormalMaterialComponent::setupUniforms() {
    std::shared_ptr<Hope::ShaderUniform> ambientUniform = std::make_shared<Hope::ShaderUniform>() ;
    ambientUniform -> setName(UniformNames::MaterialAmbientUniformName()) ;
    addShaderUniform(ambientUniform) ;

    std::shared_ptr<Hope::ShaderUniform> diffuseUniform = std::make_shared<Hope::ShaderUniform>() ;
    diffuseUniform -> setName(UniformNames::MaterialDiffuseUniformName()) ;
    addShaderUniform(diffuseUniform) ;

    std::shared_ptr<Hope::ShaderUniform> normalUniform = std::make_shared<Hope::ShaderUniform>() ;
    normalUniform -> setName(UniformNames::MaterialNormalUniformName()) ;
    addShaderUniform(normalUniform) ;

    std::shared_ptr<Hope::ShaderUniform> specularUniform = std::make_shared<Hope::ShaderUniform>() ;
    specularUniform -> setName(UniformNames::MaterialSpecularUniformName()) ;
    addShaderUniform(specularUniform) ;

    std::shared_ptr<Hope::ShaderUniform> shininessUniform = std::make_shared<Hope::ShaderUniform>() ;
    shininessUniform -> setName(UniformNames::MaterialShininessUniformName()) ;
    addShaderUniform(shininessUniform) ;
}

void DiffuseNormalMaterialComponent::setupDefaultRenderPass() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>(DefaultPassID) ;
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
    shaderProgram -> addFragmentShaderCode(IncludesAmountLightsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsLightComputeModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsUtilityModuleCode) ;
    shaderProgram -> addFragmentShaderCode(DiffuseNormalMapForwardFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(renderPass) ;
}

void DiffuseNormalMaterialComponent::setupDiffuseRenderPass() {
}

void DiffuseNormalMaterialComponent::setupNormalRenderPass() {
}

void DiffuseNormalMaterialComponent::setupSpecularRenderPass() {
}
