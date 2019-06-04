#include <scene/framegraph/DirectionalLightShadowNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>
#include <scene/components/cameras/OrthographicCameraComponent.hpp>
#include <scene/Entity.hpp>
#include <scene/components/cameras/Utils.hpp>
#include <limits>

#include <iostream>

using namespace Hope ;

DirectionalLightShadowNode::DirectionalLightShadowNode(
    DirectionalLightComponent* light,
    ActiveCameraNode* renderingCamera,
    const Mind::Dimension2Di& resolution,
    const float maxDistance,
    FrameGraphNode* parent
) : FrameGraphNode(parent) {
    setRenderingStepEnabled(false) ;

    m_light = light ;
    m_renderingCamera = renderingCamera ;
    m_resolution = resolution ;

    if (m_maxDistance < 0.f) {
        m_useCameraFarPlaneDistance = true ;
        m_maxDistance = m_renderingCamera -> camera() -> farPlaneDistance() ;
    }
    else {
        m_useCameraFarPlaneDistance = false ;
        m_maxDistance = maxDistance ;
    }

    generateSubtree() ;
}

void DirectionalLightShadowNode::computeShadowCamFrustum(const float aspectRatio) {
    /* The code is highly inspired by http://ogldev.atspace.co.uk/www/tutorial49/tutorial49.html */
    // Get the light space transform.
    m_lightCameraComponent -> lookAt(m_light -> direction()) ;
    const Mind::Matrix4x4f& lightViewMatrix = m_lightCameraComponent -> viewMatrix() ;

    // Compute the dimensions of the frustum for the rendering camera...
    CameraComponent* renderCam = m_renderingCamera -> camera() ;
    float halfFOV = (renderCam -> fov()) / 2.f ;
    float tanHalfHorizontalFOV = std::tan(Mind::Math::toRadians(halfFOV)) ;
    float tanHalfVerticalFOV = std::tan(Mind::Math::toRadians(halfFOV * aspectRatio)) ;
    // ... and its inverse view matrix.
    Mind::Matrix4x4f inverseRenderViewMatrix ;
    (renderCam -> viewMatrix()).inverse(inverseRenderViewMatrix) ;

    /*for (uint8_t cascadeIndex = 0 ; cascadeIndex < AmountCascadeShadowMaps ; ++cascadeIndex) {*/
        float renderCameraNearDistance = renderCam -> nearPlaneDistance() ;
        float xNear = renderCameraNearDistance * tanHalfHorizontalFOV ;
        float yNear = renderCameraNearDistance * tanHalfVerticalFOV ;
        float xFar = m_maxDistance * tanHalfHorizontalFOV ;
        float yFar = m_maxDistance * tanHalfVerticalFOV ;

        // Set the corners of the frustum for the rendering camera.
        Mind::Vector4f renderFrustumCorners[CameraComponent::AmountFrustumCorners] = {
            // Near face.
            Mind::Vector4f( xNear,  yNear, renderCameraNearDistance, 1.f),
            Mind::Vector4f(-xNear,  yNear, renderCameraNearDistance, 1.f),
            Mind::Vector4f( xNear, -yNear, renderCameraNearDistance, 1.f),
            Mind::Vector4f(-xNear, -yNear, renderCameraNearDistance, 1.f),

            // Far face.
            Mind::Vector4f( xFar,  yFar, m_maxDistance, 1.f),
            Mind::Vector4f(-xFar,  yFar, m_maxDistance, 1.f),
            Mind::Vector4f( xFar, -yFar, m_maxDistance, 1.f),
            Mind::Vector4f(-xFar, -yFar, m_maxDistance, 1.f)
        } ;

        // Set the corners of the frustum for the light shadow camera.
        // We search for the minimal size of this frustum.
        Mind::Vector4f lightFrustumCorners[CameraComponent::AmountFrustumCorners] ;
        float minLightFrustumX = std::numeric_limits<float>::max() ;
        float maxLightFrustumX = std::numeric_limits<float>::min() ;
        float minLightFrustumY = std::numeric_limits<float>::max() ;
        float maxLightFrustumY = std::numeric_limits<float>::min() ;
        float minLightFrustumZ = std::numeric_limits<float>::max() ;
        float maxLightFrustumZ = std::numeric_limits<float>::min() ;

        for (uint8_t cornerIndex = 0 ; cornerIndex < CameraComponent::AmountFrustumCorners ; ++cornerIndex) {
            // Transform the frustum coordinate from view to world space.
            Mind::Vector4f cornerWorld = inverseRenderViewMatrix * renderFrustumCorners[cornerIndex] ;
            // Transform the frustum coordinate from world to light space.
            lightFrustumCorners[cornerIndex] = lightViewMatrix * cornerWorld ;

            minLightFrustumX = std::min(minLightFrustumX, lightFrustumCorners[cornerIndex].get(Mind::Vector4f::X)) ;
            maxLightFrustumX = std::max(maxLightFrustumX, lightFrustumCorners[cornerIndex].get(Mind::Vector4f::X)) ;
            minLightFrustumY = std::min(minLightFrustumY, lightFrustumCorners[cornerIndex].get(Mind::Vector4f::Y)) ;
            maxLightFrustumY = std::max(maxLightFrustumY, lightFrustumCorners[cornerIndex].get(Mind::Vector4f::Y)) ;
            minLightFrustumZ = std::min(minLightFrustumZ, lightFrustumCorners[cornerIndex].get(Mind::Vector4f::Z)) ;
            maxLightFrustumZ = std::max(maxLightFrustumZ, lightFrustumCorners[cornerIndex].get(Mind::Vector4f::Z)) ;
        }

        // Apply this minimal frustum to the light shadow camera.
        m_lightCameraComponent -> setLeftPlane(minLightFrustumX) ;
        m_lightCameraComponent -> setRightPlane(maxLightFrustumX) ;
        m_lightCameraComponent -> setBottomPlane(minLightFrustumY) ;
        m_lightCameraComponent -> setTopPlane(maxLightFrustumY) ;
        m_lightCameraComponent -> setNearPlaneDistance(minLightFrustumZ) ;
        m_lightCameraComponent -> setFarPlaneDistance(maxLightFrustumZ) ;
    /*}*/
}

