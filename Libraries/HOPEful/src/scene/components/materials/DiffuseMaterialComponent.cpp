#include <scene/components/materials/DiffuseMaterialComponent.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/BlockBindings.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/BaseDataBlock.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/ModelDataBlock.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/Directive.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/AmountLights.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/LightsDataBlock.hpp>
#include <scene/components/materials/shaders/GL/4.5/DiffuseMap.hpp>
#include <algorithm>
#include <memory>

using namespace Hope ;

const float DiffuseMaterialComponent::MinimumShininessClamp = 1.f ;
const float DiffuseMaterialComponent::MaximumShininessClamp = 512.f ;

const std::string DiffuseMaterialComponent::DiffuseMapUniformName = "diffuseMaterial.diffuseMap" ;
const std::string DiffuseMaterialComponent::SpecularUniformName = "diffuseMaterial.specularColor" ;
const std::string DiffuseMaterialComponent::ShininessUniformName = "diffuseMaterial.shininess" ;

DiffuseMaterialComponent::DiffuseMaterialComponent()
    : MaterialComponent() {
    setupRendering() ;
    setupUniforms() ;

    setDiffuseMap(nullptr) ;
    setSpecular(Color(1.f, 1.f, 1.f)) ;
    setShininess(10.f) ;
}

DiffuseMaterialComponent::~DiffuseMaterialComponent() {
    delete m_diffuseMap ;
}

void DiffuseMaterialComponent::updateUniformValues() {
    m_diffuseMap -> activate(DiffuseMapBinding) ;
    m_diffuseMap -> bind() ;
    uniform(DiffuseMapUniformName) -> setInteger(DiffuseMapBinding) ;
    uniform(SpecularUniformName) -> setVec3(specular().toRGB()) ;
    uniform(ShininessUniformName) -> setFloating(shininess()) ;
}

void DiffuseMaterialComponent::setDiffuseMap(const API::Texture2D* diffuse) {
    m_diffuseMap = diffuse ;
    m_diffuseMapUniform -> setInteger(DiffuseMapBinding) ;
}

void DiffuseMaterialComponent::setSpecular(const Color& specular) {
    std::array<float, 4> colorArray = {
        specular.red(),
        specular.green(),
        specular.blue(),
        specular.alpha()
    } ;

    m_specularUniform -> setVec4(colorArray) ;
}

void DiffuseMaterialComponent::setShininess(const float shininess) {
    float shininessClamped = std::clamp(shininess, MinimumShininessClamp, MaximumShininessClamp) ;
    m_shininessUniform -> setFloating(shininessClamped) ;
}

const API::Texture2D* DiffuseMaterialComponent::diffuseMap() const {
    return m_diffuseMap ;
}

Color DiffuseMaterialComponent::specular() const {
    const float* specular = m_specularUniform -> vec4() ;
    return Color(specular[0], specular[1], specular[2], specular[3]) ;
}

float DiffuseMaterialComponent::shininess() const {
    return m_shininessUniform -> floating() ;
}

void DiffuseMaterialComponent::setupUniforms() {
    m_diffuseMapUniform = std::make_shared<Hope::ShaderUniform>() ;
    m_diffuseMapUniform -> setName(DiffuseMapUniformName) ;
    addShaderUniform(m_diffuseMapUniform) ;

    m_specularUniform = std::make_shared<Hope::ShaderUniform>() ;
    m_specularUniform -> setName(SpecularUniformName) ;
    addShaderUniform(m_specularUniform) ;

    m_shininessUniform = std::make_shared<Hope::ShaderUniform>() ;
    m_shininessUniform -> setName(ShininessUniformName) ;
    addShaderUniform(m_shininessUniform) ;
}

void DiffuseMaterialComponent::setupRendering() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>() ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(DirectiveFragmentCode) ;
    shaderProgram -> addVertexShaderCode(BlockBindingsFragmentCode) ;
    shaderProgram -> addVertexShaderCode(BaseDataBlockVertexCode) ;
    shaderProgram -> addVertexShaderCode(ModelDataBlockVertexCode) ;
    shaderProgram -> addVertexShaderCode(DiffuseMapVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(DirectiveFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(BlockBindingsFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(BaseDataBlockVertexCode) ;
    shaderProgram -> addFragmentShaderCode(ModelDataBlockVertexCode) ;
    shaderProgram -> addFragmentShaderCode(AmountLightsFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(LightsDataBlockFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(DiffuseMapFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(renderPass) ;
}
