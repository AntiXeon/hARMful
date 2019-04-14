#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/components/lights/DirectionalLightComponent.hpp>
#include <interfaces/visitors/scenegraph/ISceneGraphVisitor.hpp>
#include <scene/framegraph/ProcessedSceneNode.hpp>
#include <scene/framegraph/RenderRequiredData.hpp>
#include <scene/SceneCache.hpp>
#include <utils/StringExt.hpp>

#include <iostream>

using namespace Hope ;

const UniformNames MaterialComponent::Uniforms ;

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
    const std::vector<std::string>& names = Uniforms.names() ;
    size_t amountNames = names.size() ;

    for (size_t index = 0 ; index < amountNames ; ++index) {
        const std::string& name = names[index] ;
        m_shaderUniforms[name] = std::make_shared<Hope::ShaderUniform>() ;
        m_shaderUniforms[name] -> setName(name) ;
        addShaderUniform(m_shaderUniforms[name]) ;
    }
}

void MaterialComponent::updateUniformValues(ISceneGraphVisitor* visitor) {
    Hope::ProcessedSceneNode& node = visitor -> processedNode() ;
    Hope::RenderRequiredData& data = visitor -> requiredData() ;
    Hope::SceneCache* sceneCache = data.cache ;

    // Model matrix.
    m_shaderUniforms[UniformNames::ModelMatrixParamName()] -> setMat4(node.worldMatrix.toArray()) ;

    // View matrix.
    m_shaderUniforms[UniformNames::ViewMatrixParamName()] -> setMat4(data.viewMatrix.toArray()) ;

    // Projection matrix.
    m_shaderUniforms[UniformNames::ProjectionMatrixParamName()] -> setMat4(data.projectionMatrix.toArray()) ;

    // Model view matrix.
    Mind::Matrix4x4f modelViewMatrix = node.worldMatrix * data.viewMatrix ;
    m_shaderUniforms[UniformNames::ModelViewMatrixParamName()] -> setMat4(modelViewMatrix.toArray()) ;

    // View projection matrix.
    m_shaderUniforms[UniformNames::ViewProjectionMatrixParamName()] -> setMat4(data.viewProjectionMatrix.toArray()) ;

    // Model view projection matrix.
    Mind::Matrix4x4f modelViewProjectionMatrix = node.worldMatrix * data.viewProjectionMatrix ;
    m_shaderUniforms[UniformNames::MVPMatrixParamName()] -> setMat4(modelViewProjectionMatrix.toArray()) ;

    // Inverse model matrix.
    Mind::Matrix4x4f inverseModelMatrix ;
    node.worldMatrix.inverse(inverseModelMatrix) ;
    m_shaderUniforms[UniformNames::InverseModelMatrixParamName()] -> setMat4(inverseModelMatrix.toArray()) ;

    // Inverse view matrix.
    m_shaderUniforms[UniformNames::InverseViewMatrixParamName()] -> setMat4(data.inverseViewMatrix.toArray()) ;

    // Inverse projection matrix.
    m_shaderUniforms[UniformNames::InverseProjectionMatrixParamName()] -> setMat4(data.inverseProjectionMatrix.toArray()) ;

    // Inverse model view matrix.
    Mind::Matrix4x4f inverseModelViewMatrix ;
    modelViewMatrix.inverse(inverseModelViewMatrix) ;
    m_shaderUniforms[UniformNames::InverseModelViewMatrixParamName()] -> setMat4(inverseModelViewMatrix.toArray()) ;

    // Inverse view projection matrix.
    m_shaderUniforms[UniformNames::InverseViewProjectionMatrixParamName()] -> setMat4(data.inverseViewProjectionMatrix.toArray()) ;

    // Inverse model view projection matrix.
    Mind::Matrix4x4f inverseModelViewProjectionMatrix ;
    modelViewProjectionMatrix.inverse(inverseModelViewProjectionMatrix) ;
    m_shaderUniforms[UniformNames::InverseMVPMatrixParamName()]  -> setMat4(inverseModelViewProjectionMatrix.toArray()) ;

    // Normal matrix.
    Mind::Matrix4x4f normalMatrix ;
    inverseModelViewMatrix.transposed(normalMatrix) ;
    m_shaderUniforms[UniformNames::NormalMatrixParamName()] -> setMat4(normalMatrix.toArray()) ;

    // Model normal matrix.
    Mind::Matrix4x4f modelNormalMatrix = node.worldMatrix * normalMatrix ;
    m_shaderUniforms[UniformNames::ModelNormalMatrixParamName()] -> setMat4(modelNormalMatrix.toArray()) ;

    // Model view normal matrix.
    Mind::Matrix4x4f modelViewNormalMatrix = modelViewMatrix * normalMatrix ;
    m_shaderUniforms[UniformNames::ModelViewNormalMatrixParamName()] -> setMat4(modelViewNormalMatrix.toArray()) ;

    // Viewport matrix.
    m_shaderUniforms[UniformNames::ViewportMatrixParamName()] -> setMat3(data.viewportMatrix.toArray()) ;

    // Inverse viewport matrix.
    m_shaderUniforms[UniformNames::InverseViewportMatrixParamName()] -> setMat3(data.inverseViewportMatrix.toArray()) ;

    // Aspect ratio.
    m_shaderUniforms[UniformNames::AspectRatioParamName()] -> setFloating(data.aspectRatio) ;

    // Elapsed time.
    m_shaderUniforms[UniformNames::TimeParamName()] -> setFloating(data.time) ;

    // Eye position.
    m_shaderUniforms[UniformNames::EyePositionParamName()] -> setVec3(data.eyePosition.toArray()) ;


    // Lights.
    int dirLampIndex = 0 ;
    auto dirLights = sceneCache -> directionalLights() ;

    // Amount directional lights.
    m_shaderUniforms[UniformNames::AmountDirectionalLightsParamName()] -> setInteger(dirLights.size()) ;

    for (DirectionalLightComponent* light : dirLights) {
        std::string indexString = "[" + Doom::StringExt::ToStringi(dirLampIndex) + "]." ;
        m_shaderUniforms[UniformNames::DirectionalLightParamName() + indexString + UniformNames::LightColorParamName()] -> setVec3((light -> color()).toRGB()) ;
        m_shaderUniforms[UniformNames::DirectionalLightParamName() + indexString + UniformNames::LightPowerParamName()] -> setFloating(light -> power()) ;
        m_shaderUniforms[UniformNames::DirectionalLightParamName() + indexString + UniformNames::LightGenerateSpecularParamName()] -> setBoolean(light -> generateSpecular()) ;
        m_shaderUniforms[UniformNames::DirectionalLightParamName() + indexString + UniformNames::LightDirectionParamName()] -> setVec3((light -> direction()).toArray()) ;
        dirLampIndex++ ;
    }

    updateAdditionalUniformValues(visitor) ;
}
