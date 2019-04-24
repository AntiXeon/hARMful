#include <scene/ogl/visitors/OpenGLRenderVisitor.hpp>
#include <scene/components/CameraComponent.hpp>
#include <scene/components/RenderConfiguration.hpp>
#include <scene/components/mesh/MeshGeometryComponent.hpp>
#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/components/test/TriangleTestComponent.hpp>
#include <scene/ogl/mesh/MeshGeometry.hpp>
#include <scene/ogl/rendering/glsl/ShaderAttributeApplicator.hpp>
#include <scene/ogl/rendering/glsl/ShaderUniformApplicator.hpp>
#include <scene/Entity.hpp>

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
    auto materialAttributes = component -> shaderAttributes() ;
    const RenderEffect& effect = component -> effect() ;

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
            shaderProgram -> use() ;

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
