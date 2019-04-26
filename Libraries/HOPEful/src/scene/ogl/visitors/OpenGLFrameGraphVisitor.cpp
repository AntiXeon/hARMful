#include <scene/ogl/visitors/OpenGLFrameGraphVisitor.hpp>
#include <scene/ogl/visitors/UBOSharedData.hpp>
#include <scene/framegraph/ActiveCamera.hpp>
#include <scene/framegraph/FrustumCulling.hpp>
#include <scene/framegraph/Viewport.hpp>
#include <scene/components/RenderConfiguration.hpp>
#include <scene/ogl/Utils.hpp>
#include <Math.hpp>
#include <GLFW/glfw3.h>
#include <GL/glew.h>

using namespace Hope ;
using namespace Hope::GL ;

OpenGLFrameGraphVisitor::OpenGLFrameGraphVisitor()
    : IFrameGraphVisitor() {
    m_sceneCache = new SceneCache() ;
    m_ubos = new UBOSharedData() ;

    RenderConditionAggregator defaultAggregator ;
    m_aggregators.push_back(defaultAggregator) ;
}

OpenGLFrameGraphVisitor::~OpenGLFrameGraphVisitor() {
    delete m_sceneCache ;
    delete m_ubos ;
}

void OpenGLFrameGraphVisitor::createNewBranch(Hope::FrameGraphNode* fgNode) {
    if (m_renderVisitors.count(fgNode) > 0) {
        // Discard if the framegraph node is already registered.
        // Just set the active render visitor.
        m_activeOpenGLRenderVisitor = &m_renderVisitors[fgNode] ;
        return ;
    }

    // Otherwise, create the render visitor of the new branch.
    if (m_activeOpenGLRenderVisitor) {
        m_renderVisitors[fgNode] = *m_activeOpenGLRenderVisitor ;
    }
    else {
        m_renderVisitors[fgNode] = OpenGLRenderVisitor() ;
    }

    m_activeOpenGLRenderVisitor = &m_renderVisitors[fgNode] ;
    (m_activeOpenGLRenderVisitor -> requiredData()).cache = m_sceneCache ;
}

void OpenGLFrameGraphVisitor::setSceneRoot(Hope::Entity* root) {
    m_sceneRoot = root ;

    m_renderVisitors.clear() ;
    RenderConfiguration* config = dynamic_cast<RenderConfiguration*>(m_sceneRoot -> component(Hope::RenderConfigurationType)) ;
    createNewBranch(config -> root()) ;
}

void OpenGLFrameGraphVisitor::visit(ActiveCamera* node) {
    RenderRequiredData& requiredData = m_activeOpenGLRenderVisitor -> requiredData() ;

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
    float aspectRatio = 0.f ;
    if (m_hasWindowChanged) {
        // Set up the projection matrix.
        const float CameraFOV = 45.f ;
        const float NearPlaneDistance = 0.1f ;
        const float FarPlaneDistance = 1000.f ;
        aspectRatio = m_windowSize.width() / m_windowSize.height() ;

        GLPerspective(
            requiredData.projectionMatrix,
            Mind::Math::toRadians(CameraFOV),
            aspectRatio,
            NearPlaneDistance,
            FarPlaneDistance
        ) ;

        Mind::Matrix4x4f inverseProjectionMatrix ;
        requiredData.projectionMatrix.inverse(inverseProjectionMatrix) ;

        m_ubos -> base() -> setProjectionMatrix(requiredData.projectionMatrix) ;
        m_ubos -> base() -> setInverseProjectionMatrix(inverseProjectionMatrix) ;
        m_ubos -> base() -> setAspectRatio(aspectRatio) ;
    }

    // Update the model view matrix.
    requiredData.viewMatrix = camera -> viewMatrix() ;
    float viewMatrixData[Mind::Matrix4x4f::MatrixSize] ;
    requiredData.viewMatrix.data(viewMatrixData) ;

    Hope::Entity* cameraEntity = camera -> firstEntity() ;
    Hope::Transform& cameraTransform = cameraEntity -> transform() ;
    // Inverse as the world moves instead of the camera!
    Mind::Vector3f eyeView = -cameraTransform.translation() ;

    // Update the required data.
    m_ubos -> base() -> setTime(glfwGetTime()) ;
    m_ubos -> base() -> setEyePosition(eyeView) ;
    m_ubos -> base() -> setViewMatrix(requiredData.viewMatrix) ;

    Mind::Matrix4x4f resultInverse ;
    requiredData.viewMatrix.inverse(resultInverse) ;
    m_ubos -> base() -> setInverseViewMatrix(resultInverse) ;

    Mind::Matrix4x4f viewProjectionMatrix = requiredData.projectionMatrix * requiredData.viewMatrix ;
    m_ubos -> base() -> setViewProjectionMatrix(viewProjectionMatrix) ;

    viewProjectionMatrix.inverse(resultInverse) ;
    m_ubos -> base() -> setInverseViewProjectionMatrix(resultInverse) ;
}

