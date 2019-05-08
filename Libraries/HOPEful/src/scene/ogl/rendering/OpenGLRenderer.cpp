#include <scene/ogl/rendering/OpenGLRenderer.hpp>
#include <scene/ogl/rendering/glsl/ShaderUniformApplicator.hpp>
#include <scene/components/mesh/MeshGeometryComponent.hpp>
#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/ogl/visitors/cache/FrameRenderSharedData.hpp>
#include <scene/ogl/mesh/Geometry.hpp>

using namespace Hope::GL ;

#define BufferOffset(offset) (static_cast<const char*>(nullptr) + (offset))

void OpenGLRenderer::render(std::vector<GeometryData>& dataList) {
    for (GeometryData& meshData : dataList) {
        (meshData.sharedData -> modelUBO).setMatrices(
            meshData.worldTransformation,
            meshData.sharedData -> viewMatrix,
            meshData.sharedData -> projectionMatrix
        ) ;
        (meshData.sharedData -> modelUBO).update() ;

        const Geometry* geometry = (meshData.mesh -> geometry()) ;
        geometry -> bind() ;

        for (auto& [material, meshPartIndices] : meshData.parts) {
            material -> updateUniformValues() ;
            auto renderPass = useMaterial(material) ;

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

std::shared_ptr<API::RenderPass> OpenGLRenderer::useMaterial(const MaterialComponent* component) {
    const RenderEffect& effect = component -> effect() ;
    auto renderPasses = effect.renderPasses() ;

    for (const std::shared_ptr<API::RenderPass>& pass : renderPasses) {
        // Maybe should check render passes (or it will work in FrameGraph
        // visitor through the RenderConditionAggregator?).

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

    return nullptr ;
}
