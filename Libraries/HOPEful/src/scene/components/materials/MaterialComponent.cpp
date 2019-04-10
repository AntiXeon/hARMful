#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/components/lights/DirectionalLightComponent.hpp>
#include <interfaces/visitors/scenegraph/ISceneGraphVisitor.hpp>
#include <scene/framegraph/ProcessedSceneNode.hpp>
#include <scene/framegraph/RenderRequiredData.hpp>

#include <iostream>

using namespace Hope ;

// Generic uniforms names.
const std::string Hope::MaterialComponent::ModelMatrixParamName = u8"modelMatrix" ;
const std::string Hope::MaterialComponent::ViewMatrixParamName = u8"viewMatrix" ;
const std::string Hope::MaterialComponent::ProjectionMatrixParamName = u8"projectionMatrix" ;
const std::string Hope::MaterialComponent::ModelViewMatrixParamName = u8"modelViewMatrix" ;
const std::string Hope::MaterialComponent::ViewProjectionMatrixParamName = u8"viewProjectionMatrix" ;
const std::string Hope::MaterialComponent::MVPMatrixParamName = u8"mvpMatrix" ;
const std::string Hope::MaterialComponent::InverseModelMatrixParamName = u8"inverseModelMatrix" ;
const std::string Hope::MaterialComponent::InverseViewMatrixParamName = u8"inverseViewMatrix" ;
const std::string Hope::MaterialComponent::InverseProjectionMatrixParamName = u8"inverseProjectionMatrix" ;
const std::string Hope::MaterialComponent::InverseModelViewMatrixParamName = u8"inverseModelViewMatrix" ;
const std::string Hope::MaterialComponent::InverseViewProjectionMatrixParamName = u8"inverseViewProjectionMatrix" ;
const std::string Hope::MaterialComponent::InverseMVPMatrixParamName = u8"inverseMVPMatrix" ;
const std::string Hope::MaterialComponent::ModelNormalMatrixParamName = u8"modelNormalMatrix" ;
const std::string Hope::MaterialComponent::ModelViewNormalMatrixParamName = u8"modelViewNormalMatrix" ;
const std::string Hope::MaterialComponent::ViewportMatrixParamName = u8"viewportMatrix" ;
const std::string Hope::MaterialComponent::InverseViewportMatrixParamName = u8"inverseViewportMatrix" ;
const std::string Hope::MaterialComponent::AspectRatioParamName = u8"aspectRatio" ;
const std::string Hope::MaterialComponent::TimeParamName = u8"time" ;
const std::string Hope::MaterialComponent::EyePositionParamName = u8"eyePosition" ;

// Lighting uniforms names.
const std::string Hope::MaterialComponent::DirectionalLightParamName = "dirLight" ;
const std::string Hope::MaterialComponent::PointLightParamName = "pointLight" ;
const std::string Hope::MaterialComponent::SpotLightParamName = "spotLight" ;
const std::string Hope::MaterialComponent::HemisphereLightParamName = "hemiLight" ;
const std::string Hope::MaterialComponent::LightAmbientParamName = "ambient" ;
const std::string Hope::MaterialComponent::LightDiffuseParamName = "diffuse" ;
const std::string Hope::MaterialComponent::LightSpecularParamName = "specular" ;
const std::string Hope::MaterialComponent::LightDirectionParamName = "direction" ;

MaterialComponent::MaterialComponent()
    : Component(Hope::MaterialComponentType) {
    setupDefaultUniforms() ;
}

void MaterialComponent::accept(ISceneGraphVisitor* visitor) {
    updateUniformValues(visitor) ;
    visitor -> visit(this) ;
}

bool MaterialComponent::isShareable() const {
    return true ;
}

RenderEffect& MaterialComponent::effect() {
    return m_effect ;
}

void MaterialComponent::addShaderAttribute(const std::shared_ptr<Hope::ShaderAttribute> attrib) {
    m_shaderAttribs.insert(attrib) ;
}

void MaterialComponent::removeShaderAttribute(const std::shared_ptr<Hope::ShaderAttribute> attrib) {
    m_shaderAttribs.erase(attrib) ;
}

void MaterialComponent::addShaderUniform(const std::shared_ptr<Hope::ShaderUniform> uniform) {
    m_shaderUniforms.insert(uniform) ;
}

void MaterialComponent::removeShaderUniform(const std::shared_ptr<Hope::ShaderUniform> uniform) {
    m_shaderUniforms.erase(uniform) ;
}

