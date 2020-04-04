#include <scene/framegraph/deferred/effects/shadows/cascade/ShadowCascade.hpp>
#include <geometry/points/Point3Df.hpp>
#include <Math.hpp>
#include <limits>

using namespace Hope ;

ShadowCascade::ShadowCascade(
    int8_t cascadeIndex,
    Entity* cascadeRoot,
    OrthographicCameraComponent* computeCameraComponent
) : m_cascadeIndex(cascadeIndex),
    m_computeCameraComponent(computeCameraComponent) {

    if (m_cascadeIndex >= 0) {
        // Generate a "LightCamera" that will get the matrices from the
        // compute camera. This camera is used in the framegraph to set up
        // the camera matrices that are sent to the shaders, to compute the
        // related shadow depth map.
        m_lightCamEntity = std::make_unique<Entity>(cascadeRoot);
        m_lightCamera = std::make_unique<DirectionalLightCameraComponent>();
        m_lightCamEntity -> addComponent(m_lightCamera.get());
    }
}

void ShadowCascade::update(
    CameraComponent* renderCam,
    const DirectionalLightComponent* light,
    std::array<Mind::Vector3f, CameraComponent::AmountFrustumCorners / 2>& frustumCornersWorld
) {
    static const uint8_t AmountFrustumSides = 4 ;
    std::array<Mind::Vector3f, CameraComponent::AmountFrustumCorners> cascadeCornersWorld = {} ;
    m_relativeCascadeNearPlane = m_cascadeNearPlane / renderCam -> farPlaneDistance() ;
    m_relativeCascadeFarPlane = m_cascadeFarPlane / renderCam -> farPlaneDistance() ;

    Entity* renderCamEntity = renderCam -> firstEntity() ;
    const Mind::Vector3f renderCamPosition = (renderCamEntity -> transform()).translation() ;

    // Maximal height in the current cascade frustum.
    float maxHeight = -std::numeric_limits<float>::max() ;

    // Compute the near and far planes of the render camera frustum for the
    // current cascade.
    for (uint8_t sideIndex = 0 ; sideIndex < AmountFrustumSides ; ++sideIndex) {
		cascadeCornersWorld[sideIndex] = renderCamPosition + frustumCornersWorld[sideIndex] * m_relativeCascadeNearPlane ;
        cascadeCornersWorld[sideIndex + AmountFrustumSides] = renderCamPosition + frustumCornersWorld[sideIndex] * m_relativeCascadeFarPlane ;
        maxHeight = std::max(maxHeight, cascadeCornersWorld[sideIndex + AmountFrustumSides].get(Mind::Vector3f::Y)) ;
	}

    Mind::Vector3f lightPosition ;
    lightPosition.set(Mind::Vector3f::Y, maxHeight) ;

    // Compute the light view and projection matrices.
    updateLightViewMatrix(lightPosition, light -> direction()) ;
    updateLightProjectionMatrix(cascadeCornersWorld) ;
}

void ShadowCascade::setupFramegraph(
    FrameGraphNode* owner,
    ActiveCameraNode* renderingCamera,
    API::Framebuffer2DStack* framebuffer
) {
    // 1. Set up the camera node for the depth map rendering.
    m_fgSubtree.lightSpaceCamera = std::make_unique<ActiveCameraNode>(owner, renderingCamera) ;
    m_fgSubtree.lightSpaceCamera -> setCamera(m_lightCamera.get()) ;

    // 2. Select the DirectionalShadowPassID to only render the depth map from
    //    the light point-of-view.
    m_fgSubtree.depthMapPassSelector = std::make_unique<RenderPassSelectorNode>(
        DirectionalShadowPassID,
        m_fgSubtree.lightSpaceCamera.get()
    ) ;

    // 3. Framebuffer to draw the depth map in.
    static const bool WindowSizedFramebuffer2D = false ;
    m_fgSubtree.offscreenBuffer = std::make_unique<LayerFramebufferRenderNode>(
        framebuffer,
        m_cascadeIndex,
        WindowSizedFramebuffer2D,
        m_fgSubtree.depthMapPassSelector.get()
    ) ;

    // 4. Clear the depth buffer from the previous frame.
    m_fgSubtree.clearBuffers = std::make_unique<ClearBuffersNode>(
        API::BufferClearer::Buffer::Depth,
        m_fgSubtree.offscreenBuffer.get()
    ) ;
}

void ShadowCascade::updateLightViewMatrix(
    const Mind::Vector3f&,
    const Mind::Vector3f& lightDirection
) {
    // Set the direction of the compute camera.
    m_computeCameraComponent -> lookAt(lightDirection) ;
    // Extract its view matrix.
    m_lightViewMatrix = m_computeCameraComponent -> viewMatrix() ;
    m_lightCamera -> setViewMatrix(m_lightViewMatrix) ;
}

void ShadowCascade::updateLightProjectionMatrix(
    const std::array<Mind::Vector3f, CameraComponent::AmountFrustumCorners>& frustumCornersWorld
) {
    Mind::Vector4f firstCorner = m_lightViewMatrix * Mind::Vector4f(frustumCornersWorld[0]) ;

    // Now compute light frustum dimensions
    float minX = firstCorner.get(Mind::Vector4f::X) ;
    float maxX = firstCorner.get(Mind::Vector4f::X) ;
    float minY = firstCorner.get(Mind::Vector4f::Y) ;
    float maxY = firstCorner.get(Mind::Vector4f::Y) ;
    float minZ = firstCorner.get(Mind::Vector4f::Z) ;
    float maxZ = firstCorner.get(Mind::Vector4f::Z) ;

    for (int cornerIndex = 1 ; cornerIndex < CameraComponent::AmountFrustumCorners ; ++cornerIndex) {
        Mind::Vector4f corner(frustumCornersWorld[cornerIndex]) ;
        corner = m_lightViewMatrix * corner ;

        minX = std::min(corner.get(Mind::Vector4f::X), minX) ;
        maxX = std::max(corner.get(Mind::Vector4f::X), maxX) ;
        minY = std::min(corner.get(Mind::Vector4f::Y), minY) ;
        maxY = std::max(corner.get(Mind::Vector4f::Y), maxY) ;
        minZ = std::min(corner.get(Mind::Vector4f::Z), minZ) ;
        maxZ = std::max(corner.get(Mind::Vector4f::Z), maxZ) ;
    }

    m_computeCameraComponent -> setLeftPlane(minX) ;
    m_computeCameraComponent -> setRightPlane(maxX) ;
    m_computeCameraComponent -> setBottomPlane(minY) ;
    m_computeCameraComponent -> setTopPlane(maxY) ;
    m_computeCameraComponent -> setNearPlaneDistance(-maxZ) ;
    m_computeCameraComponent -> setFarPlaneDistance(-minZ) ;
    m_computeCameraComponent -> projectionMatrix(m_lightProjectionMatrix, 1.f) ;
    m_lightCamera -> setProjectionMatrix(m_lightProjectionMatrix) ;
}
