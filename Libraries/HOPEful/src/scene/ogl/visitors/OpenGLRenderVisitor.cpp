#include <scene/ogl/visitors/OpenGLRenderVisitor.hpp>
#include <scene/ogl/visitors/UBOSharedData.hpp>
#include <scene/components/CameraComponent.hpp>
#include <scene/components/RenderConfiguration.hpp>
#include <scene/components/mesh/MeshGeometryComponent.hpp>
#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/components/test/TriangleTestComponent.hpp>
#include <scene/ogl/rendering/glsl/ShaderUniformApplicator.hpp>
#include <scene/ogl/mesh/MeshGeometry.hpp>
#include <scene/Entity.hpp>

using namespace Hope ;
using namespace Hope::GL ;

void OpenGLRenderVisitor::startNewFrame() {
    m_currentFrameID++ ;
}

void OpenGLRenderVisitor::setProcessedNode(const Hope::ProcessedSceneNode& node) {
    m_processedNode = node ;
}

void OpenGLRenderVisitor::visit(MeshGeometryComponent* component) {
     const API::MeshGeometry* geometry = component -> geometry() ;
     size_t amountParts = geometry -> amountParts() ;

     geometry -> bind() ;

     for (size_t partIndex = 0 ; partIndex < amountParts ; ++partIndex) {
        const MeshPart& part = geometry -> part(partIndex) ;

        // Retrieve the material to use to render the part.
        Entity* entity = m_processedNode.node ;
        uint32_t materialID = part.materialID() ;

        size_t amountMaterials = entity -> amountComponents(MaterialComponentType) ;
        if (materialID < amountMaterials) {
            Component* wantedComponent = entity -> component(MaterialComponentType, materialID) ;
            MaterialComponent* material = static_cast<MaterialComponent*>(wantedComponent) ;
            useMaterial(material) ;
        }
        else {
            const MaterialComponent* defaultMaterial = (m_requiredData.cache) -> defaultMaterial() ;
            useMaterial(defaultMaterial) ;
        }

        // Render the part.
        part.render() ;
     }

     geometry -> unbind() ;
}

void OpenGLRenderVisitor::visit(TriangleTestComponent* component) {
    component -> render() ;
}

void OpenGLRenderVisitor::useMaterial(const MaterialComponent* component) {
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
            //m_lightUBO -> getInfo(shaderProgram -> id()) ;

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
