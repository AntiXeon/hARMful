#include <scene/ogl/rendering/glsl/ubo/LightGLSLDataUBO.hpp>
#include <scene/components/lights/DirectionalLightComponent.hpp>
#include <scene/components/lights/PointLightComponent.hpp>
#include <geometry/points/Point3Df.hpp>
#include <geometry/points/Point4Df.hpp>

using namespace Hope ;
using namespace Hope::GL ;

LightGLSLDataUBO::LightGLSLDataUBO(const GLuint bindingPointIndex)
    : UniformBufferObject(bindingPointIndex) {
    glBindBuffer(GL_UNIFORM_BUFFER, bufferID()) ;
    glBufferData(GL_UNIFORM_BUFFER, size(), data(), GL_DYNAMIC_DRAW) ;
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPointIndex, bufferID()) ;
    glBindBuffer(GL_UNIFORM_BUFFER, 0) ;
}

void LightGLSLDataUBO::setDirectionalLight(
    const uint16_t index,
    const DirectionalLightComponent* light
) {
    m_data.dirLights[index].direction = Mind::Vector4f(light -> direction()).toArray() ;
    m_data.dirLights[index].color = (light -> color()).toRGBA() ;
    m_data.dirLights[index].power_specular[0] = light -> power() ;
    m_data.dirLights[index].power_specular[1] = light -> generateSpecular() ;
}

void LightGLSLDataUBO::setPointLight(
    const uint16_t index,
    const PointLightComponent* light
) {
    m_data.pointLights[index].position = Mind::Vector4f(light -> position()).toArray() ;
    m_data.pointLights[index].color_distance = (light -> color()).toRGBA() ;
    m_data.pointLights[index].color_distance[3] = light -> distance() ;
    m_data.pointLights[index].linAtt_quadAtt_power_specular[0] = light -> linearAttenuation() ;
    m_data.pointLights[index].linAtt_quadAtt_power_specular[1] = light -> quadraticAttenuation() ;
    m_data.pointLights[index].linAtt_quadAtt_power_specular[2] = light -> power() ;
    m_data.pointLights[index].linAtt_quadAtt_power_specular[3] = light -> generateSpecular() ;
}
