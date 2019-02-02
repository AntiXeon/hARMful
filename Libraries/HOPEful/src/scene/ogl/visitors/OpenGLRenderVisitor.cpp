#include <scene/ogl/visitors/OpenGLRenderVisitor.hpp>
#include <scene/components/CameraComponent.hpp>
#include <scene/components/MeshComponent.hpp>
#include <scene/components/RenderConfiguration.hpp>
#include <scene/components/materials/Material.hpp>
#include <scene/ogl/rendering/glsl/ShaderParameterApplicator.hpp>

using namespace Hope ;
using namespace Hope::GL ;

void OpenGLRenderVisitor::startNewFrame() {
    m_currentFrameID++ ;
}

FrameID OpenGLRenderVisitor::currentFrameID() const {
    return m_currentFrameID ;
}

void OpenGLRenderVisitor::visit(CameraComponent* /*component*/) {
    // TODO
}

void OpenGLRenderVisitor::visit(MeshComponent* component) {
    std::shared_ptr<API::Mesh> mesh = component -> mesh() ;
    const std::vector<MeshPart>& meshParts = mesh -> parts() ;

    for (const MeshPart& part : meshParts) {
        glBindBuffer(GL_ARRAY_BUFFER, part.vertexBufferID()) ;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, part.indexBufferID()) ;
        glDrawElements(GL_TRIANGLES, part.amountIndices(), GL_UNSIGNED_INT, 0) ;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) ;
    }
}

void OpenGLRenderVisitor::visit(Hope::RenderConfiguration* /*component*/) {
    // TODO
}

void OpenGLRenderVisitor::visit(Material* component) {
    auto materialParameters = component -> shaderParameters() ;
    const RenderEffect* effect = component -> effect() ;

    auto effectParameters = effect -> shaderParameters() ;
    ShaderParameter::merge(materialParameters, effectParameters) ;

    auto effectTechniques = effect -> techniques() ;

    for (const std::shared_ptr<RenderTechnique>& technique : effectTechniques) {
        // TODO: Check API compatibility.
        auto appliedParameters = effectParameters ;
        auto techniqueParameters = technique -> shaderParameters() ;
        ShaderParameter::merge(appliedParameters, techniqueParameters) ;

        auto renderPasses = technique -> renderPasses() ;

        for (const std::shared_ptr<API::RenderPass>& pass : renderPasses) {
            auto passParameters = pass -> shaderParameters() ;
            ShaderParameter::merge(appliedParameters, passParameters) ;

            auto capabilities = pass -> capabilities() ;

            // Apply the capabilities.
            for (const std::shared_ptr<Hope::GL::Capability>& capability : capabilities) {
                capability -> apply() ;
            }

            // Do material processing.
            std::weak_ptr<ShaderProgram> shaderProgramWk = pass -> shaderProgram() ;
            std::shared_ptr<ShaderProgram> shaderProgram = shaderProgramWk.lock() ;

            if (shaderProgram) {
                shaderProgram -> link() ;

                // Set uniform values from the parameters here.
                for (const std::shared_ptr<Hope::ShaderParameter> param : appliedParameters) {
                    ShaderParameterApplicator::ApplyParameter(
                        shaderProgram -> id(),
                        param
                    ) ;
                }

                shaderProgram -> use() ;
                shaderProgram -> unuse() ;
            }

            // Restore the OpenGL state machine for the next rendered object.
            for (const std::shared_ptr<Hope::GL::Capability>& capability : capabilities) {
                capability -> remove() ;
            }
        }
    }
}
