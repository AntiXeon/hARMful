#include <scene/components/materials/Material.hpp>
#include <interfaces/visitors/scenegraph/ISceneGraphVisitor.hpp>
#include <scene/framegraph/ProcessedSceneNode.hpp>
#include <scene/framegraph/RenderRequiredData.hpp>

using namespace Hope ;

const std::string Hope::Material::ModelMatrixParamName = u8"modelMatrix" ;
const std::string Hope::Material::ViewMatrixParamName = u8"viewMatrix" ;
const std::string Hope::Material::ProjectionMatrixParamName = u8"projectionMatrix" ;
const std::string Hope::Material::ModelViewMatrixParamName = u8"modelViewMatrix" ;
const std::string Hope::Material::ViewProjectionMatrixParamName = u8"viewProjectionMatrix" ;
const std::string Hope::Material::MVPMatrixParamName = u8"mvpMatrix" ;
const std::string Hope::Material::InverseModelMatrixParamName = u8"inverseModelMatrix" ;
const std::string Hope::Material::InverseViewMatrixParamName = u8"inverseViewMatrix" ;
const std::string Hope::Material::InverseProjectionMatrixParamName = u8"inverseProjectionMatrix" ;
const std::string Hope::Material::InverseModelViewMatrixParamName = u8"inverseModelViewMatrix" ;
const std::string Hope::Material::InverseViewProjectionMatrixParamName = u8"inverseViewProjectionMatrix" ;
const std::string Hope::Material::InverseMVPMatrixParamName = u8"inverseMVPMatrix" ;
const std::string Hope::Material::ModelNormalMatrixParamName = u8"modelNormalMatrix" ;
const std::string Hope::Material::ModelViewNormalMatrixParamName = u8"modelViewNormalMatrix" ;
const std::string Hope::Material::ViewportMatrixParamName = u8"viewportMatrix" ;
const std::string Hope::Material::InverseViewportMatrixParamName = u8"inverseViewportMatrix" ;
const std::string Hope::Material::AspectRatioParamName = u8"aspectRatio" ;
const std::string Hope::Material::TimeParamName = u8"time" ;
const std::string Hope::Material::EyePositionParamName = u8"eyePosition" ;

Material::Material()
    : Component(Hope::MaterialComponentType) {
    setupDefaultParameters() ;
}

void Material::accept(ISceneGraphVisitor* visitor) {
    updateParameterValues(visitor) ;
    visitor -> visit(this) ;
}

bool Material::isShareable() const {
    return true ;
}

const RenderEffect* Material::effect() const {
    return &m_effect ;
}

void Material::addShaderParameter(const std::shared_ptr<Hope::ShaderParameter> param) {
    m_shaderParams.insert(param) ;
}

void Material::removeShaderParameter(const std::shared_ptr<Hope::ShaderParameter> param) {
    m_shaderParams.erase(param) ;
}

