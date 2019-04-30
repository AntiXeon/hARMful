#include <scene/ogl/visitors/cache/FrameRenderCache.hpp>
#include <scene/components/lights/DirectionalLightComponent.hpp>
#include <scene/components/lights/PointLightComponent.hpp>
#include <scene/components/materials/AmountLights.hpp>
#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/components/mesh/MeshGeometryComponent.hpp>
#include <scene/SceneTypes.hpp>
#include <scene/Entity.hpp>
#include <map>

using namespace Hope::GL ;

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
        cacheLight(light) ;
    }

    // Get the mesh info if available.
    if (entity -> amountComponents(MeshGeometryComponentType) > 0) {
        cacheMesh(entity, worldTransformation) ;
    }
}

void FrameRenderCache::cacheLight(LightComponent* light) {
    switch (light -> lightType()) {
        case LightComponent::Type::Directional:
            m_directionalLights.push_back(static_cast<DirectionalLightComponent*>(light)) ;
            break ;

        case LightComponent::Type::Point:
            m_pointLights.push_back(static_cast<PointLightComponent*>(light)) ;
            break ;

        default:
            break ;
    }
}

void FrameRenderCache::cacheMesh(
    const Entity* entity,
    const Mind::Matrix4x4f& worldTransformation
) {
    // Group mesh parts by material.
    MeshData entityMeshData ;
    entityMeshData.mesh = entity -> component<MeshGeometryComponent>() ;
    entityMeshData.worldTransformation = worldTransformation ;
    entityMeshData.sharedData = &m_sharedData ;

    const MeshGeometry* geometry = entityMeshData.mesh -> geometry() ;
    size_t amountParts = geometry -> amountParts() ;

    for (size_t partIndex = 0 ; partIndex < amountParts ; ++partIndex) {
        MeshPart& part = const_cast<MeshPart&>(geometry -> part(partIndex)) ;

        uint32_t materialID = part.materialID() ;
        MaterialComponent* material = entity -> component<MaterialComponent>(materialID) ;
        entityMeshData.parts[material].push_back(part) ;
    }

    m_meshes.push_back(entityMeshData) ;
}
