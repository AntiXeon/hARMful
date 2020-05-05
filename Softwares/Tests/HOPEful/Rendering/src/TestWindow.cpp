#include <TestWindow.hpp>
#include <scene/framegraph/ActiveCameraNode.hpp>
#include <scene/framegraph/RenderPassSelectorNode.hpp>
#include <scene/framegraph/ViewportNode.hpp>
#include <scene/framegraph/ClearBuffersNode.hpp>
#include <scene/framegraph/RenderCapabilityNode.hpp>
#include <scene/framegraph/deferred/effects/shadows/DirectionalLightShadowNode.hpp>
#include <scene/framegraph/deferred/effects/fog/FogRenderNode.hpp>
#include <scene/framegraph/deferred/effects/ao/SSAORenderNode.hpp>
#include <scene/framegraph/deferred/offscreen/GBufferRenderNode.hpp>
#include <scene/framegraph/deferred/DeferredRenderingNode.hpp>
#include <scene/components/mesh/MeshTreeComponent.hpp>
#include <scene/components/mesh/builtin/CubeGeometryComponent.hpp>
#include <scene/components/mesh/builtin/QuadGeometryComponent.hpp>
#include <scene/components/materials/deferred/GBufferQuadMaterialComponent.hpp>
#include <scene/components/materials/EnvironmentMapMaterialComponent.hpp>
#include <scene/components/lights/DirectionalLightComponent.hpp>
#include <scene/components/lights/PointLightComponent.hpp>
#include <scene/ogl/rendering/capabilities/SeamlessCubemap.hpp>

#include <files/images/ImageFile.hpp>
#include <Math.hpp>

#include <algorithm>
#include <memory>

const std::string TestWindow::AppName = "Rendering test" ;

#define     WIDTH   1400
#define     HEIGHT  900

