#include <TestWindow.hpp>
#include <scene/framegraph/ActiveCameraNode.hpp>
#include <scene/framegraph/RenderPassSelectorNode.hpp>
#include <scene/framegraph/ViewportNode.hpp>
#include <scene/framegraph/ClearBuffersNode.hpp>
#include <scene/framegraph/RenderCapabilityNode.hpp>
#include <scene/framegraph/deferred/effects/shadows/DirectionalLightShadowNode.hpp>
#include <scene/framegraph/deferred/GBufferRenderNode.hpp>
#include <scene/framegraph/deferred/DeferredRenderingNode.hpp>
#include <scene/framegraph/deferred/FinalStepRenderingNode.hpp>
#include <scene/framegraph/deferred/effects/ao/SSAORenderNode.hpp>
#include <scene/components/mesh/MeshTreeComponent.hpp>
#include <scene/components/mesh/builtin/CubeGeometryComponent.hpp>
#include <scene/components/mesh/builtin/QuadGeometryComponent.hpp>
#include <scene/components/materials/BlinnPhongMaterialComponent.hpp>
#include <scene/components/materials/deferred/GBufferQuadMaterialComponent.hpp>
#include <scene/components/materials/CubemapMaterialComponent.hpp>
#include <scene/components/lights/DirectionalLightComponent.hpp>
#include <scene/components/lights/PointLightComponent.hpp>

#include <scene/ogl/rendering/capabilities/SeamlessCubemap.hpp>

const std::string TestWindow::AppName = "Rendering test" ;