void Material::setupDefaultParameters() {
    // uniform mat4 modelMatrix ;
    m_modelMatrix = std::make_shared<Hope::ShaderParameter>() ;
    m_modelMatrix -> setName(ModelMatrixParamName) ;
    addShaderParameter(m_modelMatrix) ;

    // uniform mat4 viewMatrix ;
    m_viewMatrix = std::make_shared<Hope::ShaderParameter>() ;
    m_viewMatrix -> setName(ViewMatrixParamName) ;
    addShaderParameter(m_viewMatrix) ;

    // uniform mat4 projectionMatrix ;
    m_projectionMatrix = std::make_shared<Hope::ShaderParameter>() ;
    m_projectionMatrix -> setName(ProjectionMatrixParamName) ;
    addShaderParameter(m_projectionMatrix) ;

    // uniform mat4 modelViewMatrix ;
    m_modelViewMatrix = std::make_shared<Hope::ShaderParameter>() ;
    m_modelViewMatrix -> setName(ModelViewMatrixParamName) ;
    addShaderParameter(m_modelViewMatrix) ;

    // uniform mat4 viewProjectionMatrix ;
    m_viewProjectionMatrix = std::make_shared<Hope::ShaderParameter>() ;
    m_viewProjectionMatrix -> setName(ViewProjectionMatrixParamName) ;
    addShaderParameter(m_viewProjectionMatrix) ;

    // uniform mat4 mvpMatrix ;
    m_mvpMatrix = std::make_shared<Hope::ShaderParameter>() ;
    m_mvpMatrix -> setName(MVPMatrixParamName) ;
    addShaderParameter(m_mvpMatrix) ;

    // uniform mat4 inverseModelMatrix ;
    m_inverseModelMatrix = std::make_shared<Hope::ShaderParameter>() ;
    m_inverseModelMatrix -> setName(InverseModelMatrixParamName) ;
    addShaderParameter(m_inverseModelMatrix) ;

    // uniform mat4 inverseViewMatrix ;
    m_inverseViewMatrix = std::make_shared<Hope::ShaderParameter>() ;
    m_inverseViewMatrix -> setName(InverseViewMatrixParamName) ;
    addShaderParameter(m_inverseViewMatrix) ;

    // uniform mat4 inverseProjectionMatrix ;
    m_inverseProjectionMatrix = std::make_shared<Hope::ShaderParameter>() ;
    m_inverseProjectionMatrix -> setName(InverseProjectionMatrixParamName) ;
    addShaderParameter(m_inverseProjectionMatrix) ;

    // uniform mat4 inverseModelViewMatrix ;
    m_inverseModelViewMatrix = std::make_shared<Hope::ShaderParameter>() ;
    m_inverseModelViewMatrix -> setName(InverseModelViewMatrixParamName) ;
    addShaderParameter(m_inverseModelViewMatrix) ;

    // uniform mat4 inverseViewProjectionMatrix ;
    m_inverseViewProjectionMatrix = std::make_shared<Hope::ShaderParameter>() ;
    m_inverseViewProjectionMatrix -> setName(InverseViewProjectionMatrixParamName) ;
    addShaderParameter(m_inverseViewProjectionMatrix) ;

    // uniform mat4 inverseMVPMatrix ;
    m_inverseMVPMatrix = std::make_shared<Hope::ShaderParameter>() ;
    m_inverseMVPMatrix -> setName(InverseMVPMatrixParamName) ;
    addShaderParameter(m_inverseMVPMatrix) ;

    // uniform mat3 modelNormalMatrix ;
    m_modelNormalMatrix = std::make_shared<Hope::ShaderParameter>() ;
    m_modelNormalMatrix -> setName(ModelNormalMatrixParamName) ;
    addShaderParameter(m_modelNormalMatrix) ;

    // uniform mat3 modelViewNormalMatrix ;
    m_modelViewNormalMatrix = std::make_shared<Hope::ShaderParameter>() ;
    m_modelViewNormalMatrix -> setName(ModelViewNormalMatrixParamName) ;
    addShaderParameter(m_modelViewNormalMatrix) ;

    // uniform mat4 viewportMatrix ;
    m_viewportMatrix = std::make_shared<Hope::ShaderParameter>() ;
    m_viewportMatrix -> setName(ViewportMatrixParamName) ;
    addShaderParameter(m_viewportMatrix) ;

    // uniform mat4 inverseViewportMatrix ;
    m_inverseViewportMatrix = std::make_shared<Hope::ShaderParameter>() ;
    m_inverseViewportMatrix -> setName(InverseViewportMatrixParamName) ;
    addShaderParameter(m_inverseViewportMatrix) ;

    // uniform float aspectRatio ;
    m_aspectRatio = std::make_shared<Hope::ShaderParameter>() ;
    m_aspectRatio -> setName(AspectRatioParamName) ;
    addShaderParameter(m_aspectRatio) ;

    // uniform float time ;
    m_time = std::make_shared<Hope::ShaderParameter>() ;
    m_time -> setName(TimeParamName) ;
    addShaderParameter(m_time) ;

    // uniform vec3 eyePosition ;
    m_eyePosition = std::make_shared<Hope::ShaderParameter>() ;
    m_eyePosition -> setName(EyePositionParamName) ;
    addShaderParameter(m_eyePosition) ;
}

