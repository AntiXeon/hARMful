#include <scene/ogl/visitors/OpenGLFrameGraphVisitor.hpp>
#include <scene/framegraph/ActiveCamera.hpp>
#include <scene/framegraph/FrustumCulling.hpp>
#include <scene/framegraph/Viewport.hpp>
#include <scene/ogl/Utils.hpp>
#include <GL/glew.h>

using namespace Hope ;
using namespace Hope::GL ;

OpenGLFrameGraphVisitor::OpenGLFrameGraphVisitor()
    : IFrameGraphVisitor() {
    RenderConditionAggregator defaultAggregator ;
    m_aggregators.push_back(defaultAggregator) ;
}

void OpenGLFrameGraphVisitor::visit(ActiveCamera* node) {
    Hope::CameraComponent* camera = node -> camera() ;

    // Set up the clear color.
    Color clearColor = camera -> clearColor() ;
    glClearColor(
        clearColor.red(),
        clearColor.green(),
        clearColor.blue(),
        clearColor.alpha()
    ) ;

    // Update the projection matrix if needed.
    if (m_hasWindowChanged) {
        // Set up the projection matrix.
        const float CameraFOV = 45.f ;
        const float NearPlaneDistance = 1.f ;
        const float FarPlaneDistance = 1000.f ;
        float aspectRatio = m_windowSize.width() / m_windowSize.height() ;

        glMatrixMode(GL_PROJECTION) ;
        glLoadIdentity() ;
        GLPerspective(CameraFOV, aspectRatio, NearPlaneDistance, FarPlaneDistance) ;
    }

    // Update the model view matrix.
    glMatrixMode(GL_MODELVIEW) ;
    Mind::Matrix4x4f viewMatrix = camera -> viewMatrix() ;
    float viewMatrixData[Mind::Matrix4x4f::MatrixSize] ;
    viewMatrix.data(viewMatrixData) ;
    glMultMatrixf(viewMatrixData) ;

    Hope::Entity* cameraEntity = camera -> firstEntity() ;
    Hope::Transform& cameraTransform = cameraEntity -> transform() ;
    // Inverse as the world moves instead of the camera!
    Mind::Vector3f eyeView = -cameraTransform.translation() ;
    glTranslatef(
        eyeView.get(Mind::Vector3f::X),
        eyeView.get(Mind::Vector3f::Y),
        eyeView.get(Mind::Vector3f::Z)
    ) ;
}

void OpenGLFrameGraphVisitor::visit(FrustumCulling* /*node*/) {
    // TODO
}

void OpenGLFrameGraphVisitor::visit(Viewport* node) {
    if (!m_hasWindowChanged) {
        return ;
    }

    // Update the projection matrix.
    glMatrixMode(GL_PROJECTION) ;

    Mind::Point2Df relativePosition = node -> position() ;
    Mind::Dimension2Df relativeDimension = node -> dimension() ;

    Mind::Point2Df absolutePosition(
        relativePosition.get(Mind::Point2Df::X) * m_windowSize.width(),
        relativePosition.get(Mind::Point2Df::Y) * m_windowSize.height()
    ) ;

    Mind::Dimension2Df absoluteDimension(
        relativeDimension.width() * m_windowSize.width(),
        relativeDimension.height() * m_windowSize.height()
    ) ;

    // Apply the viewport parameters.
    glViewport(
        absolutePosition.get(Mind::Point2Df::X),
        absolutePosition.get(Mind::Point2Df::Y),
        absoluteDimension.width(),
        absoluteDimension.height()
    ) ;

    // Switch back to the modelview matrix.
    glMatrixMode(GL_MODELVIEW) ;
}

void OpenGLFrameGraphVisitor::makeRender() {
    assert(m_aggregators.size() > 0) ;

    Hope::ProcessedSceneNode rootNode ;
    rootNode.node = m_root ;
    rootNode.worldMatrix = (m_root -> transform()).matrix() ;
    m_processedNodes.push(rootNode) ;

    while (m_processedNodes.size() > 0) {
        // For each entity: check if all the conditions are OK otherwise, go back to
        // the parent entity and process the other ones.
        // The children of an invalid entity are discarded as well.
        renderGraph() ;
    }

    // Remove the last RenderConditionAggregator from the list!
    m_aggregators.pop_back() ;
}

void OpenGLFrameGraphVisitor::backupRenderConditions() {
    // Copy and push back that copy in the list. So that, the copy can be
    // modified while the original still the same and can be reused for the
    // other branch of the frame graph.
    RenderConditionAggregator copy = m_aggregators.back() ;
    m_aggregators.push_back(copy) ;
}

void OpenGLFrameGraphVisitor::renderGraph() {
    Hope::Entity* renderedEntity = m_processedNodes.top().node ;

    if (renderedEntity && m_aggregators.back().check(renderedEntity)) {
        // Process the components of the top node.
        m_renderVisitor.setProcessedNode(m_processedNodes.top()) ;
        std::vector<Component*> components = renderedEntity -> components() ;
        for (Component* component : components) {
            component -> accept(&m_renderVisitor) ;
        }

        // Save the parent world matrix before pop.
        Mind::Matrix4x4f parentMatrix = m_processedNodes.top().worldMatrix ;
        // As the top node is processed, pop it from the stack.
        m_processedNodes.pop() ;

        // Avoid further processing if not necessary...
        if (renderedEntity -> childrenCount() == 0) {
            return ;
        }

        // If the node has children, push them in the stack.
        const std::vector<Node*>& nodeChildren = renderedEntity -> children() ;
        for (const Hope::Node* child : nodeChildren) {
            const Hope::Entity* childEntityConst = static_cast<const Entity*>(child) ;
            Hope::Entity* childEntity = const_cast<Entity*>(childEntityConst) ;
            Mind::Matrix4x4f childMatrix = (childEntity -> transform()).matrix() ;

            Hope::ProcessedSceneNode childNode ;
            childNode.node = childEntity ;
            childNode.worldMatrix = parentMatrix * childMatrix ;
            m_processedNodes.push(childNode) ;
        }
    }
}