TestWindow::TestWindow()
    : Hope::GL::Window(WIDTH, HEIGHT, AppName) {
    //fullscreen() ;
    disableMouseCursor() ;

    /** SCENE GRAPH **/
    // Create a camera in the scene graph.
    m_cameraTransform = new Hope::Transform(root()) ;
    m_cameraComponent = new Hope::PerspectiveCameraComponent() ;

    m_cameraComponent -> setClearColor(Hope::Color(0.5f, 0.1f, 0.1f));
    m_cameraComponent -> setFOV(50.f);
    m_cameraComponent -> setFarPlaneDistance(100.f);
    m_cameraComponent -> lookAt(Mind::Vector3f(0.f, 0.f, 0.f)) ;

    m_cameraTransform -> entity() -> addComponent(m_cameraComponent);
    m_cameraTransform -> entity() -> setLocked(true) ;

    // Cubemap.
    {
        Hope::Transform* cubemapTransform = new Hope::Transform(root()) ;
        cubemapTransform -> entity() -> setLocked(true) ;

        // auto cubemapTexture = std::make_unique<Hope::GL::CubemapTexture>(cubemapTexturePaths) ;
		auto cubemap = std::make_unique<Hope::GL::EnvironmentMap>("../data/meshes/textures/", "palermo_sidewalk_1k") ;

        Hope::EnvironmentMapMaterialComponent* cubemapMaterial = new Hope::EnvironmentMapMaterialComponent() ;
        cubemapMaterial -> setCubemap(cubemap) ;

        cubemapTransform -> entity() -> addComponent(cubemapMaterial) ;
        Hope::CubeGeometryComponent* cubeGeometry = new Hope::CubeGeometryComponent() ;
        cubemapTransform -> entity() -> addComponent(cubeGeometry) ;
    }

/*
    // Mesh test.
    {
        Hope::Transform* meshTreeTransform = new Hope::Transform(root()) ;
        meshTreeTransform -> setScale(10.f) ;
        Hope::MeshTreeComponent* meshTreeComponent = new Hope::MeshTreeComponent("../data/meshes/WoodenTable.fbx") ;
        meshTreeTransform -> entity() -> addComponent(meshTreeComponent) ;

        m_cubeTransform = meshTreeComponent -> transform("Cube") ;
    }
*/
    // Create a directional light.
    Hope::DirectionalLightComponent* dirLightComponent = nullptr ;
	{
		Hope::Transform* dirLightTransform = new Hope::Transform(root()) ;
		dirLightComponent = new Hope::DirectionalLightComponent() ;
		dirLightComponent -> setDirection(Mind::Vector3f(-0.5f, -0.8f, 0.5f)) ;
		dirLightComponent -> setColor(Hope::Color(1.f, 0.95f, 0.95f, 1.f)) ;
		dirLightComponent -> setPower(1.f) ;
		dirLightComponent -> setSpecularGenerated(true) ;
		dirLightTransform -> entity() -> addComponent(dirLightComponent) ;
        dirLightTransform -> entity() -> setLocked(true) ;
	}


	// // Point light
    // {
    //     Hope::Color lightColor(1.f, 1.f, 1.f) ;
	//
    // 	Hope::Transform* parentLightTransform = new Hope::Transform(root()) ;
    //     parentLightTransform -> setTranslation(Mind::Vector3f(0.f, 1.f, 1.f)) ;
	//
    //     Hope::Transform* pointLightTransform = new Hope::Transform(parentLightTransform) ;
    //     Hope::PointLightComponent* pointLightComponent = new Hope::PointLightComponent() ;
    //     pointLightComponent -> setColor(lightColor) ;
    //     pointLightComponent -> setPower(1.f) ;
    //     pointLightComponent -> setSpecularGenerated(false) ;
    //     pointLightComponent -> setQuadraticAttenuation(0.f) ;
    //     pointLightComponent -> setLinearAttenuation(1.f) ;
    //     pointLightTransform -> entity() -> addComponent(pointLightComponent) ;
    //     pointLightTransform -> entity() -> setLocked(true) ;
    // }

    /** FRAME GRAPH **/
    Hope::ActiveCameraNode* activeCameraNode = new Hope::ActiveCameraNode() ;
    activeCameraNode -> setCamera(m_cameraComponent) ;

    /*
                      +-- SSAORender
                      |
                      +-- ActiveCamera -- G-Buffer
                      |
        root-- +-- Viewport
               |      |
               |      +-- DeferredRendering
               |
               +-- ShadowMap (- ActiveCamera -- ClearDepthBuffer -- DepthBuffer)
     */

    Hope::FrameGraphNode* rootFG = new Hope::FrameGraphNode() ;

    // -- Shadow mapping pass --
    const uint32_t ShadowResolution = 2048 ;
    float maxDistance = 250.f ;
    uint8_t amountCascades = 4 ;
    new Hope::DirectionalLightShadowNode(
        dirLightComponent,
        activeCameraNode,
        ShadowResolution,
        maxDistance,
        amountCascades,
        rootFG
    ) ;

    // // -- Fog effect --
    // new Hope::FogRenderNode(
    //     Hope::Color(0.4f, 0.5f, 0.6f, 0.7f),
    //     100.f,
    //     300.f,
    //     rootFG
    // ) ;

    // -- Rendering pass --
    Hope::ViewportNode* viewportNode = new Hope::ViewportNode(rootFG) ;
    viewportNode -> setPosition(Mind::Point2Df(0.f, 0.f)) ;
    viewportNode -> setDimension(Mind::Dimension2Df(1.f, 1.f)) ;

    // G-Buffer branch of the framegraph.
    //renderingActiveCameraNode -> setParent(viewportNode) ;
    activeCameraNode -> setParent(viewportNode) ;

    Hope::RenderCapabilityNode* capabilitiesNode = new Hope::RenderCapabilityNode(activeCameraNode) ;
    Hope::GL::SeamlessCubemap* seamlessCubemap = new Hope::GL::SeamlessCubemap() ;
    capabilitiesNode -> addCapability(seamlessCubemap) ;

    Hope::GBufferRenderNode* gBufferNode = new Hope::GBufferRenderNode(
        Mind::Dimension2Di(WIDTH, HEIGHT),
        capabilitiesNode
    ) ;

    Hope::ClearBuffersNode* clearBuffers = new Hope::ClearBuffersNode(Hope::GL::BufferClearer::Buffer::ColorDepth, gBufferNode) ;
    new Hope::RenderPassSelectorNode(DeferredPassID, clearBuffers) ;

    new Hope::DeferredRenderingNode(
        gBufferNode,
        viewportNode
    ) ;

    // Use the frame graph.
    setFrameGraphRoot(rootFG) ;
}

