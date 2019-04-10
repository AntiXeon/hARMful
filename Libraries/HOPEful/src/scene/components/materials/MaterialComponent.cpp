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


const std::string Hope::MaterialComponent::UniformNames[] = {
    Hope::MaterialComponent::ModelMatrixParamName,
    Hope::MaterialComponent::ViewMatrixParamName,
    Hope::MaterialComponent::ProjectionMatrixParamName,
    Hope::MaterialComponent::ModelViewMatrixParamName,
    Hope::MaterialComponent::ViewProjectionMatrixParamName,
    Hope::MaterialComponent::MVPMatrixParamName,
    Hope::MaterialComponent::InverseModelMatrixParamName,
    Hope::MaterialComponent::InverseViewMatrixParamName,
    Hope::MaterialComponent::InverseProjectionMatrixParamName,
    Hope::MaterialComponent::InverseModelViewMatrixParamName,
    Hope::MaterialComponent::InverseViewProjectionMatrixParamName,
    Hope::MaterialComponent::InverseMVPMatrixParamName,
    Hope::MaterialComponent::ModelNormalMatrixParamName,
    Hope::MaterialComponent::ModelViewNormalMatrixParamName,
    Hope::MaterialComponent::ViewportMatrixParamName,
    Hope::MaterialComponent::InverseViewportMatrixParamName,
    Hope::MaterialComponent::AspectRatioParamName,
    Hope::MaterialComponent::TimeParamName,
    Hope::MaterialComponent::EyePositionParamName
} ;

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
    m_shaderAttribs[attrib -> name()] = attrib ;
}

void MaterialComponent::removeShaderAttribute(const std::shared_ptr<Hope::ShaderAttribute> attrib) {
    m_shaderAttribs.erase(attrib -> name()) ;
}

void MaterialComponent::addShaderUniform(const std::shared_ptr<Hope::ShaderUniform> uniform) {
    m_shaderUniforms[uniform -> name()] = uniform ;
}

void MaterialComponent::removeShaderUniform(const std::shared_ptr<Hope::ShaderUniform> uniform) {
    m_shaderUniforms.erase(uniform -> name()) ;
}

void MaterialComponent::setupDefaultUniforms() {
    for (unsigned short index = 0 ; index < MaterialComponent::AmountUniformNames ; ++index) {
        const std::string& name = UniformNames[index] ;
        m_shaderUniforms[name] = std::make_shared<Hope::ShaderUniform>() ;
        m_shaderUniforms[name] -> setName(name) ;
        addShaderUniform(m_shaderUniforms[name]) ;
    }
}

void MaterialComponent::updateUniformValues(ISceneGraphVisitor* visitor) {
    Hope::ProcessedSceneNode& node = visitor -> processedNode() ;
    Hope::RenderRequiredData& data = visitor -> requiredData() ;

    // Model matrix.
    m_shaderUniforms[ModelMatrixParamName] -> setMat4(node.worldMatrix.toArray()) ;

    // View matrix.
    m_shaderUniforms[ViewMatrixParamName] -> setMat4(data.viewMatrix.toArray()) ;

    // Projection matrix.
    m_shaderUniforms[ProjectionMatrixParamName] -> setMat4(data.projectionMatrix.toArray()) ;

    // Model view matrix.
    Mind::Matrix4x4f modelViewMatrix = node.worldMatrix * data.viewMatrix ;
    m_shaderUniforms[ModelViewMatrixParamName] -> setMat4(modelViewMatrix.toArray()) ;

    // View projection matrix.
    m_shaderUniforms[ViewProjectionMatrixParamName] -> setMat4(data.viewProjectionMatrix.toArray()) ;

    // Model view projection matrix.
    Mind::Matrix4x4f modelViewProjectionMatrix = node.worldMatrix * data.viewProjectionMatrix ;
    m_shaderUniforms[MVPMatrixParamName] -> setMat4(modelViewProjectionMatrix.toArray()) ;

    // Inverse model matrix.
    Mind::Matrix4x4f inverseModelMatrix ;
    node.worldMatrix.inverse(inverseModelMatrix) ;
    m_shaderUniforms[InverseModelMatrixParamName] -> setMat4(inverseModelMatrix.toArray()) ;

    // Inverse view matrix.
    m_shaderUniforms[InverseViewMatrixParamName] -> setMat4(data.inverseViewMatrix.toArray()) ;

    // Inverse projection matrix.
    m_shaderUniforms[InverseProjectionMatrixParamName] -> setMat4(data.inverseProjectionMatrix.toArray()) ;

    // Inverse model view matrix.
    Mind::Matrix4x4f inverseModelViewMatrix ;
    modelViewMatrix.inverse(inverseModelViewMatrix) ;
    m_shaderUniforms[InverseModelViewMatrixParamName] -> setMat4(inverseModelViewMatrix.toArray()) ;

    // Inverse view projection matrix.
    m_shaderUniforms[InverseViewProjectionMatrixParamName] -> setMat4(data.inverseViewProjectionMatrix.toArray()) ;

    // Inverse model view projection matrix.
    Mind::Matrix4x4f inverseModelViewProjectionMatrix ;
    modelViewProjectionMatrix.inverse(inverseModelViewProjectionMatrix) ;
    m_shaderUniforms[InverseMVPMatrixParamName]  -> setMat4(inverseModelViewProjectionMatrix.toArray()) ;

    // Normal matrix.
    Mind::Matrix4x4f normalMatrix ;
    inverseModelViewMatrix.transposed(normalMatrix) ;

    // Model normal matrix.
    Mind::Matrix4x4f modelNormalMatrix = node.worldMatrix * normalMatrix ;
    m_shaderUniforms[ModelNormalMatrixParamName] -> setMat4(modelNormalMatrix.toArray()) ;

    // Model view normal matrix.
    Mind::Matrix4x4f modelViewNormalMatrix = modelViewMatrix * normalMatrix ;
    m_shaderUniforms[ModelViewNormalMatrixParamName] -> setMat4(modelViewNormalMatrix.toArray()) ;

    // Viewport matrix.
    m_shaderUniforms[ViewportMatrixParamName] -> setMat3(data.viewportMatrix.toArray()) ;

    // Inverse viewport matrix.
    m_shaderUniforms[InverseViewportMatrixParamName] -> setMat3(data.inverseViewportMatrix.toArray()) ;

    // Aspect ratio.
    m_shaderUniforms[AspectRatioParamName] -> setFloating(data.aspectRatio) ;

    // Elapsed time.
    m_shaderUniforms[TimeParamName] -> setFloating(data.time) ;

    // Eye position.
    m_shaderUniforms[EyePositionParamName] -> setVec3(data.eyePosition.toArray()) ;
}
