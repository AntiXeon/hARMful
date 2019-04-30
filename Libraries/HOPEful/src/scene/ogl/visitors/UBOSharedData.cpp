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
        const auto& pointLights = cache.pointLights() ;
        m_lightUBO.setAmountPointLights(pointLights.size()) ;

        uint16_t lightIndex = 0 ;
        for (PointLightComponent* pointLight : pointLights) {
            m_lightUBO.setPointLight(
                lightIndex,
                pointLight
            ) ;
            lightIndex++ ;
        }
    }

    m_lightUBO.update() ;
}
