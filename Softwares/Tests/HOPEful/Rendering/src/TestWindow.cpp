#include <TestWindow.hpp>
#include <scene/framegraph/ActiveCamera.hpp>
#include <scene/framegraph/Viewport.hpp>
#include <scene/components/mesh/MeshTreeComponent.hpp>
#include <scene/components/materials/PhongMaterialComponent.hpp>
#include <scene/components/lights/DirectionalLightComponent.hpp>
#include <scene/components/lights/PointLightComponent.hpp>

const std::string TestWindow::AppName = "Rendering test" ;

TestWindow::TestWindow()
    : Hope::GL::Window(800, 480, AppName) {
    /** SCENE GRAPH **/
    // Create a camera in the scene graph.
    m_cameraEntity = new Hope::Entity(scene() -> root()) ;
    m_cameraComponent = new Hope::CameraComponent() ;
    m_cameraComponent -> setClearColor(Hope::Color(DefaultClearColor)) ;
    m_cameraEntity -> addComponent(m_cameraComponent) ;
    m_cameraComponent -> lookAt(Mind::Vector3f(0.f, 0.f, 0.f)) ;

    Hope::Entity* meshTreeEntity = new Hope::Entity(scene() -> root()) ;
    Hope::MeshTreeComponent* meshTreeComponent = new Hope::MeshTreeComponent("../data/meshes/Mesh_Set.fbx") ;
    meshTreeEntity -> addComponent(meshTreeComponent) ;

/*
	// Test of matrices / parent relation.
    // Load a mesh.
    Hope::Entity* planeEntity = new Hope::Entity(scene() -> root()) ;
    Hope::MeshTreeComponent* meshPlaneComponent = new Hope::MeshTreeComponent("../data/meshes/Plane.fbx") ;
    planeEntity -> addComponent(meshPlaneComponent) ;
    (planeEntity -> transform()).setTranslation(Mind::Vector3f(0.f, -0.6f, 0.f)) ;
    (planeEntity -> transform()).setScale(0.5f) ;
    (planeEntity -> transform()).setRotation(Mind::Quaternion(0.f, 0.f, 25.f)) ;

    Hope::Entity* suzanneEntity = new Hope::Entity(planeEntity) ;
    Hope::MeshTreeComponent* meshSuzanneComponent = new Hope::MeshTreeComponent("../data/meshes/Suzanne.fbx") ;
    suzanneEntity -> addComponent(meshSuzanneComponent) ;
    (suzanneEntity -> transform()).setTranslation(Mind::Vector3f(0.f, 0.7f, 0.f)) ;
    (suzanneEntity -> transform()).setRotation(Mind::Quaternion(-30.f, 0.f, 0.f)) ;
*/


    // Create a directional light.
	{
		Hope::Entity* dirLightEntity = new Hope::Entity(scene() -> root()) ;
		Hope::DirectionalLightComponent* dirLightComponent = new Hope::DirectionalLightComponent() ;
		dirLightComponent -> setDirection(Mind::Vector3f(0.f, 1.f, -1.f)) ;
		dirLightComponent -> setColor(Hope::Color(0.9f, 0.85f, 0.7f, 1.f)) ;
		dirLightComponent -> setPower(1.f) ;
		dirLightComponent -> setSpecularGenerated(true) ;
		dirLightEntity -> addComponent(dirLightComponent) ;
	}

    {
        Hope::Entity* pointLightEntity = new Hope::Entity(scene() -> root()) ;
        (pointLightEntity -> transform()).setTranslation(Mind::Vector3f(0.f, 5.f, 5.f)) ;
        Hope::PointLightComponent* pointLightComponent = new Hope::PointLightComponent() ;
        pointLightComponent -> setColor(Hope::Color(0.7f, 0.8f, 1.f, 1.f)) ;
        pointLightComponent -> setPower(1.f) ;
        pointLightComponent -> setSpecularGenerated(false) ;
        pointLightComponent -> setQuadraticAttenuation(0.f) ;
        pointLightComponent -> setLinearAttenuation(1.f) ;
        pointLightEntity -> addComponent(pointLightComponent) ;
    }

    {
        Hope::Entity* pointLightEntity = new Hope::Entity(scene() -> root()) ;
        (pointLightEntity -> transform()).setTranslation(Mind::Vector3f(-5.f, 0.f, 0.f)) ;
        Hope::PointLightComponent* pointLightComponent = new Hope::PointLightComponent() ;
        pointLightComponent -> setColor(Hope::Color(1.f, 0.3f, 0.3f, 1.f)) ;
        pointLightComponent -> setPower(0.5f) ;
        pointLightComponent -> setSpecularGenerated(true) ;
        pointLightComponent -> setQuadraticAttenuation(1.f) ;
        pointLightComponent -> setLinearAttenuation(0.f) ;
        pointLightEntity -> addComponent(pointLightComponent) ;
    }

    {
        Hope::Entity* pointLightEntity = new Hope::Entity(scene() -> root()) ;
        (pointLightEntity -> transform()).setTranslation(Mind::Vector3f(5.f, -5.f, -5.f)) ;
        Hope::PointLightComponent* pointLightComponent = new Hope::PointLightComponent() ;
        pointLightComponent -> setColor(Hope::Color(0.1f, 0.5f, 1.f, 1.f)) ;
        pointLightComponent -> setPower(0.7f) ;
        pointLightComponent -> setSpecularGenerated(false) ;
        pointLightComponent -> setQuadraticAttenuation(1.f) ;
        pointLightComponent -> setLinearAttenuation(0.f) ;
        pointLightEntity -> addComponent(pointLightComponent) ;
    }

    /** FRAME GRAPH **/
    // Set the viewport.
    Hope::Viewport* viewportNode = new Hope::Viewport() ;
    viewportNode -> setPosition(Mind::Point2Df(0.f, 0.f)) ;
    viewportNode -> setDimension(Mind::Dimension2Df(1.f, 1.f)) ;

    // Set the camera in use.
    Hope::ActiveCamera* activeCameraNode = new Hope::ActiveCamera(viewportNode) ;
    activeCameraNode -> setCamera(m_cameraComponent) ;

    // Use the frame graph.
    scene() -> setFrameGraphRoot(viewportNode) ;
}

void TestWindow::preRender() {
    float radius = 3.f ;
    float camX = sin(glfwGetTime() / 2.f) * radius ;
    float camZ = cos(glfwGetTime() / 2.f) * radius ;

    Mind::Vector3f camPos(camX, 0.f, camZ) ;
    (m_cameraEntity -> transform()).setTranslation(camPos) ;
}

void TestWindow::postRender() {
    // Nothing to do for now!
}