void OpenGLFrameGraphVisitor::visit(FrustumCulling* /*node*/) {
    // TODO
}

void OpenGLFrameGraphVisitor::visit(Viewport* node) {
    if (!m_hasWindowChanged) {
        return ;
    }

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


    // Compute the viewport matrices.
    Mind::Scalar viewportX = relativePosition.get(Mind::Point2Df::X) ;
    Mind::Scalar viewportY = relativePosition.get(Mind::Point2Df::Y) ;
    Mind::Scalar viewportWidth = relativeDimension.width() ;
    Mind::Scalar viewportHeight = relativeDimension.height() ;
    Mind::Point3Df row0(viewportWidth / 2.f, 0.f, viewportWidth / (2 + viewportX)) ;
    Mind::Point3Df row1(0.f, viewportHeight/ 2.f, viewportHeight / (2 + viewportY)) ;
    Mind::Point3Df row2(0.f, 0.f, 1.f) ;

    Mind::Matrix4x4f viewportMatrix ;
    viewportMatrix.setRowValues(0, row0) ;
    viewportMatrix.setRowValues(1, row1) ;
    viewportMatrix.setRowValues(2, row2) ;

    Mind::Matrix4x4f inverseViewportMatrix ;
    viewportMatrix.inverse(inverseViewportMatrix) ;

    m_ubos -> base() -> setViewportMatrix(viewportMatrix) ;
    m_ubos -> base() -> setInverseViewportMatrix(inverseViewportMatrix) ;
}

void OpenGLFrameGraphVisitor::makeRender() {
    assert(m_aggregators.size() > 0) ;

    // Send data of the base UBO to the GPU before rendering this part of the
    // framegraph.
    m_ubos -> updateLightUBO(m_sceneCache) ;
    m_ubos -> base() -> update() ;
    m_sceneCache -> clearChanges() ;

    Hope::ProcessedSceneNode rootNode ;
    rootNode.node = m_sceneRoot ;
    rootNode.worldMatrix = (m_sceneRoot -> transform()).matrix() ;
    m_processedNodes.push(rootNode) ;

    while (m_processedNodes.size() > 0) {
        // For each entity: check if all the conditions are OK otherwise, go
        // back to the parent entity and process the other ones.
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
        m_activeOpenGLRenderVisitor -> setProcessedNode(m_processedNodes.top()) ;

        // Update the model UBO.
        RenderRequiredData& requiredData = m_activeOpenGLRenderVisitor -> requiredData() ;
        m_ubos -> updateModelUBO(
            m_processedNodes.top().worldMatrix,
            requiredData.viewMatrix,
            requiredData.projectionMatrix
        ) ;

        std::vector<std::vector<Component*>> components = renderedEntity -> components() ;
        for (std::vector<Component*> typeComponents : components) {
            for (Component* component : typeComponents) {
                if (component) {
                    component -> accept(m_activeOpenGLRenderVisitor) ;
                }
            }
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
