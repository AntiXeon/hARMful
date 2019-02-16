#include <scene/ogl/visitors/OpenGLRenderVisitor.hpp>
#include <scene/components/CameraComponent.hpp>
#include <scene/components/MeshComponent.hpp>
#include <scene/components/RenderConfiguration.hpp>
#include <scene/components/materials/Material.hpp>
#include <scene/ogl/rendering/glsl/ShaderParameterApplicator.hpp>

#include <iostream>

using namespace Hope ;
using namespace Hope::GL ;

void OpenGLRenderVisitor::startNewFrame() {
    m_currentFrameID++ ;
}

FrameID OpenGLRenderVisitor::currentFrameID() const {
    return m_currentFrameID ;
}

RenderRequiredData& OpenGLRenderVisitor::requiredData() {
    return m_requiredData ;
}

void OpenGLRenderVisitor::setProcessedNode(const Hope::ProcessedSceneNode& node) {
    m_processedNode = node ;
}

Hope::ProcessedSceneNode& OpenGLRenderVisitor::processedNode() {
    return m_processedNode ;
}

void OpenGLRenderVisitor::visit(CameraComponent* /*component*/) {
    // TODO
}

void OpenGLRenderVisitor::visit(MeshComponent* component) {
    std::shared_ptr<API::Mesh> mesh = component -> mesh() ;
    const std::vector<MeshPart>& meshParts = mesh -> parts() ;

    for (const MeshPart& part : meshParts) {
        part.bind() ;
        glBindBuffer(GL_ARRAY_BUFFER, part.vertexBufferID()) ;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, part.indexBufferID()) ;
        glDrawArrays(GL_TRIANGLES, 0, part.amountIndices()) ;
    }
}

void OpenGLRenderVisitor::visit(Hope::RenderConfiguration* /*component*/) {
    // TODO
}

void OpenGLRenderVisitor::visit(Material* component) {
    auto materialParameters = component -> shaderParameters() ;
    RenderEffect& effect = component -> effect() ;

    auto effectParameters = effect.shaderParameters() ;
    ShaderParameter::merge(materialParameters, effectParameters) ;

    // Select the technique that is used.
    std::shared_ptr<RenderTechnique> selectedTechnique ;
    selectedTechnique = selectBestMaterialTechnique(effect.techniques()) ;

    if (!selectedTechnique) {
        // Impossible to render the material with the defined techniques...
        return ;
    }

    auto appliedParameters = effectParameters ;
    auto techniqueParameters = selectedTechnique -> shaderParameters() ;
    ShaderParameter::merge(appliedParameters, techniqueParameters) ;
    auto renderPasses = selectedTechnique -> renderPasses() ;

    for (const std::shared_ptr<API::RenderPass>& pass : renderPasses) {
        // Maybe should check render passes (or it will work in FrameGraph
        // visitor through the RenderConditionAggregator?).

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
            shaderProgram -> use() ;

            // Set uniform values from the parameters here.
            for (const std::shared_ptr<Hope::ShaderParameter> param : appliedParameters) {
                ShaderParameterApplicator::ApplyParameter(
                    shaderProgram -> id(),
                    param
                ) ;
            }
        }

        // Restore the OpenGL state machine for the next rendered object.
        for (const std::shared_ptr<Hope::GL::Capability>& capability : capabilities) {
            capability -> remove() ;
        }
    }
}

std::shared_ptr<RenderTechnique> OpenGLRenderVisitor::selectBestMaterialTechnique(
    const std::set<std::shared_ptr<RenderTechnique>>& techniques
) {
    GLint glSupportedMajorVersion = 0 ;
    GLint glSupportedMinorVersion = 0 ;
    glGetIntegerv(GL_MAJOR_VERSION, &glSupportedMajorVersion) ;
    glGetIntegerv(GL_MINOR_VERSION, &glSupportedMinorVersion) ;

    std::shared_ptr<RenderTechnique> selectedTechnique ;
    for (const std::shared_ptr<RenderTechnique>& technique : techniques) {
        // Check API compatibility.
        if (technique -> api() != RenderTechnique::GraphicsAPI::OpenGL) {
            // Discard API other than OpenGL (as we are in an OpenGL
            // implementation!).
            continue ;
        }

        if ((technique -> apiMajorVersion() <= glSupportedMajorVersion)
                && (technique -> apiMinorVersion() <= glSupportedMinorVersion)) {
            if (!selectedTechnique) {
                // Set as used technique since it is compatible.
                selectedTechnique = technique ;
            }
            else if ((selectedTechnique -> apiMajorVersion() <= technique -> apiMajorVersion())
                        && (selectedTechnique -> apiMinorVersion() <= technique -> apiMinorVersion())) {
                // Set as used technique since it is compatible and it offers
                // the most advanced graphical features.
                selectedTechnique = technique ;
            }
        }
    }

    return selectedTechnique ;
}
