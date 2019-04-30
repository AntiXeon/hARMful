#include <scene/ogl/visitors/UBOSharedData.hpp>
#include <scene/ogl/visitors/cache/FrameRenderCache.hpp>

using namespace Hope::GL ;

void UBOSharedData::updateLightUBO(const FrameRenderCache& cache) {
    {
        const auto& directionalLights = cache.directionalLights() ;
        m_lightUBO.setAmountDirectionalLights(directionalLights.size()) ;

        uint16_t lightIndex = 0 ;
        for (const DirectionalLightData& dirLight : directionalLights) {
            m_lightUBO.setDirectionalLight(
                lightIndex,
                dirLight.light,
                dirLight.worldTransformation
            ) ;
            lightIndex++ ;
        }
    }

    {
        const auto& pointLights = cache.pointLights() ;
        m_lightUBO.setAmountPointLights(pointLights.size()) ;

        uint16_t lightIndex = 0 ;
        for (const PointLightData& pointLight : pointLights) {
            m_lightUBO.setPointLight(
                lightIndex,
                pointLight.light,
                pointLight.worldTransformation
            ) ;
            lightIndex++ ;
        }
    }

    m_lightUBO.update() ;
}
