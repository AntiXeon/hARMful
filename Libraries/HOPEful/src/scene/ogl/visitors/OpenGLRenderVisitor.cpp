#include <scene/ogl/visitors/OpenGLRenderVisitor.hpp>
#include <scene/components/CameraComponent.hpp>
#include <scene/components/RenderConfiguration.hpp>
#include <scene/components/mesh/MeshGeometryComponent.hpp>
#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/components/test/TriangleTestComponent.hpp>
#include <scene/ogl/mesh/MeshGeometry.hpp>
#include <scene/ogl/rendering/glsl/ShaderAttributeApplicator.hpp>
#include <scene/ogl/rendering/glsl/ShaderUniformApplicator.hpp>
#include <scene/ogl/rendering/glsl/ubo/BaseGLSLDataUBO.hpp>
#include <scene/ogl/rendering/glsl/ubo/ModelGLSLDataUBO.hpp>
#include <scene/Entity.hpp>

using namespace Hope ;
using namespace Hope::GL ;

void OpenGLRenderVisitor::startNewFrame() {
    m_currentFrameID++ ;
}

void OpenGLRenderVisitor::setProcessedNode(const Hope::ProcessedSceneNode& node) {
    m_processedNode = node ;
}

void OpenGLRenderVisitor::setUBOs(
    BaseGLSLDataUBO* baseUBO,
    ModelGLSLDataUBO* modelUBO
) {
    m_baseUBO = baseUBO ;
    m_modelUBO = modelUBO ;

    // Update the UBO matrices.
    m_modelUBO -> setModelMatrix(m_processedNode.worldMatrix) ;

    Mind::Matrix4x4f modelViewMatrix = m_processedNode.worldMatrix * m_requiredData.viewMatrix ;
    m_modelUBO -> setModelViewMatrix(modelViewMatrix) ;

    Mind::Matrix4x4f mvpMatrix = modelViewMatrix * m_requiredData.projectionMatrix ;
    m_modelUBO -> setMVPMatrix(mvpMatrix) ;

    Mind::Matrix4x4f resultMatrix ;
    m_processedNode.worldMatrix.inverse(resultMatrix) ;
    m_modelUBO -> setInverseModelMatrix(resultMatrix) ;

    modelViewMatrix.inverse(resultMatrix) ;
    m_modelUBO -> setInverseModelViewMatrix(resultMatrix) ;

    Mind::Matrix4x4f normalMatrix ;
    resultMatrix.transposed(normalMatrix) ; // Normal matrix = transposed of the inverse model view matrix.
    m_modelUBO -> setNormalMatrix(normalMatrix) ;

    mvpMatrix.inverse(resultMatrix) ;
    m_modelUBO -> setInverseMVPMatrix(resultMatrix) ;

    m_modelUBO -> setModelNormalMatrix(m_processedNode.worldMatrix * normalMatrix) ;
    m_modelUBO -> setModelViewNormalMatrix(modelViewMatrix * normalMatrix) ;

    // Send these new values to the GPU.
    m_modelUBO -> update() ;
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

    // Select the technique that is used.
    std::shared_ptr<RenderTechnique> selectedTechnique ;
    selectedTechnique = selectBestMaterialTechnique(effect.techniques()) ;

    if (!selectedTechnique) {
        // Impossible to render the material with the defined techniques...
        return ;
    }

    auto techniqueAttributes = selectedTechnique -> shaderAttributes() ;
    auto renderPasses = selectedTechnique -> renderPasses() ;

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

            // Bind the UBOs.
            m_baseUBO -> bindToProgram(shaderProgram -> id()) ;
            m_modelUBO -> bindToProgram(shaderProgram -> id()) ;

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