TestWindow::TestWindow()
    : Hope::GL::Window(800, 480, AppName) {
    // fullscreen() ;
    // hideMouseCursor() ;

    /** SCENE GRAPH **/
    // Create a camera in the scene graph.
    m_cameraEntity = new Hope::Entity(scene() -> root()) ;
    m_cameraComponent = new Hope::PerspectiveCameraComponent() ;
    m_cameraComponent -> setClearColor(Hope::Color(DefaultClearColor)) ;
    m_cameraComponent -> setFarPlaneDistance(100.f) ;
    m_cameraEntity -> addComponent(m_cameraComponent) ;
    m_cameraComponent -> lookAt(Mind::Vector3f(0.f, 0.f, 0.f)) ;

    // Cubemap.
    {
        std::array<std::string, Hope::GL::CubemapTexture::AmountFaces> cubemapTexturePaths = {
            "../data/meshes/cubemap/right.jpg",
            "../data/meshes/cubemap/left.jpg",
            "../data/meshes/cubemap/top.jpg",
            "../data/meshes/cubemap/bottom.jpg",
            "../data/meshes/cubemap/back.jpg",
            "../data/meshes/cubemap/front.jpg"
        } ;

        Hope::Entity* cubemapEntity = new Hope::Entity(scene() -> root()) ;

        Hope::GL::CubemapTexture* cubemapTexture = new Hope::GL::CubemapTexture(cubemapTexturePaths) ;
        Hope::CubemapMaterialComponent* cubemapMaterial = new Hope::CubemapMaterialComponent() ;
        cubemapMaterial -> setCubemap(cubemapTexture) ;
        cubemapEntity -> addComponent(cubemapMaterial) ;

        Hope::CubeGeometryComponent* cubeGeometry = new Hope::CubeGeometryComponent() ;
        cubemapEntity -> addComponent(cubeGeometry) ;
    }


    // Mesh test.
    {
        Hope::Entity* meshTreeEntity = new Hope::Entity(scene() -> root()) ;
        (meshTreeEntity -> transform()).setScale(0.1f) ;
        Hope::MeshTreeComponent* meshTreeComponent = new Hope::MeshTreeComponent("../data/meshes/Test.fbx") ;
        meshTreeEntity -> addComponent(meshTreeComponent) ;
    }

    // Create a directional light.
    Hope::DirectionalLightComponent* dirLightComponent = nullptr ;
	{
		Hope::Entity* dirLightEntity = new Hope::Entity(scene() -> root()) ;
		dirLightComponent = new Hope::DirectionalLightComponent() ;
		dirLightComponent -> setDirection(Mind::Vector3f(0.3f, -0.5f, 0.5f)) ;
		dirLightComponent -> setColor(Hope::Color(1.f, 1.f, 0.95f, 1.f)) ;
		dirLightComponent -> setPower(1.f) ;
		dirLightComponent -> setSpecularGenerated(true) ;
		dirLightEntity -> addComponent(dirLightComponent) ;
	}


	// Point light
    {
        Hope::Color lightColor(1.f, 1.f, 1.f) ;

    	Hope::Entity* parentLightEntity = new Hope::Entity(scene() -> root()) ;
        (parentLightEntity -> transform()).setTranslation(Mind::Vector3f(0.f, -25.f, 0.f)) ;

        {
            Hope::Entity* lightReprensentationEntity = new Hope::Entity(parentLightEntity) ;
            Hope::BlinnPhongMaterialComponent* cubeMaterial = new Hope::BlinnPhongMaterialComponent() ;
            cubeMaterial -> setAmbient(lightColor) ;
            lightReprensentationEntity -> addComponent(cubeMaterial) ;
        }

        Hope::Entity* pointLightEntity = new Hope::Entity(parentLightEntity) ;
        Hope::PointLightComponent* pointLightComponent = new Hope::PointLightComponent() ;
        pointLightComponent -> setColor(lightColor) ;
        pointLightComponent -> setPower(0.5f) ;
        pointLightComponent -> setSpecularGenerated(false) ;
        pointLightComponent -> setQuadraticAttenuation(0.f) ;
        pointLightComponent -> setLinearAttenuation(1.f) ;
        pointLightEntity -> addComponent(pointLightComponent) ;
    }

	// Point light
    {
        Hope::Color lightColor(0.3f, 0.7f, 1.f) ;

    	Hope::Entity* parentLightEntity = new Hope::Entity(scene() -> root()) ;
        (parentLightEntity -> transform()).setTranslation(Mind::Vector3f(0.f, 125.f, 150.f)) ;

        {
            Hope::Entity* lightReprensentationEntity = new Hope::Entity(parentLightEntity) ;
            Hope::BlinnPhongMaterialComponent* cubeMaterial = new Hope::BlinnPhongMaterialComponent() ;
            cubeMaterial -> setAmbient(lightColor) ;
            lightReprensentationEntity -> addComponent(cubeMaterial) ;
        }

        Hope::Entity* pointLightEntity = new Hope::Entity(parentLightEntity) ;
        Hope::PointLightComponent* pointLightComponent = new Hope::PointLightComponent() ;
        pointLightComponent -> setColor(lightColor) ;
        pointLightComponent -> setPower(5.f) ;
        pointLightComponent -> setSpecularGenerated(false) ;
        pointLightComponent -> setQuadraticAttenuation(0.f) ;
        pointLightComponent -> setLinearAttenuation(1.f) ;
        pointLightEntity -> addComponent(pointLightComponent) ;
    }



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
    const uint32_t ShadowResolution = 1024 ;
    float maxDistance = 75.f ;
    uint8_t amountCascades = 3 ;
    new Hope::DirectionalLightShadowNode(
        dirLightComponent,
        activeCameraNode,
        ShadowResolution,
        maxDistance,
        amountCascades,
        rootFG
    ) ;

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
        Mind::Dimension2Di(800, 480),
        true,
        capabilitiesNode
    ) ;
    Hope::ClearBuffersNode* clearBuffers = new Hope::ClearBuffersNode(Hope::GL::BufferClearer::Buffer::ColorDepthStencil, gBufferNode) ;
    new Hope::RenderPassSelectorNode(DeferredPassID, clearBuffers) ;

    // SSAO pass (not working yet).
    new Hope::SSAORenderNode(gBufferNode, activeCameraNode) ;

    // Deferred shading branch of the framegraph.
    Hope::GBufferQuadMaterialComponent* drMaterial = new Hope::GBufferQuadMaterialComponent(gBufferNode) ;
    new Hope::FinalStepRenderingNode(drMaterial, viewportNode) ;

    // Use the frame graph.
    scene() -> setFrameGraphRoot(rootFG) ;
}

void TestWindow::preRender() {
    float radius = 10.f ;
    float camX = sin(glfwGetTime() / 2.f) * radius ;
    float camZ = cos(glfwGetTime() / 2.f) * radius ;

    Mind::Vector3f camPos(camX, 3.f, camZ) ;
    (m_cameraEntity -> transform()).setTranslation(camPos) ;
}

void TestWindow::postRender() {
    // Nothing to do for now!
}
