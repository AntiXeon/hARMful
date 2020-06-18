#include <scene/framegraph/deferred/effects/shadows/cascade/ShadowCascade.hpp>
#include <scene/Entity.hpp>
#include <geometry/points/Point3Df.hpp>
#include <Math.hpp>
#include <limits>

using namespace Hope ;

const float ShadowCascade::SceneYLimit = 50.f ;

ShadowCascade::ShadowCascade(
    int8_t cascadeIndex,
	uint32_t resolution,
    Transform* cascadeRoot,
    OrthographicCameraComponent* computeCameraComponent
) : m_cascadeIndex(cascadeIndex),
	m_resolution(resolution),
    m_computeCameraComponent(computeCameraComponent) {

    if (m_cascadeIndex >= 0) {
        // Generate a "LightCamera" that will get the matrices from the
        // compute camera. This camera is used in the framegraph to set up
        // the camera matrices that are sent to the shaders, to compute the
        // related shadow depth map.
        m_lightCamTransform = std::make_unique<Transform>(cascadeRoot);
        m_lightCamera = std::make_shared<DirectionalLightCameraComponent>();
        m_lightCamTransform -> entity() -> addComponent(m_lightCamera);
    }
}

void ShadowCascade::update(
    CameraComponent* renderCam,
    const DirectionalLightComponent* light,
    std::array<Mind::Vector3f, CameraComponent::AmountFrustumCorners / 2>& frustumCornersWorld
) {
    static const uint8_t AmountFrustumSides = CameraComponent::AmountFrustumCorners / 2;
    std::array<Mind::Vector3f, CameraComponent::AmountFrustumCorners> cascadeCornersWorld = {} ;
    m_relativeCascadeNearPlane = m_cascadeNearPlane / renderCam -> farPlaneDistance() ;
    m_relativeCascadeFarPlane = m_cascadeFarPlane / renderCam -> farPlaneDistance() ;

    Entity* renderCamEntity = renderCam -> firstEntity() ;
    const Mind::Vector3f renderCamPosition = (renderCamEntity -> transform()).translation() ;

    // Maximal height in the current cascade frustum.
    float maxHeight = -std::numeric_limits<float>::max() ;
    Mind::Vector3f nearPlaneCenter;
    Mind::Vector3f farPlaneCenter;

    // Compute the near and far planes of the render camera frustum for the
    // current cascade.
    for (uint8_t sideIndex = 0 ; sideIndex < AmountFrustumSides ; ++sideIndex) {
        uint16_t side = sideIndex;
        auto nearFrustumPoint = frustumCornersWorld[side] * m_relativeCascadeNearPlane;
        nearPlaneCenter += nearFrustumPoint;
		cascadeCornersWorld[side] = renderCamPosition + nearFrustumPoint;

        side = sideIndex + AmountFrustumSides;
        auto farFrustumPoint = frustumCornersWorld[sideIndex] * m_relativeCascadeFarPlane;
        farPlaneCenter += farFrustumPoint;
        cascadeCornersWorld[side] = renderCamPosition + farFrustumPoint;

        maxHeight = std::max(maxHeight, cascadeCornersWorld[side].get(Mind::Vector3f::Y)) ;
	}

    nearPlaneCenter /= AmountFrustumSides;
    farPlaneCenter /= AmountFrustumSides;
    Mind::Vector3f frustumCenter(renderCamPosition + ((nearPlaneCenter + farPlaneCenter) / 2.f));
    float cascadeSphereRadius = Mind::Vector3f::distance(frustumCenter, cascadeCornersWorld[AmountFrustumSides]);

    // Compute the light view and projection matrices.
    updateLightViewMatrix(cascadeSphereRadius, frustumCenter, light -> direction()) ;
    updateLightProjectionMatrix(cascadeSphereRadius, cascadeCornersWorld) ;
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
    const float cascadeSphereRadius,
    const Mind::Vector3f& frustumCenter,
    const Mind::Vector3f& lightDirection
) {
    float computeCamX = frustumCenter.get(Mind::Vector3f::X);
    float computeCamZ = frustumCenter.get(Mind::Vector3f::Z);

    float texelsPerUnit = m_resolution / (cascadeSphereRadius * cascadeSphereRadius);

    float xMod = fmod(computeCamX, texelsPerUnit);
    computeCamX -= xMod;

    float zMod = fmod(computeCamZ, texelsPerUnit);
    computeCamZ -= zMod;

    Mind::Vector3f computeCamPosition(
        computeCamX,
        0.f,
        computeCamZ
    );

    // Set the direction of the compute camera.
    auto& computeTransform = m_computeCameraComponent -> firstEntity() -> transform();
    computeTransform.setTranslation(computeCamPosition);
	m_computeCameraComponent -> lookAt(computeCamPosition + lightDirection) ;

	// Extract its view matrix.
    m_lightViewMatrix = m_computeCameraComponent -> viewMatrix() ;
    m_lightCamera -> setViewMatrix(m_lightViewMatrix) ;
}

void ShadowCascade::updateLightProjectionMatrix(
    const float cascadeSphereRadius,
    const std::array<Mind::Vector3f, CameraComponent::AmountFrustumCorners>& frustumCornersWorld
) {
    Mind::Vector4f firstCorner = m_lightViewMatrix * Mind::Vector4f(frustumCornersWorld[0]) ;

    // // Now compute light frustum dimensions
    float minZ = firstCorner.get(Mind::Vector4f::Z) ;
    float maxZ = firstCorner.get(Mind::Vector4f::Z) ;

    for (int cornerIndex = 1 ; cornerIndex < CameraComponent::AmountFrustumCorners ; ++cornerIndex) {
        Mind::Vector4f corner(frustumCornersWorld[cornerIndex]) ;
        corner = m_lightViewMatrix * corner ;

        minZ = std::min(corner.get(Mind::Vector4f::Z), minZ) ;
        maxZ = std::max(corner.get(Mind::Vector4f::Z), maxZ) ;
    }

	m_computeCameraComponent -> setLeftPlane(-cascadeSphereRadius) ;
	m_computeCameraComponent -> setRightPlane(cascadeSphereRadius) ;
	m_computeCameraComponent -> setBottomPlane(-cascadeSphereRadius) ;
	m_computeCameraComponent -> setTopPlane(cascadeSphereRadius) ;
	m_computeCameraComponent -> setNearPlaneDistance(-std::max(maxZ, SceneYLimit)) ;
	m_computeCameraComponent -> setFarPlaneDistance(-minZ) ;
	m_computeCameraComponent -> projectionMatrix(m_lightProjectionMatrix, 1.f) ;
	m_lightCamera -> setProjectionMatrix(m_lightProjectionMatrix) ;


    //  Fix is to move the orthographic projection bounds in pixel size increments.
}
