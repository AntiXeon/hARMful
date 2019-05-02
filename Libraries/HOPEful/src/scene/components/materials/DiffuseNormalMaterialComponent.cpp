#include <scene/components/materials/DiffuseNormalMaterialComponent.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/BlockBindings.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/BaseDataBlock.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/ModelDataBlock.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/Directive.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/AmountLights.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/LightsDataBlock.hpp>
#include <scene/components/materials/shaders/GL/4.5/DiffuseNormalMap.hpp>
#include <algorithm>
#include <memory>

using namespace Hope ;

const float DiffuseNormalMaterialComponent::MinimumShininessClamp = 1.f ;
const float DiffuseNormalMaterialComponent::MaximumShininessClamp = 512.f ;

const std::string DiffuseNormalMaterialComponent::DiffuseUniformName = "diffuseNormalMaterial.diffuseMap" ;
const std::string DiffuseNormalMaterialComponent::NormalMapUniformName = "diffuseNormalMaterial.normalMap" ;
const std::string DiffuseNormalMaterialComponent::SpecularUniformName = "diffuseNormalMaterial.specularColor" ;
const std::string DiffuseNormalMaterialComponent::ShininessUniformName = "diffuseNormalMaterial.shininess" ;

DiffuseNormalMaterialComponent::DiffuseNormalMaterialComponent()
    : MaterialComponent() {
    setupRendering() ;
    setupUniforms() ;

    setDiffuse(nullptr) ;
    setNormal(nullptr) ;
    setSpecular(Color(1.f, 1.f, 1.f)) ;
    setShininess(10.f) ;
}

DiffuseNormalMaterialComponent::~DiffuseNormalMaterialComponent() {
    delete m_diffuseMap ;
}

void DiffuseNormalMaterialComponent::updateUniformValues() {
    m_diffuseMap -> activate(DiffuseMapBinding) ;
    m_diffuseMap -> bind() ;
    uniform(DiffuseUniformName) -> setInteger(DiffuseMapBinding) ;
    m_normalMap -> activate(NormalMapBinding) ;
    m_normalMap -> bind() ;
    uniform(NormalMapUniformName) -> setInteger(NormalMapBinding) ;
    uniform(SpecularUniformName) -> setVec3(specular().toRGB()) ;
    uniform(ShininessUniformName) -> setFloating(shininess()) ;
}

void DiffuseNormalMaterialComponent::setDiffuse(const API::Texture2D* diffuse) {
    m_diffuseMap = diffuse ;
    m_diffuseUniform -> setInteger(DiffuseMapBinding) ;
}

void DiffuseNormalMaterialComponent::setNormal(const API::Texture2D* normal) {
    m_normalMap = normal ;
    m_normalUniform -> setInteger(NormalMapBinding) ;
}

void DiffuseNormalMaterialComponent::setSpecular(const Color& specular) {
    std::array<float, 4> colorArray = {
        specular.red(),
        specular.green(),
        specular.blue(),
        specular.alpha()
    } ;

    m_specularUniform -> setVec4(colorArray) ;
}

void DiffuseNormalMaterialComponent::setShininess(const float shininess) {
    float shininessClamped = std::clamp(shininess, MinimumShininessClamp, MaximumShininessClamp) ;
    m_shininessUniform -> setFloating(shininessClamped) ;
}

const API::Texture2D* DiffuseNormalMaterialComponent::diffuse() const {
    return m_diffuseMap ;
}

const API::Texture2D* DiffuseNormalMaterialComponent::normal() const {
    return m_normalMap ;
}

Color DiffuseNormalMaterialComponent::specular() const {
    const float* specular = m_specularUniform -> vec4() ;
    return Color(specular[0], specular[1], specular[2], specular[3]) ;
}

float DiffuseNormalMaterialComponent::shininess() const {
    return m_shininessUniform -> floating() ;
}

void DiffuseNormalMaterialComponent::setupUniforms() {
    m_diffuseUniform = std::make_shared<Hope::ShaderUniform>() ;
    m_diffuseUniform -> setName(DiffuseUniformName) ;
    addShaderUniform(m_diffuseUniform) ;

    m_normalUniform = std::make_shared<Hope::ShaderUniform>() ;
    m_normalUniform -> setName(NormalMapUniformName) ;
    addShaderUniform(m_normalUniform) ;

    m_specularUniform = std::make_shared<Hope::ShaderUniform>() ;
    m_specularUniform -> setName(SpecularUniformName) ;
    addShaderUniform(m_specularUniform) ;

    m_shininessUniform = std::make_shared<Hope::ShaderUniform>() ;
    m_shininessUniform -> setName(ShininessUniformName) ;
    addShaderUniform(m_shininessUniform) ;
}

void DiffuseNormalMaterialComponent::setupRendering() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>() ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(DirectiveFragmentCode) ;
    shaderProgram -> addVertexShaderCode(BlockBindingsFragmentCode) ;
    shaderProgram -> addVertexShaderCode(BaseDataBlockVertexCode) ;
    shaderProgram -> addVertexShaderCode(ModelDataBlockVertexCode) ;
    shaderProgram -> addVertexShaderCode(DiffuseNormalMapVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(DirectiveFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(BlockBindingsFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(BaseDataBlockVertexCode) ;
    shaderProgram -> addFragmentShaderCode(ModelDataBlockVertexCode) ;
    shaderProgram -> addFragmentShaderCode(AmountLightsFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(LightsDataBlockFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(DiffuseNormalMapFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(renderPass) ;
}