void DirectionalLightShadowNode::specificAccept(IFrameGraphVisitor* visitor) {
    // Update the maximal distance for computing shadows.
    if (m_useCameraFarPlaneDistance) {
        m_maxDistance = m_renderingCamera -> camera() -> farPlaneDistance() ;
    }

    visitor -> visit(this) ;
}

void DirectionalLightShadowNode::generateSubtree() {
    // 1. Generate an OrthographicCamera that is child of the scene root.
    Entity* shadowCamEntity = new Entity(sceneRoot()) ;
    (shadowCamEntity -> transform()).setTranslation(Mind::Vector3f(10.f, 10.f, 10.f)) ;
    m_lightCameraComponent = new OrthographicCameraComponent() ;
    shadowCamEntity -> addComponent(m_lightCameraComponent) ;
    // Set up the camera node for the depth map rendering.
    m_subtree.lightSpaceCamera = new ActiveCameraNode(this, m_renderingCamera) ;
    m_subtree.lightSpaceCamera -> setCamera(m_lightCameraComponent) ;

    // 2. Select the DirectionalShadowPassID to only render the depth map from
    //    the light point-of-view.
    m_subtree.depthMapPassSelector = new RenderPassSelectorNode(
        DirectionalShadowPassID,
        m_subtree.lightSpaceCamera
    ) ;

    // 3. Clear the depth buffer from the previous frame.
    m_subtree.clearBuffers = new ClearBuffersNode(
        API::BufferClearer::Buffer::Depth,
        m_subtree.depthMapPassSelector
    ) ;

    // 4. Framebuffer to draw the depth map in.
    static const bool WindowSizedFramebuffer = false ;
    m_subtree.offscreenBuffer = new OffScreenRenderNode(
        m_resolution,
        WindowSizedFramebuffer,
        m_subtree.clearBuffers
    ) ;
    (m_subtree.offscreenBuffer -> framebuffer()).attachDepth() ;
    (m_subtree.offscreenBuffer -> framebuffer()).useNoColorBuffers() ;
}
