#include <scene/components/materials/DiffuseMaterialComponent.hpp>
#include <scene/components/materials/shaders/GLSL/450/Modules.hpp>
#include <scene/components/materials/shaders/GLSL/450/modules/Functions.hpp>
#include <scene/components/materials/shaders/GLSL/450/modules/Includes.hpp>
#include <scene/components/materials/shaders/GLSL/450/materials/DiffuseMap.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <memory>

using namespace Hope ;

DiffuseMaterialComponent::DiffuseMaterialComponent()
    : MaterialComponent(),
      m_ambient(Color(0.f, 0.f, 0.f)),
      m_diffuse(nullptr),
      m_specular(Color(1.f, 1.f, 1.f)),
      m_shininess(10.f) {
    setupRendering() ;
    setupUniforms() ;
}

DiffuseMaterialComponent::~DiffuseMaterialComponent() {
    delete m_diffuse ;
}

void DiffuseMaterialComponent::updateUniformValues() {
    if (m_diffuse) {
        m_diffuse -> activate(DiffuseMapBinding) ;
        m_diffuse -> bind() ;
        uniform(UniformNames::MaterialDiffuseUniformName()) -> setInteger(DiffuseMapBinding) ;
    }

    uniform(UniformNames::MaterialAmbientUniformName()) -> setVec3(m_ambient.toRGB()) ;
    uniform(UniformNames::MaterialSpecularUniformName()) -> setVec3(m_specular.toRGB()) ;
    uniform(UniformNames::MaterialShininessUniformName()) -> setFloating(m_shininess) ;
}

void DiffuseMaterialComponent::setupUniforms() {
    std::shared_ptr<Hope::ShaderUniform> ambientMapUniform = std::make_shared<Hope::ShaderUniform>() ;
    ambientMapUniform -> setName(UniformNames::MaterialAmbientUniformName()) ;
    addShaderUniform(ambientMapUniform) ;

    std::shared_ptr<Hope::ShaderUniform> diffuseMapUniform = std::make_shared<Hope::ShaderUniform>() ;
    diffuseMapUniform -> setName(UniformNames::MaterialDiffuseUniformName()) ;
    addShaderUniform(diffuseMapUniform) ;

    std::shared_ptr<Hope::ShaderUniform> specularUniform = std::make_shared<Hope::ShaderUniform>() ;
    specularUniform -> setName(UniformNames::MaterialSpecularUniformName()) ;
    addShaderUniform(specularUniform) ;

    std::shared_ptr<Hope::ShaderUniform> shininessUniform = std::make_shared<Hope::ShaderUniform>() ;
    shininessUniform -> setName(UniformNames::MaterialShininessUniformName()) ;
    addShaderUniform(shininessUniform) ;
}

void DiffuseMaterialComponent::setupDefaultRenderPass() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>(ForwardPassID) ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(DiffuseMapForwardVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesAmountLightsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsLightComputeModuleCode) ;
    shaderProgram -> addFragmentShaderCode(DiffuseMapForwardFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(renderPass) ;
}

void DiffuseMaterialComponent::setupDiffuseRenderPass() {
}

void DiffuseMaterialComponent::setupNormalRenderPass() {
}

void DiffuseMaterialComponent::setupSpecularRenderPass() {
}
