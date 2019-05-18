#include <scene/ogl/rendering/OpenGLRenderer.hpp>
#include <scene/ogl/rendering/glsl/ShaderUniformApplicator.hpp>
#include <scene/components/mesh/MeshGeometryComponent.hpp>
#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/framegraph/cache/FrameRenderCache.hpp>
#include <scene/ogl/mesh/Geometry.hpp>

using namespace Hope::GL ;

#define BufferOffset(offset) (static_cast<const char*>(nullptr) + (offset))

void OpenGLRenderer::render(
    const RenderPassID renderPassID,
    std::vector<GeometryData>& dataList
) {
    for (GeometryData& meshData : dataList) {
        m_modelUBO.setMatrices(
            meshData.worldTransformation,
            m_viewMatrix,
            m_projectionMatrix
        ) ;
        m_modelUBO.update() ;

        const Geometry* geometry = (meshData.mesh -> geometry()) ;
        geometry -> bind() ;

        for (auto& [material, meshPartIndices] : meshData.parts) {
            material -> updateUniformValues(renderPassID) ;
            std::shared_ptr<API::RenderPass> renderPass = useMaterial(renderPassID, material) ;

            if (!renderPass) {
                // Do not try to render as it is not possible!
                continue ;
            }

            size_t amountParts = geometry -> amountParts() ;
            std::vector<int32_t> counts(amountParts) ;
            std::vector<const void*> indiceOffsets(amountParts) ;

            size_t counter = 0 ;
            for (uint32_t partIndex : meshPartIndices) {
                const GeometryPart& part = geometry -> part(partIndex) ;
                counts[counter] = static_cast<int32_t>(part.amountIndices()) ;
                indiceOffsets[counter] = BufferOffset(sizeof(uint32_t) * part.offset()) ;
                counter++ ;
            }

            enableCapabilities(renderPass) ;
            glMultiDrawElements(
                GL_TRIANGLES,
                counts.data(),
                geometry -> indiceType(),
                indiceOffsets.data(),
                amountParts
            ) ;
            disableCapabilities(renderPass) ;
        }

        geometry -> unbind() ;
    }
}

std::shared_ptr<API::RenderPass> OpenGLRenderer::useMaterial(
    const RenderPassID renderPassID,
    const MaterialComponent* component
) {
    std::shared_ptr<API::RenderPass> pass = component -> renderPass(renderPassID) ;

    if (!pass) {
        return nullptr ;
    }

    // Do material processing.
    std::weak_ptr<ShaderProgram> shaderProgramWk = pass -> shaderProgram() ;
    std::shared_ptr<ShaderProgram> shaderProgram = shaderProgramWk.lock() ;

    if (shaderProgram) {
        shaderProgram -> use() ;

        // Apply shader uniforms.
        auto materialUniforms = component -> shaderUniforms() ;
        for (auto& [name, uniform] : materialUniforms) {
            ShaderUniformApplicator::ApplyUniform(
                shaderProgram -> id(),
                uniform
            ) ;
        }
    }

    return pass ;
}

void OpenGLRenderer::updateLightUBO(const std::shared_ptr<Hope::FrameRenderCache> cache) {
    {
        const auto& directionalLights = cache -> directionalLights() ;
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
        const auto& pointLightsData = cache -> pointLights() ;
        m_lightUBO.setAmountPointLights(pointLightsData.size()) ;

        uint16_t lightIndex = 0 ;
        for (const PointLightData& lightData : pointLightsData) {
            m_lightUBO.setPointLight(
                lightIndex,
                lightData.light,
                lightData.worldPosition,
                m_viewMatrix
            ) ;
            lightIndex++ ;
        }
    }

    m_lightUBO.update() ;
}
