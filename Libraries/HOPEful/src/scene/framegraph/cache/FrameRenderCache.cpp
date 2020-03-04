#include <scene/framegraph/cache/FrameRenderCache.hpp>
#include <scene/components/lights/DirectionalLightComponent.hpp>
#include <scene/components/lights/PointLightComponent.hpp>
#include <scene/components/materials/shaders/GLSL/includes/AmountLights.hpp>
#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/components/mesh/MeshGeometryComponent.hpp>
#include <scene/SceneTypes.hpp>
#include <scene/Entity.hpp>
#include <map>

using namespace Hope ;

FrameRenderCache::FrameRenderCache() {
    const size_t EstimatedAmountMeshes = 256 ;
    m_meshes.reserve(EstimatedAmountMeshes) ;
    m_directionalLights.reserve(MAX_DIRECTIONAL_LIGHTS) ;
    m_pointLights.reserve(MAX_POINT_LIGHTS) ;
}

void FrameRenderCache::cacheEntity(
    const Entity* entity,
    const Mind::Matrix4x4f& worldTransformation
) {
    // Get the light if available.
    if (entity -> amountComponents(LightComponentType) > 0) {
        LightComponent* light = entity -> component<LightComponent>() ;
        cacheLight(light, worldTransformation) ;
    }

    // Get the mesh info if available.
    if (entity -> amountComponents(GeometryComponentType) > 0) {
        cacheGeometry(entity, worldTransformation) ;
    }
}

void FrameRenderCache::cacheLight(
    LightComponent* light,
    const Mind::Matrix4x4f& worldTransformation
) {
    switch (light -> lightType()) {
        case LightComponent::Type::Directional:
            m_directionalLights.push_back(static_cast<DirectionalLightComponent*>(light)) ;
            break ;

        case LightComponent::Type::Point:
            {
                PointLightData data = {
                    static_cast<PointLightComponent*>(light),
                    worldTransformation.extractTranslation()
                } ;
                m_pointLights.push_back(data) ;
                break ;
            }

        default:
            break ;
    }
}

void FrameRenderCache::cacheGeometry(
    const Entity* entity,
    const Mind::Matrix4x4f& worldTransformation
) {
    // Group mesh parts by material.
    GeometryData entityGeometryData ;
    entityGeometryData.mesh = entity -> component<GeometryComponent>() ;
    entityGeometryData.worldTransformation = worldTransformation ;

    const API::Geometry* geometry = entityGeometryData.mesh -> geometry() ;
    uint32_t amountParts = static_cast<int32_t>(geometry -> amountParts()) ;

    for (uint32_t partIndex = 0 ; partIndex < amountParts ; ++partIndex) {
        API::GeometryPart& part = const_cast<API::GeometryPart&>(geometry -> part(partIndex)) ;

        uint32_t materialID = part.materialID() ;
        MaterialComponent* material = entity -> component<MaterialComponent>(materialID) ;

        if (!material) {
            material = &m_defaultMaterial ;
        }

        entityGeometryData.parts[material].push_back(partIndex) ;
    }

    m_meshes.push_back(entityGeometryData) ;
}
