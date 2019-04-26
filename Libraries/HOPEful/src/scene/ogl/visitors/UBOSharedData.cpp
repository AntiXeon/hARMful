#include <scene/ogl/visitors/UBOSharedData.hpp>
#include <scene/components/materials/BlockBindings.hpp>

using namespace Hope::GL ;

UBOSharedData::UBOSharedData() {
    m_baseUBO = new BaseGLSLDataUBO(BASE_DATA_UBO_BINDING_INDEX) ;
    m_modelUBO = new ModelGLSLDataUBO(MODEL_DATA_UBO_BINDING_INDEX) ;
    m_lightUBO = new LightGLSLDataUBO(LIGHTS_DATA_UBO_BINDING_INDEX) ;
}

UBOSharedData::~UBOSharedData() {
    delete m_baseUBO ;
    delete m_modelUBO ;
    delete m_lightUBO ;
}

void UBOSharedData::updateLightUBO(const SceneCache* cache) {
    // Refresh light UBO if needed.
    bool changedDirLights = cache -> hasDirectionalLightsChanged() ;
    if (changedDirLights) {
        const auto& directionalLights = cache -> directionalLights() ;
        m_lightUBO -> setAmountDirectionalLights(directionalLights.size()) ;

        uint16_t lightIndex = 0 ;
        for (const DirectionalLightComponent* dirLight : directionalLights) {
            m_lightUBO -> setDirectionalLight(lightIndex, dirLight) ;
            lightIndex++ ;
        }
    }

    bool changedPointLights = cache -> hasPointLightsChanged() ;
    if (changedPointLights) {
        const auto& pointLights = cache -> pointLights() ;
        m_lightUBO -> setAmountPointLights(pointLights.size()) ;

        uint16_t lightIndex = 0 ;
        for (const PointLightComponent* pointLight : pointLights) {
            m_lightUBO -> setPointLight(lightIndex, pointLight) ;
            lightIndex++ ;
        }
    }

    if (changedDirLights || changedPointLights) {
        m_lightUBO -> update() ;
    }
}

void UBOSharedData::updateModelUBO(
    Mind::Matrix4x4f& modelMatrix,
    Mind::Matrix4x4f& viewMatrix,
    Mind::Matrix4x4f& projectionMatrix
) {
    // Update the UBO matrices.
    m_modelUBO -> setModelMatrix(modelMatrix) ;

    Mind::Matrix4x4f modelViewMatrix = viewMatrix * modelMatrix ;
    m_modelUBO -> setModelViewMatrix(modelViewMatrix) ;

    Mind::Matrix4x4f mvpMatrix = projectionMatrix * modelViewMatrix ;
    m_modelUBO -> setMVPMatrix(mvpMatrix) ;

    Mind::Matrix4x4f resultMatrix ;
    modelMatrix.inverse(resultMatrix) ;
    m_modelUBO -> setInverseModelMatrix(resultMatrix) ;

    modelViewMatrix.inverse(resultMatrix) ;
    m_modelUBO -> setInverseModelViewMatrix(resultMatrix) ;

    Mind::Matrix4x4f normalMatrix ;
    resultMatrix.transposed(normalMatrix) ; // Normal matrix = transposed of the inverse model view matrix.
    m_modelUBO -> setNormalMatrix(normalMatrix) ;

    mvpMatrix.inverse(resultMatrix) ;
    m_modelUBO -> setInverseMVPMatrix(resultMatrix) ;

    m_modelUBO -> setModelNormalMatrix(normalMatrix * modelMatrix) ;
    m_modelUBO -> setModelViewNormalMatrix(normalMatrix * modelViewMatrix) ;

    // Send these new values to the GPU.
    m_modelUBO -> update() ;
}
