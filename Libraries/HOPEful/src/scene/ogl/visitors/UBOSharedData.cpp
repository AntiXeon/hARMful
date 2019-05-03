#include <scene/ogl/visitors/UBOSharedData.hpp>
#include <scene/ogl/visitors/cache/FrameRenderCache.hpp>

using namespace Hope::GL ;

void UBOSharedData::updateLightUBO(const FrameRenderCache& cache) {
    {
        const auto& directionalLights = cache.directionalLights() ;
        m_lightUBO.setAmountDirectionalLights(directionalLights.size()) ;

        uint16_t lightIndex = 0 ;
        for (DirectionalLightComponent* dirLight : directionalLights) {
            m_lightUBO.setDirectionalLight(
                lightIndex,
                dirLight
            ) ;
            lightIndex++ ;
        }
    }

    {
        const auto& pointLightsData = cache.pointLights() ;
        m_lightUBO.setAmountPointLights(pointLightsData.size()) ;

        uint16_t lightIndex = 0 ;
        for (const PointLightData& lightData : pointLightsData) {
            m_lightUBO.setPointLight(
                lightIndex,
                lightData.light,
                lightData.worldPosition,
                lightData.sharedData -> viewMatrix
            ) ;
            lightIndex++ ;
        }
    }

    m_lightUBO.update() ;
}
