#include <scene/components/materials/PhongMaterial.hpp>

using namespace Hope ;

const std::string PhongMaterial::AmbientParamName = "ambientColor" ;
const std::string PhongMaterial::DiffuseParamName = "diffuseColor" ;
const std::string PhongMaterial::SpecularParamName = "specularColor" ;
const std::string PhongMaterial::ShininessParamName = "shininess" ;

PhongMaterial::PhongMaterial()
    : Material() {
    // Add the specific shader parameters here: diffuse, ambient, specular and
    // shininess.
    m_ambientParam = std::make_shared<Hope::ShaderParameter>() ;
    m_ambientParam -> setName(AmbientParamName) ;
    addShaderParameter(m_ambientParam) ;

    m_diffuseParam = std::make_shared<Hope::ShaderParameter>() ;
    m_diffuseParam -> setName(DiffuseParamName) ;
    addShaderParameter(m_diffuseParam) ;

    m_specularParam = std::make_shared<Hope::ShaderParameter>() ;
    m_specularParam -> setName(SpecularParamName) ;
    addShaderParameter(m_specularParam) ;

    m_shininessParam = std::make_shared<Hope::ShaderParameter>() ;
    m_shininessParam -> setName(ShininessParamName) ;
    addShaderParameter(m_shininessParam) ;
}

void PhongMaterial::setAmbient(const Color& ambient) {
    std::array<float, 4> colorArray = {
        ambient.red(),
        ambient.green(),
        ambient.blue(),
        ambient.alpha()
    } ;

    m_ambientParam -> setVec4(colorArray) ;
}

void PhongMaterial::setDiffuse(const Color& diffuse) {
    std::array<float, 4> colorArray = {
        diffuse.red(),
        diffuse.green(),
        diffuse.blue(),
        diffuse.alpha()
    } ;

    m_diffuseParam -> setVec4(colorArray) ;
}

void PhongMaterial::setSpecular(const Color& specular) {
    std::array<float, 4> colorArray = {
        specular.red(),
        specular.green(),
        specular.blue(),
        specular.alpha()
    } ;

    m_specularParam -> setVec4(colorArray) ;
}

void PhongMaterial::setShininess(const float shininess) {
    m_shininessParam -> setFloating(shininess) ;
}

Color PhongMaterial::ambient() const {
    const float* ambient = m_ambientParam -> vec4() ;
    return Color(ambient[0], ambient[1], ambient[2], ambient[3]) ;
}

Color PhongMaterial::diffuse() const {
    const float* diffuse = m_diffuseParam -> vec4() ;
    return Color(diffuse[0], diffuse[1], diffuse[2], diffuse[3]) ;
}

Color PhongMaterial::specular() const {
    const float* specular = m_specularParam -> vec4() ;
    return Color(specular[0], specular[1], specular[2], specular[3]) ;
}

float PhongMaterial::shininess() const {
    return m_shininessParam -> floating() ;
}
