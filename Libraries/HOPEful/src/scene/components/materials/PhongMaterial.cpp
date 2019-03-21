#include <scene/components/materials/PhongMaterial.hpp>
#include <scene/components/materials/shaders/GL/3.1/Phong.hpp>
#include <memory>

using namespace Hope ;

const std::string PhongMaterial::AmbientAttribName = "material.ambientColor" ;
const std::string PhongMaterial::DiffuseAttribName = "material.diffuseColor" ;
const std::string PhongMaterial::SpecularAttribName = "material.specularColor" ;
const std::string PhongMaterial::ShininessAttribName = "material.shininess" ;

PhongMaterial::PhongMaterial()
    : Material() {
    setupRendering() ;
    setupAttributes() ;
}

void PhongMaterial::setAmbient(const Color& ambient) {
    std::array<float, 4> colorArray = {
        ambient.red(),
        ambient.green(),
        ambient.blue(),
        ambient.alpha()
    } ;

    m_ambientAttrib -> setVec4(colorArray) ;
}

void PhongMaterial::setDiffuse(const Color& diffuse) {
    std::array<float, 4> colorArray = {
        diffuse.red(),
        diffuse.green(),
        diffuse.blue(),
        diffuse.alpha()
    } ;

    m_diffuseAttrib -> setVec4(colorArray) ;
}

void PhongMaterial::setSpecular(const Color& specular) {
    std::array<float, 4> colorArray = {
        specular.red(),
        specular.green(),
        specular.blue(),
        specular.alpha()
    } ;

    m_specularAttrib -> setVec4(colorArray) ;
}

void PhongMaterial::setShininess(const float shininess) {
    m_shininessAttrib -> setFloating(shininess) ;
}

Color PhongMaterial::ambient() const {
    const float* ambient = m_ambientAttrib -> vec4() ;
    return Color(ambient[0], ambient[1], ambient[2], ambient[3]) ;
}

Color PhongMaterial::diffuse() const {
    const float* diffuse = m_diffuseAttrib -> vec4() ;
    return Color(diffuse[0], diffuse[1], diffuse[2], diffuse[3]) ;
}

Color PhongMaterial::specular() const {
    const float* specular = m_specularAttrib -> vec4() ;
    return Color(specular[0], specular[1], specular[2], specular[3]) ;
}

float PhongMaterial::shininess() const {
    return m_shininessAttrib -> floating() ;
}

void PhongMaterial::setupAttributes() {
    m_ambientAttrib = std::make_shared<Hope::ShaderAttribute>() ;
    m_ambientAttrib -> setName(AmbientAttribName) ;
    addShaderAttribute(m_ambientAttrib) ;

    m_diffuseAttrib = std::make_shared<Hope::ShaderAttribute>() ;
    m_diffuseAttrib -> setName(DiffuseAttribName) ;
    addShaderAttribute(m_diffuseAttrib) ;

    m_specularAttrib = std::make_shared<Hope::ShaderAttribute>() ;
    m_specularAttrib -> setName(SpecularAttribName) ;
    addShaderAttribute(m_specularAttrib) ;

    m_shininessAttrib = std::make_shared<Hope::ShaderAttribute>() ;
    m_shininessAttrib -> setName(ShininessAttribName) ;
    addShaderAttribute(m_shininessAttrib) ;
}

void PhongMaterial::setupRendering() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>() ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    shaderProgram -> setVertexShaderCode(PhongVertexCode) ;
    shaderProgram -> setVertexShaderCode(PhongFragmentCode) ;
    shaderProgram -> link() ;

    std::shared_ptr<RenderTechnique> techniqueGL31 = std::make_shared<RenderTechnique>() ;
    techniqueGL31 -> setAPI(RenderTechnique::GraphicsAPI::OpenGL, 3, 1) ;
    techniqueGL31 -> addRenderPass(renderPass) ;
    effect().addTechnique(techniqueGL31) ;
}
