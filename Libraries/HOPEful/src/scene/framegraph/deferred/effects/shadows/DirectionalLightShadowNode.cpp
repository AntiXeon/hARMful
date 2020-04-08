#include <scene/framegraph/deferred/effects/shadows/DirectionalLightShadowNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

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

	createFramebuffer(resolution) ;

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

	const Mind::Vector3f RenderCamUpVector = renderCam -> upOriented() ;
	const Mind::Vector3f RenderCamRightVector = renderCam -> rightAxis() ;
	const Mind::Vector3f RenderCamViewDirection = -renderCam -> viewDirection() ;

	const float RenderCamFarDistance = renderCam -> farPlaneDistance() ;
	const Mind::Vector3f FarCenter = RenderCamViewDirection * RenderCamFarDistance ;

	const float RenderCamFOV = Mind::Math::toRadians(renderCam -> fov()) ;
	const float TanHalfRenderCamFOV = tan(RenderCamFOV / 2.f) ;
	const float FarHeight = TanHalfRenderCamFOV * RenderCamFarDistance ;
	const float FarWidth = FarHeight * aspectRatio ;

	// Store the render camera frustum points in world space.
	auto FarHeightShift = RenderCamUpVector * FarHeight ;
	auto FarWidthShift = RenderCamRightVector *FarWidth ;
    std::array<Mind::Vector3f, CameraComponent::AmountFrustumCorners / 2> frustumCornersWorld {
		// Far plane.
		FarCenter - FarHeightShift - FarWidthShift,
		FarCenter + FarHeightShift - FarWidthShift,
		FarCenter + FarHeightShift + FarWidthShift,
		FarCenter - FarHeightShift + FarWidthShift
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

exported void DirectionalLightShadowNode::createFramebuffer(const uint32_t resolution) {
	uint32_t realResolution = resolution + ShadowMapMoveAmplitude ;

	Mind::Dimension3Di dimensions(realResolution, realResolution, m_parameters.amountCascades) ;
    m_framebuffer = std::make_unique<API::Framebuffer2DStack>(dimensions) ;
    m_framebuffer -> attachDepth() ;
    m_framebuffer -> useNoColorBuffers() ;
}

void DirectionalLightShadowNode::specificAccept(IFrameGraphVisitor* visitor) {
    // Update the maximal distance for computing shadows.
    if (m_parameters.useCameraFarPlaneDistance) {
        m_parameters.maxDistance = m_renderingCamera -> camera() -> farPlaneDistance() ;
    }

    visitor -> visit(this) ;
}

void DirectionalLightShadowNode::generateSubtree() {
    m_cascadeRoot = std::unique_ptr<Entity>(sceneRoot()) ;

    // Generate an OrthographicCamera, to compute light matrices, that is child
    // of the cascade root.
    m_computeCamEntity = std::make_unique<Entity>(m_cascadeRoot.get()) ;
    m_computeCameraComponent = std::make_unique<OrthographicCameraComponent>() ;
    m_computeCamEntity -> addComponent(m_computeCameraComponent.get()) ;

    // Compute cascade distances.
    std::vector<float> cascadedSplits(m_parameters.amountCascades + 1) ;
    for (uint8_t cascadeIndex = 0 ; cascadeIndex < m_parameters.amountCascades ; ++cascadeIndex) {
        float step = static_cast<float>(std::pow(CascadeSplitStep, cascadeIndex)) ;
        cascadedSplits[cascadeIndex] = m_parameters.maxDistance / step ;
    }
    cascadedSplits[m_parameters.amountCascades] = m_renderingCamera -> camera() -> nearPlaneDistance() ;

    // Create the cascade objects.
    for (uint8_t cascadeIndex = 0 ; cascadeIndex < m_parameters.amountCascades ; ++cascadeIndex) {
        m_cascades[cascadeIndex] = ShadowCascade(
            cascadeIndex,
			m_parameters.resolution,
            m_cascadeRoot.get(),
            m_computeCameraComponent.get()
        ) ;

        m_cascades[cascadeIndex].setNearPlane(cascadedSplits[cascadeIndex + 1]) ;
        m_cascades[cascadeIndex].setFarPlane(cascadedSplits[cascadeIndex]) ;
        m_cascades[cascadeIndex].setupFramegraph(
            this,
            m_renderingCamera,
            m_framebuffer.get()
        ) ;
    }
}