void Material::updateParameterValues(ISceneGraphVisitor* visitor) {
    Hope::ProcessedSceneNode& node = visitor -> processedNode() ;
    Hope::RenderRequiredData& data = visitor -> requiredData() ;

    // Model matrix.
    m_modelMatrix -> setMat4(node.worldMatrix.toArray()) ;

    // View matrix.
    m_viewMatrix -> setMat4(data.viewMatrix.toArray()) ;

    // Projection matrix.
    m_projectionMatrix -> setMat4(data.projectionMatrix.toArray()) ;

    // Model view matrix.
    Mind::Matrix4x4f modelViewMatrix = data.viewMatrix * node.worldMatrix ;
    m_modelViewMatrix -> setMat4(modelViewMatrix.toArray()) ;

    // View projection matrix.
    Mind::Matrix4x4f viewProjectionMatrix = data.projectionMatrix * data.viewMatrix  ;
    m_viewProjectionMatrix -> setMat4(viewProjectionMatrix.toArray()) ;

    // Model view projection matrix.
    Mind::Matrix4x4f modelViewProjectionMatrix = viewProjectionMatrix * node.worldMatrix ;
    m_mvpMatrix -> setMat4(modelViewProjectionMatrix.toArray()) ;

    // Inverse model matrix.
    Mind::Matrix4x4f inverseModelMatrix ;
    node.worldMatrix.inverse(inverseModelMatrix) ;
    m_inverseModelMatrix -> setMat4(inverseModelMatrix.toArray()) ;

    // Inverse view matrix.
    Mind::Matrix4x4f inverseViewMatrix ;
    data.viewMatrix.inverse(inverseViewMatrix) ;
    m_inverseViewMatrix -> setMat4(inverseViewMatrix.toArray()) ;

    // Inverse projection matrix.
    Mind::Matrix4x4f inverseProjectionMatrix ;
    data.projectionMatrix.inverse(inverseProjectionMatrix) ;
    m_inverseProjectionMatrix -> setMat4(inverseProjectionMatrix.toArray()) ;

    // Inverse model view matrix.
    Mind::Matrix4x4f inverseModelViewMatrix ;
    modelViewMatrix.inverse(inverseModelViewMatrix) ;
    m_inverseModelViewMatrix -> setMat4(inverseModelViewMatrix.toArray()) ;

    // Inverse view projection matrix.
    Mind::Matrix4x4f inverseViewProjectionMatrix ;
    viewProjectionMatrix.inverse(inverseViewProjectionMatrix) ;
    m_inverseViewProjectionMatrix -> setMat4(inverseViewProjectionMatrix.toArray()) ;

    // Inverse model view projection matrix.
    Mind::Matrix4x4f inverseModelViewProjectionMatrix ;
    modelViewProjectionMatrix.inverse(inverseModelViewProjectionMatrix) ;
    m_inverseMVPMatrix  -> setMat4(inverseModelViewProjectionMatrix.toArray()) ;

    // Normal matrix.
    Mind::Matrix4x4f normalMatrix ;
    inverseModelViewMatrix.transposed(normalMatrix) ;

    // Model normal matrix.
    Mind::Matrix4x4f modelNormalMatrix = normalMatrix * node.worldMatrix ;
    m_modelNormalMatrix -> setMat4(modelNormalMatrix.toArray()) ;

    // Model view normal matrix.
    Mind::Matrix4x4f modelViewNormalMatrix = normalMatrix * modelViewMatrix ;
    m_modelViewNormalMatrix -> setMat4(modelViewNormalMatrix.toArray()) ;

    // Viewport matrix.
    Viewport* viewport = data.viewport ;
    Mind::Matrix3x3f viewportMatrix ;

    Mind::Scalar viewportX = (viewport -> position()).get(Mind::Point2Df::X) ;
    Mind::Scalar viewportY = (viewport -> position()).get(Mind::Point2Df::Y) ;
    Mind::Scalar viewportWidth = (viewport -> dimension()).width() ;
    Mind::Scalar viewportHeight = (viewport -> dimension()).height() ;

    Mind::Point3Df row0(
        viewportWidth/ 2.f,
        0.f,
        viewportWidth / (2 + viewportX)
    ) ;

    Mind::Point3Df row1(
        0.f,
        viewportHeight/ 2.f,
        viewportHeight / (2 + viewportY)
    ) ;

    Mind::Point3Df row2(0.f, 0.f, 1.f) ;

    viewportMatrix.setRowValues(0, row0) ;
    viewportMatrix.setRowValues(1, row1) ;
    viewportMatrix.setRowValues(2, row2) ;

    m_viewportMatrix -> setMat3(viewportMatrix.toArray()) ;

    // Inverse viewport matrix.
    Mind::Matrix3x3f inverseViewportMatrix ;
    viewportMatrix.inverse(inverseViewportMatrix) ;
    m_inverseViewportMatrix -> setMat3(inverseViewportMatrix.toArray()) ;

    // Aspect ratio.
    m_aspectRatio -> setFloating(data.aspectRatio) ;

    // Elapsed time.
    m_time -> setFloating(data.time) ;

    // Eye position.
    m_eyePosition -> setVec3(data.eyePosition.toArray()) ;
}
