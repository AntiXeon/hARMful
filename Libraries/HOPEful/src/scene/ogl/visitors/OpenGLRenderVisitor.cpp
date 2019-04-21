#include <scene/ogl/visitors/OpenGLRenderVisitor.hpp>
#include <scene/components/CameraComponent.hpp>
#include <scene/components/RenderConfiguration.hpp>
#include <scene/components/mesh/MeshGeometryComponent.hpp>
#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/components/test/TriangleTestComponent.hpp>
#include <scene/ogl/mesh/MeshGeometry.hpp>
#include <scene/ogl/rendering/glsl/ShaderAttributeApplicator.hpp>
#include <scene/ogl/rendering/glsl/ShaderUniformApplicator.hpp>

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

void OpenGLRenderVisitor::visit(MeshGeometryComponent* component) {
    const API::MeshGeometry& geometry = component -> geometry() ;
    geometry.render() ;
}

void OpenGLRenderVisitor::visit(MaterialComponent* component) {
    auto materialAttributes = component -> shaderAttributes() ;
    RenderEffect& effect = component -> effect() ;

    auto effectAttributes = effect.shaderAttributes() ;
    ShaderAttribute::merge(materialAttributes, effectAttributes) ;

    // Select the technique that is used.
    std::shared_ptr<RenderTechnique> selectedTechnique ;
    selectedTechnique = selectBestMaterialTechnique(effect.techniques()) ;

    if (!selectedTechnique) {
        // Impossible to render the material with the defined techniques...
        return ;
    }

    auto appliedAttributes = effectAttributes ;
    auto techniqueAttributes = selectedTechnique -> shaderAttributes() ;
    ShaderAttribute::merge(appliedAttributes, techniqueAttributes) ;
    auto renderPasses = selectedTechnique -> renderPasses() ;

    for (const std::shared_ptr<API::RenderPass>& pass : renderPasses) {
        // Maybe should check render passes (or it will work in FrameGraph
        // visitor through the RenderConditionAggregator?).

        auto passAttrributes = pass -> shaderAttributes() ;
        ShaderAttribute::merge(appliedAttributes, passAttrributes) ;

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

            // Apply shader uniforms.
            auto materialUniforms = component -> shaderUniforms() ;
            for (auto& [name, uniform] : materialUniforms) {
                ShaderUniformApplicator::ApplyUniform(
                    shaderProgram -> id(),
                    uniform
                ) ;
            }

            // Set attribute values here.
            for (auto& [name, attrib] : appliedAttributes) {
                ShaderAttributeApplicator::ApplyAttribute(
                    shaderProgram -> id(),
                    attrib
                ) ;
            }

            shaderProgram -> use() ;
        }

        // Restore the OpenGL state machine for the next rendered object.
        for (const std::shared_ptr<Hope::GL::Capability>& capability : capabilities) {
            capability -> remove() ;
        }
    }
}

void OpenGLRenderVisitor::visit(TriangleTestComponent* component) {
    component -> render() ;
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
