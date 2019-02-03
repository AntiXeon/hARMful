#include <scene/components/materials/Material.hpp>
#include <interfaces/visitors/scenegraph/ISceneGraphVisitor.hpp>

using namespace Hope ;

const std::string ModelMatrixParamName = u8"modelMatrix" ;
const std::string ViewMatrixParamName = u8"viewMatrix" ;
const std::string ProjectionMatrixParamName = u8"projectionMatrix" ;
const std::string ModelViewMatrixParamName = u8"modelViewMatrix" ;
const std::string ViewProjectionMatrixParamName = u8"viewProjectionMatrix" ;
const std::string MVPMatrixParamName = u8"mvpMatrix" ;
const std::string InverseModelMatrixParamName = u8"inverseModelMatrix" ;
const std::string InverseViewMatrixParamName = u8"inverseViewMatrix" ;
const std::string InverseProjectionMatrixParamName = u8"inverseProjectionMatrix" ;
const std::string InverseModelViewMatrixParamName = u8"inverseModelViewMatrix" ;
const std::string InverseViewProjectionMatrixParamName = u8"inverseViewProjectionMatrix" ;
const std::string InverseMVPMatrixParamName = u8"inverseMVPMatrix" ;
const std::string ModelNormalMatrixParamName = u8"modelNormalMatrix" ;
const std::string ModelViewNormalMatrixParamName = u8"modelViewNormalMatrix" ;
const std::string ViewportMatrixParamName = u8"viewportMatrix" ;
const std::string InverseViewportMatrixParamName = u8"inverseViewportMatrix" ;
const std::string AspectRatioParamName = u8"aspectRatio" ;
const std::string TimeParamName = u8"time" ;
const std::string EyePositionParamName = u8"eyePosition" ;

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

void Material::updateParameterValues(ISceneGraphVisitor* /*visitor*/) {
    // m_modelMatrix
    // m_viewMatrix
    // m_projectionMatrix
    // m_modelViewMatrix
    // m_viewProjectionMatrix
    // m_mvpMatrix
    // m_inverseModelMatrix
    // m_inverseViewMatrix
    // m_inverseProjectionMatrix
    // m_inverseModelViewMatrix
    // m_inverseViewProjectionMatrix
    // m_inverseMVPMatrix
    // m_modelNormalMatrix
    // m_modelViewNormalMatrix
    // m_viewportMatrix
    // m_inverseViewportMatrix
    // m_aspectRatio
    // m_time
    // m_eyePosition
}
