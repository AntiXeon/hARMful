#include <scene/components/materials/PhongMaterial.hpp>
#include <scene/components/materials/shaders/GL/4.5/Phong.hpp>
#include <memory>

using namespace Hope ;

const std::string PhongMaterial::AmbientUniformName = "ambientColor" ;
const std::string PhongMaterial::DiffuseUniformName = "diffuseColor" ;
const std::string PhongMaterial::SpecularUniformName = "specularColor" ;
const std::string PhongMaterial::ShininessUniformName = "shininess" ;

PhongMaterial::PhongMaterial()
    : Material() {
    setupRendering() ;
    setupUniforms() ;
}

void PhongMaterial::setAmbient(const Color& ambient) {
    std::array<float, 4> colorArray = {
        ambient.red(),
        ambient.green(),
        ambient.blue(),
        ambient.alpha()
    } ;

    m_ambientUniform -> setVec4(colorArray) ;
}

void PhongMaterial::setDiffuse(const Color& diffuse) {
    std::array<float, 4> colorArray = {
        diffuse.red(),
        diffuse.green(),
        diffuse.blue(),
        diffuse.alpha()
    } ;

    m_diffuseUniform -> setVec4(colorArray) ;
}

void PhongMaterial::setSpecular(const Color& specular) {
    std::array<float, 4> colorArray = {
        specular.red(),
        specular.green(),
        specular.blue(),
        specular.alpha()
    } ;

    m_specularUniform -> setVec4(colorArray) ;
}

void PhongMaterial::setShininess(const float shininess) {
    m_shininessUniform -> setFloating(shininess) ;
}

Color PhongMaterial::ambient() const {
    const float* ambient = m_ambientUniform -> vec4() ;
    return Color(ambient[0], ambient[1], ambient[2], ambient[3]) ;
}

Color PhongMaterial::diffuse() const {
    const float* diffuse = m_diffuseUniform -> vec4() ;
    return Color(diffuse[0], diffuse[1], diffuse[2], diffuse[3]) ;
}

Color PhongMaterial::specular() const {
    const float* specular = m_specularUniform -> vec4() ;
    return Color(specular[0], specular[1], specular[2], specular[3]) ;
}

float PhongMaterial::shininess() const {
    return m_shininessUniform -> floating() ;
}

void PhongMaterial::setupUniforms() {
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

void PhongMaterial::setupRendering() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>() ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    shaderProgram -> setVertexShaderCode(PhongVertexCode) ;
    shaderProgram -> setFragmentShaderCode(PhongFragmentCode) ;
    shaderProgram -> link() ;

    std::shared_ptr<RenderTechnique> techniqueGL31 = std::make_shared<RenderTechnique>() ;
    techniqueGL31 -> setAPI(RenderTechnique::GraphicsAPI::OpenGL, 3, 1) ;
    techniqueGL31 -> addRenderPass(renderPass) ;
    effect().addTechnique(techniqueGL31) ;
}
