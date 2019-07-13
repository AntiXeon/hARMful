#include <scene/framegraph/deferred/effects/shadows/DirectionalLightShadowNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>
#include <scene/components/cameras/OrthographicCameraComponent.hpp>
#include <scene/Entity.hpp>

#include <iostream>

using namespace Hope ;

const float DirectionalLightShadowNode::CascadeSplitStep = 2.5f ;

DirectionalLightShadowNode::DirectionalLightShadowNode(
    DirectionalLightComponent* light,
    ActiveCameraNode* renderingCamera,
    const uint32_t resolution,
    const float maxDistance,
    const uint8_t amountCascades,
    FrameGraphNode* parent
) : EffectFrameGraphNode(parent) {
    setRenderingStepEnabled(false) ;

    m_parameters.light = light ;
    m_parameters.resolution = resolution ;
    m_renderingCamera = renderingCamera ;
    m_parameters.amountCascades = std::min(static_cast<uint8_t>(MAX_AMOUNT_SHADOW_CASCADES), amountCascades) ;
    m_cascades.resize(m_parameters.amountCascades) ;

    Mind::Dimension3Di dimensions(resolution, resolution, m_parameters.amountCascades) ;
    m_framebuffer = new API::Framebuffer2DStack(dimensions) ;
    m_framebuffer -> attachDepth() ;
    m_framebuffer -> useNoColorBuffers() ;

    // Set the maximal distance at which shadows are rendered.
    if (maxDistance < 0.f) {
        m_parameters.useCameraFarPlaneDistance = true ;
        m_parameters.maxDistance = m_renderingCamera -> camera() -> farPlaneDistance() ;
    }
    else {
        m_parameters.useCameraFarPlaneDistance = false ;
        m_parameters.maxDistance = maxDistance ;
    }

    generateSubtree() ;
    m_effectData.setDirectionalLightShadow(this) ;
}

void DirectionalLightShadowNode::computeCascadeShadowMaps(const float aspectRatio) {
    // Compute the dimensions of the frustum of the rendering camera...
    CameraComponent* renderCam = m_renderingCamera -> camera() ;

    // Compute the far plane of the render camera frustum (the cascade planes
    // are deduced from it during their update).
    // From http://cgvr.cs.uni-bremen.de/teaching/cg_literatur/lighthouse3d_view_frustum_culling/
    const float RenderCamFOV = Mind::Math::toRadians(renderCam -> fov()) ;
    const Mind::Vector3f RenderCamViewDirection = -renderCam -> viewDirection() ;
    const Mind::Vector3f RenderCamUpVector = renderCam -> upOriented() ;
    const Mind::Vector3f RenderCamRightVector = renderCam -> rightAxis() ;

    const float RenderCamFarDistance = renderCam -> farPlaneDistance() ;
    const float HalfHeightFarPlane = (2.f * std::tan(RenderCamFOV / 2.f) * RenderCamFarDistance) / 2.f ;
    const Mind::Vector3f YAxisFarPlaneDistance = RenderCamUpVector * HalfHeightFarPlane ;
    const float HalfWidthFarPlane = HalfHeightFarPlane * aspectRatio ;
    const Mind::Vector3f XAxisFarPlaneDistance = RenderCamRightVector * HalfWidthFarPlane ;
    const Mind::Vector3f FarPlaneCenter = (RenderCamViewDirection * RenderCamFarDistance) ;

    // Store the render camera frustum points (far plane) in world space.
    std::array<Mind::Vector3f, CameraComponent::AmountFrustumCorners/2> frustumCornersWorld {
        FarPlaneCenter + YAxisFarPlaneDistance + XAxisFarPlaneDistance,
        FarPlaneCenter + YAxisFarPlaneDistance - XAxisFarPlaneDistance,
        FarPlaneCenter - YAxisFarPlaneDistance + XAxisFarPlaneDistance,
        FarPlaneCenter - YAxisFarPlaneDistance - XAxisFarPlaneDistance
    } ;

    // Update each cascade frustum.
    for (uint8_t cascadeIndex = 0 ; cascadeIndex < m_parameters.amountCascades ; ++cascadeIndex) {
        m_cascades[cascadeIndex].update(
            renderCam,
            m_parameters.light,
            frustumCornersWorld
        ) ;
    }
}

void DirectionalLightShadowNode::specificAccept(IFrameGraphVisitor* visitor) {
    // Update the maximal distance for computing shadows.
    if (m_parameters.useCameraFarPlaneDistance) {
        m_parameters.maxDistance = m_renderingCamera -> camera() -> farPlaneDistance() ;
    }

    visitor -> visit(this) ;
}

void DirectionalLightShadowNode::generateSubtree() {
    m_cascadeRoot = new Entity(sceneRoot()) ;

    // Generate an OrthographicCamera, to compute light matrices, that is child
    // of the cascade root.
    Entity* computeCamEntity = new Entity(m_cascadeRoot) ;
    OrthographicCameraComponent* computeCameraComponent = new OrthographicCameraComponent() ;
    computeCamEntity -> addComponent(computeCameraComponent) ;

    // Compute cascade distances.
    std::vector<float> cascadedSplits(m_parameters.amountCascades + 1) ;
    for (uint8_t cascadeIndex = 0 ; cascadeIndex < m_parameters.amountCascades ; ++cascadeIndex) {
        float step = std::pow(CascadeSplitStep, cascadeIndex) ;
        cascadedSplits[cascadeIndex] = m_parameters.maxDistance / step ;
    }
    cascadedSplits[m_parameters.amountCascades] = m_renderingCamera -> camera() -> nearPlaneDistance() ;

    // Create the cascade objects.
    for (uint8_t cascadeIndex = 0 ; cascadeIndex < m_parameters.amountCascades ; ++cascadeIndex) {
        m_cascades[cascadeIndex] = ShadowCascade(
            cascadeIndex,
            m_cascadeRoot,
            computeCameraComponent
        ) ;

        m_cascades[cascadeIndex].setNearPlane(cascadedSplits[cascadeIndex + 1]) ;
        m_cascades[cascadeIndex].setFarPlane(cascadedSplits[cascadeIndex]) ;
        m_cascades[cascadeIndex].setupFramegraph(
            this,
            m_renderingCamera,
            m_framebuffer
        ) ;
    }
}