void MaterialComponent::setupDefaultUniforms() {
    // uniform mat4 modelMatrix ;
    m_modelMatrix = std::make_shared<Hope::ShaderUniform>() ;
    m_modelMatrix -> setName(ModelMatrixParamName) ;
    addShaderUniform(m_modelMatrix) ;

    // uniform mat4 viewMatrix ;
    m_viewMatrix = std::make_shared<Hope::ShaderUniform>() ;
    m_viewMatrix -> setName(ViewMatrixParamName) ;
    addShaderUniform(m_viewMatrix) ;

    // uniform mat4 projectionMatrix ;
    m_projectionMatrix = std::make_shared<Hope::ShaderUniform>() ;
    m_projectionMatrix -> setName(ProjectionMatrixParamName) ;
    addShaderUniform(m_projectionMatrix) ;

    // uniform mat4 modelViewMatrix ;
    m_modelViewMatrix = std::make_shared<Hope::ShaderUniform>() ;
    m_modelViewMatrix -> setName(ModelViewMatrixParamName) ;
    addShaderUniform(m_modelViewMatrix) ;

    // uniform mat4 viewProjectionMatrix ;
    m_viewProjectionMatrix = std::make_shared<Hope::ShaderUniform>() ;
    m_viewProjectionMatrix -> setName(ViewProjectionMatrixParamName) ;
    addShaderUniform(m_viewProjectionMatrix) ;

    // uniform mat4 mvpMatrix ;
    m_mvpMatrix = std::make_shared<Hope::ShaderUniform>() ;
    m_mvpMatrix -> setName(MVPMatrixParamName) ;
    addShaderUniform(m_mvpMatrix) ;

    // uniform mat4 inverseModelMatrix ;
    m_inverseModelMatrix = std::make_shared<Hope::ShaderUniform>() ;
    m_inverseModelMatrix -> setName(InverseModelMatrixParamName) ;
    addShaderUniform(m_inverseModelMatrix) ;

    // uniform mat4 inverseViewMatrix ;
    m_inverseViewMatrix = std::make_shared<Hope::ShaderUniform>() ;
    m_inverseViewMatrix -> setName(InverseViewMatrixParamName) ;
    addShaderUniform(m_inverseViewMatrix) ;

    // uniform mat4 inverseProjectionMatrix ;
    m_inverseProjectionMatrix = std::make_shared<Hope::ShaderUniform>() ;
    m_inverseProjectionMatrix -> setName(InverseProjectionMatrixParamName) ;
    addShaderUniform(m_inverseProjectionMatrix) ;

    // uniform mat4 inverseModelViewMatrix ;
    m_inverseModelViewMatrix = std::make_shared<Hope::ShaderUniform>() ;
    m_inverseModelViewMatrix -> setName(InverseModelViewMatrixParamName) ;
    addShaderUniform(m_inverseModelViewMatrix) ;

    // uniform mat4 inverseViewProjectionMatrix ;
    m_inverseViewProjectionMatrix = std::make_shared<Hope::ShaderUniform>() ;
    m_inverseViewProjectionMatrix -> setName(InverseViewProjectionMatrixParamName) ;
    addShaderUniform(m_inverseViewProjectionMatrix) ;

    // uniform mat4 inverseMVPMatrix ;
    m_inverseMVPMatrix = std::make_shared<Hope::ShaderUniform>() ;
    m_inverseMVPMatrix -> setName(InverseMVPMatrixParamName) ;
    addShaderUniform(m_inverseMVPMatrix) ;

    // uniform mat3 modelNormalMatrix ;
    m_modelNormalMatrix = std::make_shared<Hope::ShaderUniform>() ;
    m_modelNormalMatrix -> setName(ModelNormalMatrixParamName) ;
    addShaderUniform(m_modelNormalMatrix) ;

    // uniform mat3 modelViewNormalMatrix ;
    m_modelViewNormalMatrix = std::make_shared<Hope::ShaderUniform>() ;
    m_modelViewNormalMatrix -> setName(ModelViewNormalMatrixParamName) ;
    addShaderUniform(m_modelViewNormalMatrix) ;

    // uniform mat4 viewportMatrix ;
    m_viewportMatrix = std::make_shared<Hope::ShaderUniform>() ;
    m_viewportMatrix -> setName(ViewportMatrixParamName) ;
    addShaderUniform(m_viewportMatrix) ;

    // uniform mat4 inverseViewportMatrix ;
    m_inverseViewportMatrix = std::make_shared<Hope::ShaderUniform>() ;
    m_inverseViewportMatrix -> setName(InverseViewportMatrixParamName) ;
    addShaderUniform(m_inverseViewportMatrix) ;

    // uniform float aspectRatio ;
    m_aspectRatio = std::make_shared<Hope::ShaderUniform>() ;
    m_aspectRatio -> setName(AspectRatioParamName) ;
    addShaderUniform(m_aspectRatio) ;

    // uniform float time ;
    m_time = std::make_shared<Hope::ShaderUniform>() ;
    m_time -> setName(TimeParamName) ;
    addShaderUniform(m_time) ;

    // uniform vec3 eyePosition ;
    m_eyePosition = std::make_shared<Hope::ShaderUniform>() ;
    m_eyePosition -> setName(EyePositionParamName) ;
    addShaderUniform(m_eyePosition) ;
}

