#include <scene/components/materials/DiffuseNormalSpecularMaterialComponent.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/BlockBindings.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/BaseDataBlock.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/ModelDataBlock.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/Directive.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/AmountLights.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/LightsDataBlock.hpp>
#include <scene/components/materials/shaders/GL/4.5/DiffuseNormalSpecularMap.hpp>
#include <algorithm>
#include <memory>

using namespace Hope ;

const float DiffuseNormalSpecularMaterialComponent::MinimumShininessClamp = 1.f ;
const float DiffuseNormalSpecularMaterialComponent::MaximumShininessClamp = 512.f ;

const std::string DiffuseNormalSpecularMaterialComponent::DiffuseMapUniformName = "material.diffuseMap" ;
const std::string DiffuseNormalSpecularMaterialComponent::NormalMapUniformName = "material.normalMap" ;
const std::string DiffuseNormalSpecularMaterialComponent::SpecularMapUniformName = "material.specularMap" ;
const std::string DiffuseNormalSpecularMaterialComponent::ShininessUniformName = "material.shininess" ;

DiffuseNormalSpecularMaterialComponent::DiffuseNormalSpecularMaterialComponent()
    : MaterialComponent() {
    setupRendering() ;
    setupUniforms() ;

    setDiffuseMap(nullptr) ;
    setNormalMap(nullptr) ;
    setSpecularMap(nullptr) ;
    setShininess(10.f) ;
}

DiffuseNormalSpecularMaterialComponent::~DiffuseNormalSpecularMaterialComponent() {
    delete m_diffuseMap ;
    delete m_normalMap ;
    delete m_specularMap ;
}

void DiffuseNormalSpecularMaterialComponent::updateUniformValues() {
    m_diffuseMap -> activate(DiffuseMapBinding) ;
    m_diffuseMap -> bind() ;
    uniform(DiffuseMapUniformName) -> setInteger(DiffuseMapBinding) ;
    m_normalMap -> activate(NormalMapBinding) ;
    m_normalMap -> bind() ;
    uniform(NormalMapUniformName) -> setInteger(NormalMapBinding) ;
    m_specularMap -> activate(SpecularMapBinding) ;
    m_specularMap -> bind() ;
    uniform(SpecularMapUniformName) -> setInteger(SpecularMapBinding) ;
    uniform(ShininessUniformName) -> setFloating(shininess()) ;
}

void DiffuseNormalSpecularMaterialComponent::setDiffuseMap(const API::Texture2D* diffuse) {
    m_diffuseMap = diffuse ;
    m_diffuseMapUniform -> setInteger(DiffuseMapBinding) ;
}

void DiffuseNormalSpecularMaterialComponent::setNormalMap(const API::Texture2D* normal) {
    m_normalMap = normal ;
    m_normalMapUniform -> setInteger(NormalMapBinding) ;
}

void DiffuseNormalSpecularMaterialComponent::setSpecularMap(const API::Texture2D* specular) {
    m_specularMap = specular ;
    m_specularMapUniform -> setInteger(SpecularMapBinding) ;
}

void DiffuseNormalSpecularMaterialComponent::setShininess(const float shininess) {
    float shininessClamped = std::clamp(shininess, MinimumShininessClamp, MaximumShininessClamp) ;
    m_shininessUniform -> setFloating(shininessClamped) ;
}

const API::Texture2D* DiffuseNormalSpecularMaterialComponent::diffuseMap() const {
    return m_diffuseMap ;
}

const API::Texture2D* DiffuseNormalSpecularMaterialComponent::normalMap() const {
    return m_normalMap ;
}

const API::Texture2D* DiffuseNormalSpecularMaterialComponent::specularMap() const {
    return m_specularMap ;
}

float DiffuseNormalSpecularMaterialComponent::shininess() const {
    return m_shininessUniform -> floating() ;
}

void DiffuseNormalSpecularMaterialComponent::setupUniforms() {
    m_diffuseMapUniform = std::make_shared<Hope::ShaderUniform>() ;
    m_diffuseMapUniform -> setName(DiffuseMapUniformName) ;
    addShaderUniform(m_diffuseMapUniform) ;

    m_normalMapUniform = std::make_shared<Hope::ShaderUniform>() ;
    m_normalMapUniform -> setName(NormalMapUniformName) ;
    addShaderUniform(m_normalMapUniform) ;

    m_specularMapUniform = std::make_shared<Hope::ShaderUniform>() ;
    m_specularMapUniform -> setName(SpecularMapUniformName) ;
    addShaderUniform(m_specularMapUniform) ;

    m_shininessUniform = std::make_shared<Hope::ShaderUniform>() ;
    m_shininessUniform -> setName(ShininessUniformName) ;
    addShaderUniform(m_shininessUniform) ;
}

void DiffuseNormalSpecularMaterialComponent::setupRendering() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>() ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(DirectiveFragmentCode) ;
    shaderProgram -> addVertexShaderCode(BlockBindingsFragmentCode) ;
    shaderProgram -> addVertexShaderCode(BaseDataBlockVertexCode) ;
    shaderProgram -> addVertexShaderCode(ModelDataBlockVertexCode) ;
    shaderProgram -> addVertexShaderCode(DiffuseNormalSpecularMapVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(DirectiveFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(BlockBindingsFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(BaseDataBlockVertexCode) ;
    shaderProgram -> addFragmentShaderCode(ModelDataBlockVertexCode) ;
    shaderProgram -> addFragmentShaderCode(AmountLightsFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(LightsDataBlockFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(DiffuseNormalSpecularMapFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(renderPass) ;
}
