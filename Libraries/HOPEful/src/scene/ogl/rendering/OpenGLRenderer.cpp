#include <scene/ogl/rendering/OpenGLRenderer.hpp>
#include <scene/ogl/rendering/glsl/ShaderUniformApplicator.hpp>
#include <scene/components/mesh/MeshGeometryComponent.hpp>
#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/ogl/visitors/cache/FrameRenderSharedData.hpp>
#include <scene/ogl/mesh/MeshGeometry.hpp>

using namespace Hope::GL ;

void OpenGLRenderer::render(std::vector<MeshData>& dataList) {
    for (MeshData& meshData : dataList) {
        (meshData.sharedData -> modelUBO).setMatrices(
            meshData.worldTransformation,
            meshData.sharedData -> viewMatrix,
            meshData.sharedData -> projectionMatrix
        ) ;
        (meshData.sharedData -> modelUBO).update() ;

        for (auto& [material, meshParts] : meshData.parts) {
            material -> updateUniformValues() ;
            useMaterial(material) ;

            const MeshGeometry* geometry = (meshData.mesh -> geometry()) ;
            geometry -> bind() ;
            for (MeshPart& part : meshParts) {
                part.render() ;
            }
            geometry -> unbind() ;
        }
    }

    m_renderCache.clear() ;
}

void OpenGLRenderer::useMaterial(const MaterialComponent* component) {
    const RenderEffect& effect = component -> effect() ;
    auto renderPasses = effect.renderPasses() ;

    for (const std::shared_ptr<API::RenderPass>& pass : renderPasses) {
        // Maybe should check render passes (or it will work in FrameGraph
        // visitor through the RenderConditionAggregator?).

        auto capabilities = pass -> capabilities() ;

        // Apply the capabilities.
        for (const std::shared_ptr<Hope::GL::Capability>& capability : capabilities) {
            capability -> apply() ;
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

        // Restore the OpenGL state machine for the next rendered object.
        for (const std::shared_ptr<Hope::GL::Capability>& capability : capabilities) {
            capability -> remove() ;
        }
    }
}