void MaterialComponent::updateUniformValues(ISceneGraphVisitor* visitor) {
    Hope::ProcessedSceneNode& node = visitor -> processedNode() ;
    Hope::RenderRequiredData& data = visitor -> requiredData() ;

    // Model matrix.
    m_modelMatrix -> setMat4(node.worldMatrix.toArray()) ;

    // View matrix.
    m_viewMatrix -> setMat4(data.viewMatrix.toArray()) ;

    // Projection matrix.
    m_projectionMatrix -> setMat4(data.projectionMatrix.toArray()) ;

    // Model view matrix.
    Mind::Matrix4x4f modelViewMatrix = node.worldMatrix * data.viewMatrix ;
    m_modelViewMatrix -> setMat4(modelViewMatrix.toArray()) ;

    // View projection matrix.
    m_viewProjectionMatrix -> setMat4(data.viewProjectionMatrix.toArray()) ;

    // Model view projection matrix.
    Mind::Matrix4x4f modelViewProjectionMatrix = node.worldMatrix * data.viewProjectionMatrix ;
    m_mvpMatrix -> setMat4(modelViewProjectionMatrix.toArray()) ;

    // Inverse model matrix.
    Mind::Matrix4x4f inverseModelMatrix ;
    node.worldMatrix.inverse(inverseModelMatrix) ;
    m_inverseModelMatrix -> setMat4(inverseModelMatrix.toArray()) ;

    // Inverse view matrix.
    m_inverseViewMatrix -> setMat4(data.inverseViewMatrix.toArray()) ;

    // Inverse projection matrix.
    m_inverseProjectionMatrix -> setMat4(data.inverseProjectionMatrix.toArray()) ;

    // Inverse model view matrix.
    Mind::Matrix4x4f inverseModelViewMatrix ;
    modelViewMatrix.inverse(inverseModelViewMatrix) ;
    m_inverseModelViewMatrix -> setMat4(inverseModelViewMatrix.toArray()) ;

    // Inverse view projection matrix.
    m_inverseViewProjectionMatrix -> setMat4(data.inverseViewProjectionMatrix.toArray()) ;

    // Inverse model view projection matrix.
    Mind::Matrix4x4f inverseModelViewProjectionMatrix ;
    modelViewProjectionMatrix.inverse(inverseModelViewProjectionMatrix) ;
    m_inverseMVPMatrix  -> setMat4(inverseModelViewProjectionMatrix.toArray()) ;

    // Normal matrix.
    Mind::Matrix4x4f normalMatrix ;
    inverseModelViewMatrix.transposed(normalMatrix) ;

    // Model normal matrix.
    Mind::Matrix4x4f modelNormalMatrix = node.worldMatrix * normalMatrix ;
    m_modelNormalMatrix -> setMat4(modelNormalMatrix.toArray()) ;

    // Model view normal matrix.
    Mind::Matrix4x4f modelViewNormalMatrix = modelViewMatrix * normalMatrix ;
    m_modelViewNormalMatrix -> setMat4(modelViewNormalMatrix.toArray()) ;

    // Viewport matrix.
    m_viewportMatrix -> setMat3(data.viewportMatrix.toArray()) ;

    // Inverse viewport matrix.
    m_inverseViewportMatrix -> setMat3(data.inverseViewportMatrix.toArray()) ;

    // Aspect ratio.
    m_aspectRatio -> setFloating(data.aspectRatio) ;

    // Elapsed time.
    m_time -> setFloating(data.time) ;

    // Eye position.
    m_eyePosition -> setVec3(data.eyePosition.toArray()) ;
}