void TestWindow::preRender() {
    //double time = glfwGetTime() ;
    //float radius = 10.f ;
    //float camX = static_cast<float>(sin(time / 2.f) * radius) ;
    //float camZ = static_cast<float>(cos(time / 2.f) * radius) ;

    //const Mind::Vector3f shift(-30.f, 0.f, 80.f);
    //Mind::Vector3f camPos(/*-4.f, 3.f, 7.f*/ camX, 1.7f, camZ) ;

    //(m_cameraTransform -> transform()).setTranslation(camPos + shift) ;
    //m_cameraComponent->lookAt(shift);
}

void TestWindow::postRender() {
    // Nothing to do for now!
    m_cameraTransform -> setTranslation(m_cameraPosition);
    m_cameraComponent -> lookAt(m_cameraPosition + m_cameraDirection);
    m_lastTime = glfwGetTime();
}

void TestWindow::keyboard(
    const int,
    const int scancode,
    const int action,
    const int mods
) {
    const float CameraSpeed = 100.f;
    const float SpeedBoost = 10.f;

    auto direction = m_cameraComponent -> viewDirection();
    auto up = m_cameraComponent -> up();
    auto right = direction.cross(up);
    double deltaTime = glfwGetTime() - m_lastTime;

    float speed = CameraSpeed * deltaTime;

    if (mods & GLFW_MOD_SHIFT) {
        speed *= SpeedBoost;
    }

    const int scancodeW = glfwGetKeyScancode(GLFW_KEY_W);
    if (scancode == scancodeW && action == GLFW_REPEAT) {
        auto shift = direction * -speed;
        m_cameraPosition += shift;
    }

    const int scancodeS = glfwGetKeyScancode(GLFW_KEY_S);
    if (scancode == scancodeS && action == GLFW_REPEAT) {
        auto shift = direction * speed;
        m_cameraPosition += shift;
    }

    const int scancodeA = glfwGetKeyScancode(GLFW_KEY_A);
    if (scancode == scancodeA && action == GLFW_REPEAT) {
        auto shift = right * speed;
        m_cameraPosition += shift;
    }

    const int scancodeD = glfwGetKeyScancode(GLFW_KEY_D);
    if (scancode == scancodeD && action == GLFW_REPEAT) {
        auto shift = right * -speed;
        m_cameraPosition += shift;
    }

    const int scancodeSpace = glfwGetKeyScancode(GLFW_KEY_SPACE);
    if (scancode == scancodeSpace && action == GLFW_REPEAT) {
        auto shift = up * speed;
        m_cameraPosition += shift;
    }
}

void TestWindow::mouse(
    const double x,
    const double y
) {
    float halfWidth = width() / 2.f;
    float halfHeight = height() / 2.f;

    float adjustedX = static_cast<float>(x) - halfWidth;
    float adjustedY = static_cast<float>(y) - halfHeight;

    float rotationX = static_cast<float>(adjustedX - m_oldCursorPosition.x) * m_mouseSensibility;
    float rotationY = static_cast<float>(m_oldCursorPosition.y - adjustedY) * m_mouseSensibility;

    m_oldCursorPosition.x = adjustedX;
    m_oldCursorPosition.y = adjustedY;

    m_cameraYaw += rotationX;
    m_cameraPitch += rotationY;
    m_cameraPitch = std::clamp(m_cameraPitch, -89.f, 89.f);

    m_cameraDirection.set(
		Mind::Vector3f(
	        std::cos(Mind::Math::toRadians(m_cameraYaw)) * std::cos(Mind::Math::toRadians(m_cameraPitch)),
	        std::sin(Mind::Math::toRadians(m_cameraPitch)),
	        std::sin(Mind::Math::toRadians(m_cameraYaw)) * std::cos(Mind::Math::toRadians(m_cameraPitch))
    	)
	);
    m_cameraDirection.normalize();
}
