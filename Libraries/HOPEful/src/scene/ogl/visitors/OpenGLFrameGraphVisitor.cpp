#include <scene/ogl/visitors/OpenGLFrameGraphVisitor.hpp>
#include <scene/framegraph/ActiveCameraNode.hpp>
#include <scene/framegraph/ClearBuffersNode.hpp>
#include <scene/framegraph/FrustumCullingNode.hpp>
#include <scene/framegraph/RenderPassSelectorNode.hpp>
#include <scene/framegraph/ViewportNode.hpp>
#include <scene/framegraph/deferred/OffScreenRenderNode.hpp>
#include <scene/framegraph/deferred/DeferredRenderingNode.hpp>
#include <scene/components/RenderConfiguration.hpp>
#include <scene/ogl/Utils.hpp>
#include <Math.hpp>
#include <GLFW/glfw3.h>
#include <GL/glew.h>

using namespace Hope ;
using namespace Hope::GL ;

OpenGLFrameGraphVisitor::OpenGLFrameGraphVisitor()
    : IFrameGraphVisitor() {
    m_aggregators.push_back(FrameGraphBranchState()) ;
}

void OpenGLFrameGraphVisitor::setSceneRoot(Hope::Entity* root) {
    m_sceneRoot = root ;
}

void OpenGLFrameGraphVisitor::visit(ActiveCameraNode* node) {
    m_aggregators.back().setActiveCameraNode(node) ;

    if (node -> cacheEmpty()) {
        // Parse the scene graph.
        assert(m_aggregators.size() > 0) ;
        Hope::ProcessedSceneNode rootNode ;
        rootNode.node = m_sceneRoot ;
        rootNode.worldMatrix = (m_sceneRoot -> transform()).matrix() ;
        m_processedNodes.push(rootNode) ;

        while (m_processedNodes.size() > 0) {
            // For each entity: check if all the conditions are OK otherwise, go
            // back to the parent entity and process the other ones.
            // The children of an invalid entity are discarded as well.
            parseSceneGraph() ;
        }
    }
}

void OpenGLFrameGraphVisitor::visit(ClearBuffersNode* node) {
    BufferClearer::Clear(node -> buffers()) ;
}

void OpenGLFrameGraphVisitor::visit(FrustumCullingNode* /*node*/) {
    // TODO
}

void OpenGLFrameGraphVisitor::visit(OffScreenRenderNode* node) {
    m_aggregators.back().setOffScreenRenderNode(node) ;

    // Resize the framebuffer textures with the window if needed.
    if (m_hasWindowChanged && node -> windowSize()) {
        (node -> framebuffer()).resize(m_windowSize) ;
    }

    (node -> framebuffer()).bind() ;
}

void OpenGLFrameGraphVisitor::visit(DeferredRenderingNode* node) {
    m_aggregators.back().setRenderAtEnd(node -> renderingStepEnabled()) ;
    m_renderer.deferredShading(node -> material()) ;
}

void OpenGLFrameGraphVisitor::visit(RenderPassSelectorNode* node) {
    m_aggregators.back().setRenderPassID(node -> passID()) ;
}

