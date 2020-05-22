#include <scene/ogl/rendering/OpenGLRenderer.hpp>
#include <scene/ogl/rendering/glsl/ShaderUniformApplicator.hpp>
#include <scene/components/mesh/MeshGeometryComponent.hpp>
#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/components/materials/external/ExternalUniformSetter.hpp>
#include <scene/framegraph/cache/FrameRenderCache.hpp>
#include <scene/ogl/mesh/Geometry.hpp>

using namespace Hope::GL ;

#define BufferOffset(offset) (static_cast<const char*>(nullptr) + (offset))

void OpenGLRenderer::render(
    const Hope::RenderPassID renderPassID,
    std::vector<Hope::GeometryData>& dataList,
    const uint32_t memoryBarrier
) {
    if (m_defaultFramebuffer) {
        m_defaultFramebuffer -> bind() ;
    }

    for (Hope::GeometryData& meshData : dataList) {
        m_modelUBO.setMatrices(
            meshData.worldTransformation,
            m_viewMatrix,
            m_projectionMatrix
        ) ;
        m_modelUBO.update() ;

        const Geometry* geometry = (meshData.mesh -> geometry()) ;
        geometry -> bind() ;

        for (auto& [material, meshPartIndices] : meshData.parts) {
            const auto* renderPass = activateShader(renderPassID, material) ;

            if (!renderPass) {
                // Do not try to render as it is not possible!
                continue ;
            }

            material -> updateUniformValues();
            useMaterial(renderPass) ;

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
                static_cast<int>(amountParts)
            ) ;
            disableCapabilities(renderPass) ;

            // Insert a memory barrier.
            if (memoryBarrier != 0) {
                glMemoryBarrier(memoryBarrier) ;
            }
        }

        geometry -> unbind() ;
    }

    if (m_defaultFramebuffer) {
        m_defaultFramebuffer -> unbind() ;
    }
}

void OpenGLRenderer::deferredShading(
    Hope::MaterialComponent* material,
    const uint32_t memoryBarrier,
    std::vector<Hope::EffectData*>& effects
) {
    m_deferredShadingQuad.bind() ;

    const auto* renderPass = activateShader(ForwardPassID, material) ;

    if (!renderPass) {
        return ;
    }

    material -> updateUniformValues() ;

    // Apply effects.
    for (Hope::EffectData* effect : effects) {
        effect -> updateUniformValues() ;
    }

    useMaterial(
        renderPass,
        effects
    ) ;

    // Draw the quad.
    size_t amountIndices = m_deferredShadingQuad.part(0).amountIndices() ;
    glDrawElements(
        GL_TRIANGLE_STRIP,
        static_cast<int>(amountIndices),
        GL_UNSIGNED_BYTE,
        nullptr
    ) ;

    // Insert a memory barrier.
    if (memoryBarrier != 0) {
        glMemoryBarrier(memoryBarrier) ;
    }

    m_deferredShadingQuad.unbind() ;
}

const Hope::GL::RenderPass* OpenGLRenderer::activateShader(
    const Hope::RenderPassID renderPassID,
    const Hope::MaterialComponent* component
) {
    RenderPass* pass = component -> renderPass(renderPassID) ;

    if (!pass) {
        return nullptr ;
    }

    ShaderProgram* shaderProgram = pass -> shaderProgram() ;

    if (shaderProgram) {
        shaderProgram -> use() ;
    }

    return pass ;
}

void OpenGLRenderer::useMaterial(
    const Hope::GL::RenderPass* pass,
    const std::vector<Hope::EffectData*>& effects
) {
    if (!pass) {
        return ;
    }

    // Do material processing.
    ShaderProgram* shaderProgram = pass -> shaderProgram() ;

    if (shaderProgram) {
        // Apply shader uniforms.
        auto passUniforms = pass -> shaderUniforms() ;
        for (auto uniform : passUniforms) {
            ShaderUniformApplicator::ApplyUniform(
                shaderProgram -> id(),
                uniform
            ) ;
        }

        for (const Hope::EffectData* effect: effects) {
            if (effect -> hasAdditionalUniforms()) {
                auto additionalUniforms = effect -> uniforms() ;

                for (auto uniform : additionalUniforms) {
                    ShaderUniformApplicator::ApplyUniform(
                        shaderProgram -> id(),
                        uniform
                    ) ;
                }
            }
        }
    }
}

void OpenGLRenderer::updateLightUBO(const std::shared_ptr<Hope::FrameRenderCache> cache) {
    {
        const auto& directionalLights = cache -> directionalLights() ;
        const int amountDirLights = static_cast<int>(directionalLights.size());
        m_lightUBO.setAmountDirectionalLights(amountDirLights) ;

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
        const int amountLights = static_cast<int>(pointLightsData.size());
        m_lightUBO.setAmountPointLights(amountLights) ;

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
