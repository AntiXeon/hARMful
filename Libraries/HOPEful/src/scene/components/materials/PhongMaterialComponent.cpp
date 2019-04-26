#include <scene/components/materials/PhongMaterialComponent.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/BlockBindings.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/BaseDataBlock.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/ModelDataBlock.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/Directive.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/AmountLights.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/LightsDataBlock.hpp>
#include <scene/components/materials/shaders/GL/4.5/Phong.hpp>
#include <algorithm>
#include <memory>

using namespace Hope ;

const float PhongMaterialComponent::MinimumShininessClamp = 1.f ;
const float PhongMaterialComponent::MaximumShininessClamp = 512.f ;

const std::string PhongMaterialComponent::AmbientUniformName = "phong.ambientColor" ;
const std::string PhongMaterialComponent::DiffuseUniformName = "phong.diffuseColor" ;
const std::string PhongMaterialComponent::SpecularUniformName = "phong.specularColor" ;
const std::string PhongMaterialComponent::ShininessUniformName = "phong.shininess" ;

PhongMaterialComponent::PhongMaterialComponent()
    : MaterialComponent() {
    setupRendering() ;
    setupUniforms() ;

    setAmbient(Color(0.1f, 0.1f, 0.1f)) ;
    setDiffuse(Color(0.5f, 0.5f, 0.5f)) ;
    setSpecular(Color(1.f, 1.f, 1.f)) ;
    setShininess(10.f) ;
}

void PhongMaterialComponent::updateUniformValues(ISceneGraphVisitor*) {
    uniform(AmbientUniformName) -> setVec3(ambient().toRGB()) ;
    uniform(DiffuseUniformName) -> setVec3(diffuse().toRGB()) ;
    uniform(SpecularUniformName) -> setVec3(specular().toRGB()) ;
    uniform(ShininessUniformName) -> setFloating(shininess()) ;
}

void PhongMaterialComponent::setAmbient(const Color& ambient) {
    std::array<float, 4> colorArray = {
        ambient.red(),
        ambient.green(),
        ambient.blue(),
        ambient.alpha()
    } ;

    m_ambientUniform -> setVec4(colorArray) ;
}

void PhongMaterialComponent::setDiffuse(const Color& diffuse) {
    std::array<float, 4> colorArray = {
        diffuse.red(),
        diffuse.green(),
        diffuse.blue(),
        diffuse.alpha()
    } ;

    m_diffuseUniform -> setVec4(colorArray) ;
}

void PhongMaterialComponent::setSpecular(const Color& specular) {
    std::array<float, 4> colorArray = {
        specular.red(),
        specular.green(),
        specular.blue(),
        specular.alpha()
    } ;

    m_specularUniform -> setVec4(colorArray) ;
}

void PhongMaterialComponent::setShininess(const float shininess) {
    float shininessClamped = std::clamp(shininess, MinimumShininessClamp, MaximumShininessClamp) ;
    m_shininessUniform -> setFloating(shininessClamped) ;
}

Color PhongMaterialComponent::ambient() const {
    const float* ambient = m_ambientUniform -> vec4() ;
    return Color(ambient[0], ambient[1], ambient[2], ambient[3]) ;
}

Color PhongMaterialComponent::diffuse() const {
    const float* diffuse = m_diffuseUniform -> vec4() ;
    return Color(diffuse[0], diffuse[1], diffuse[2], diffuse[3]) ;
}

Color PhongMaterialComponent::specular() const {
    const float* specular = m_specularUniform -> vec4() ;
    return Color(specular[0], specular[1], specular[2], specular[3]) ;
}

float PhongMaterialComponent::shininess() const {
    return m_shininessUniform -> floating() ;
}

void PhongMaterialComponent::setupUniforms() {
    m_ambientUniform = std::make_shared<Hope::ShaderUniform>() ;
    m_ambientUniform -> setName(AmbientUniformName) ;
    addShaderUniform(m_ambientUniform) ;

    m_diffuseUniform = std::make_shared<Hope::ShaderUniform>() ;
    m_diffuseUniform -> setName(DiffuseUniformName) ;
    addShaderUniform(m_diffuseUniform) ;

    m_specularUniform = std::make_shared<Hope::ShaderUniform>() ;
    m_specularUniform -> setName(SpecularUniformName) ;
    addShaderUniform(m_specularUniform) ;

    m_shininessUniform = std::make_shared<Hope::ShaderUniform>() ;
    m_shininessUniform -> setName(ShininessUniformName) ;
    addShaderUniform(m_shininessUniform) ;
}

void PhongMaterialComponent::setupRendering() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>() ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(DirectiveFragmentCode) ;
    shaderProgram -> addVertexShaderCode(BlockBindingsFragmentCode) ;
    shaderProgram -> addVertexShaderCode(BaseDataBlockVertexCode) ;
    shaderProgram -> addVertexShaderCode(ModelDataBlockVertexCode) ;
    shaderProgram -> addVertexShaderCode(PhongVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(DirectiveFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(BlockBindingsFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(BaseDataBlockVertexCode) ;
    shaderProgram -> addFragmentShaderCode(ModelDataBlockVertexCode) ;
    shaderProgram -> addFragmentShaderCode(AmountLightsFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(LightsDataBlockFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(PhongFragmentCode) ;
    shaderProgram -> build() ;

    std::shared_ptr<RenderTechnique> techniqueGL31 = std::make_shared<RenderTechnique>() ;
    techniqueGL31 -> setAPI(RenderTechnique::GraphicsAPI::OpenGL, 3, 1) ;
    techniqueGL31 -> addRenderPass(renderPass) ;
    effect().addTechnique(techniqueGL31) ;
}