void OpenGLFrameGraphVisitor::visit(ViewportNode* node) {
    if (!m_hasWindowChanged && (m_projectionData.lastViewport == node)) {
        return ;
    }

    m_projectionData.lastViewport = node ;

    Mind::Point2Df relativePosition = node -> position() ;
    Mind::Dimension2Df relativeDimension = node -> dimension() ;

    Mind::Point2Df absolutePosition(
        relativePosition.get(Mind::Point2Df::X) * m_windowSize.width(),
        relativePosition.get(Mind::Point2Df::Y) * m_windowSize.height()
    ) ;

    m_projectionData.absoluteAreaWidth = relativeDimension.width() * m_windowSize.width() ;
    m_projectionData.absoluteAreaHeight = relativeDimension.height() * m_windowSize.height() ;

    // Apply the viewport parameters.
    glViewport(
        absolutePosition.get(Mind::Point2Df::X),
        absolutePosition.get(Mind::Point2Df::Y),
        m_projectionData.absoluteAreaWidth,
        m_projectionData.absoluteAreaHeight
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

    m_renderer.baseUBO().setViewportMatrix(viewportMatrix) ;
    m_renderer.baseUBO().setInverseViewportMatrix(inverseViewportMatrix) ;
}

void OpenGLFrameGraphVisitor::makeRender() {
    FrameGraphBranchState& state = m_aggregators.back() ;

    if (!state.renderAtEnd() || state.activeCamera() == nullptr) {
        // Remove the last RenderConditionAggregator from the list!
        m_aggregators.pop_back() ;

        // Prevent rendering.
        return ;
    }

    updateCameraSettings() ;

    const std::shared_ptr<Hope::FrameRenderCache> cache = state.activeCameraCache() ;
    // Send data of the base UBO to the GPU before rendering this part of the
    // framegraph.
    m_renderer.updateLightUBO(cache) ;
    m_renderer.baseUBO().update() ;

    // Render the frame.
    m_renderer.render(
        state.renderPassID(),
        cache -> meshes()
    ) ;

    // Remove the last RenderConditionAggregator from the list!
    m_aggregators.pop_back() ;
}

void OpenGLFrameGraphVisitor::parseSceneGraph() {
    Hope::Entity* renderedEntity = m_processedNodes.top().node ;
    FrameGraphBranchState& state = m_aggregators.back() ;

    if (renderedEntity && state.conditions().check(renderedEntity)) {
        // Save the world matrix before pop.
        Mind::Matrix4x4f currentWorldMatrix = m_processedNodes.top().worldMatrix ;

        if (renderedEntity == state.activeCameraEntity()) {
            // Inverse as the world moves instead of the camera!
            m_renderer.baseUBO().setEyePosition(-currentWorldMatrix.extractTranslation()) ;
        }
        else {
            // Get components that need to be cached.
            state.activeCameraCache() -> cacheEntity(
                renderedEntity,
                currentWorldMatrix
            ) ;
        }

        // As the top node is processed, pop it from the stack.
        m_processedNodes.pop() ;

        // If the node has children, push them in the stack.
        const std::vector<Node*>& nodeChildren = renderedEntity -> children() ;
        for (const Hope::Node* child : nodeChildren) {
            const Hope::Entity* childEntityConst = static_cast<const Entity*>(child) ;
            Hope::Entity* childEntity = const_cast<Entity*>(childEntityConst) ;
            Mind::Matrix4x4f childMatrix = (childEntity -> transform()).matrix() ;

            Hope::ProcessedSceneNode childNode ;
            childNode.node = childEntity ;
            childNode.worldMatrix = currentWorldMatrix * childMatrix ;
            m_processedNodes.push(childNode) ;
        }
    }
}

void OpenGLFrameGraphVisitor::updateCameraSettings() {
    FrameGraphBranchState& state = m_aggregators.back() ;
    Hope::CameraComponent* camera = state.activeCamera() -> camera() ;
    const Hope::OffScreenRenderNode* offscreen = state.offScreenRender() ;
    camera -> update() ;

    // Set up the clear color.
    const Color& clearColor = camera -> clearColor() ;
    glClearColor(
        clearColor.red(),
        clearColor.green(),
        clearColor.blue(),
        clearColor.alpha()
    ) ;

    float aspectRatio = 0.f ;
    // Update the projection matrix.
    if (!offscreen || offscreen -> windowSize()) {
        aspectRatio = m_projectionData.absoluteAreaWidth / m_projectionData.absoluteAreaHeight ;
    }
    else {
        Mind::Dimension2Di framebufferSize = (offscreen -> framebuffer()).size() ;
        float width = framebufferSize.width() ;
        float height = framebufferSize.height() ;
        aspectRatio = width / height ;
    }

    Mind::Matrix4x4f projectionMatrix ;
    // Set up the projection matrix.
    camera -> projectionMatrix(projectionMatrix, aspectRatio) ;
    Mind::Matrix4x4f inverseProjectionMatrix ;
    projectionMatrix.inverse(inverseProjectionMatrix) ;

    m_renderer.baseUBO().setProjectionMatrix(projectionMatrix) ;
    m_renderer.baseUBO().setInverseProjectionMatrix(inverseProjectionMatrix) ;
    m_renderer.baseUBO().setAspectRatio(aspectRatio) ;
    m_renderer.setProjectionMatrix(projectionMatrix) ;

    // Update the model view matrix.
    const Mind::Matrix4x4f& viewMatrix = camera -> viewMatrix() ;

    // Update the required data.
    m_renderer.setViewMatrix(viewMatrix) ;
    m_renderer.baseUBO().setFarPlaneDistance(camera -> farPlaneDistance()) ;
    m_renderer.baseUBO().setTime(glfwGetTime()) ;
    m_renderer.baseUBO().setViewMatrix(viewMatrix) ;

    Mind::Matrix4x4f resultInverse ;
    viewMatrix.inverse(resultInverse) ;
    m_renderer.baseUBO().setInverseViewMatrix(resultInverse) ;

    Mind::Matrix4x4f viewProjectionMatrix = projectionMatrix * viewMatrix ;
    m_renderer.baseUBO().setViewProjectionMatrix(viewProjectionMatrix) ;

    viewProjectionMatrix.inverse(resultInverse) ;
    m_renderer.baseUBO().setInverseViewProjectionMatrix(resultInverse) ;
}
