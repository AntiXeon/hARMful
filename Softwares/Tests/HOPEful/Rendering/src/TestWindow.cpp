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

    m_cameraComponent -> setUpVector(Mind::Vector3f(0.f, 0.f, 1.f)) ;
    m_cameraComponent -> lookAt(Mind::Vector3f(0.f, 0.f, 0.f)) ;

    // Load a mesh.
    Hope::Entity* cubeEntity = new Hope::Entity(scene() -> root()) ;
    Hope::MeshTreeComponent* meshComponent = new Hope::MeshTreeComponent("../data/meshes/mesh_set.fbx") ;
    cubeEntity -> addComponent(meshComponent) ;

    // // Create a directional light.
    // Hope::Entity* dirLightEntity = new Hope::Entity(scene() -> root()) ;
    // Hope::DirectionalLightComponent* dirLightComponent = new Hope::DirectionalLightComponent() ;
    // dirLightComponent -> setDirection(Mind::Vector3f(0.5f, -1.f, -0.5f)) ;
    // dirLightComponent -> setColor(Hope::Color(0.7f, 0.7f, 0.7f, 1.f)) ;
    // dirLightComponent -> setPower(1.f) ;
    // dirLightComponent -> setSpecularGenerated(true) ;
    // dirLightEntity -> addComponent(dirLightComponent) ;
    // (scene() -> cache()).registerLight(dirLightComponent) ;

    {
        Hope::Entity* pointLightEntity = new Hope::Entity(scene() -> root()) ;
        (pointLightEntity -> transform()).setTranslation(Mind::Vector3f(1.f, 0.f, 0.f)) ;
        Hope::PointLightComponent* pointLightComponent = new Hope::PointLightComponent() ;
        pointLightComponent -> setColor(Hope::Color(0.7f, 0.8f, 1.f, 1.f)) ;
        pointLightComponent -> setPower(1.f) ;
        pointLightComponent -> setSpecularGenerated(true) ;
        pointLightComponent -> setQuadraticAttenuation(0.f) ;
        pointLightComponent -> setLinearAttenuation(1.f) ;
        pointLightEntity -> addComponent(pointLightComponent) ;
        (scene() -> cache()) -> registerLight(pointLightComponent) ;
    }

    {
        Hope::Entity* pointLightEntity = new Hope::Entity(scene() -> root()) ;
        (pointLightEntity -> transform()).setTranslation(Mind::Vector3f(0.f, 1.f, 0.f)) ;
        Hope::PointLightComponent* pointLightComponent = new Hope::PointLightComponent() ;
        pointLightComponent -> setColor(Hope::Color(1.f, 0.3f, 0.3f, 1.f)) ;
        pointLightComponent -> setPower(0.5f) ;
        pointLightComponent -> setSpecularGenerated(true) ;
        pointLightComponent -> setQuadraticAttenuation(1.f) ;
        pointLightComponent -> setLinearAttenuation(0.f) ;
        pointLightEntity -> addComponent(pointLightComponent) ;
        (scene() -> cache()) -> registerLight(pointLightComponent) ;
    }

    {
        Hope::Entity* pointLightEntity = new Hope::Entity(scene() -> root()) ;
        (pointLightEntity -> transform()).setTranslation(Mind::Vector3f(0.f, 0.f, 1.f)) ;
        Hope::PointLightComponent* pointLightComponent = new Hope::PointLightComponent() ;
        pointLightComponent -> setColor(Hope::Color(0.1f, 0.5f, 1.f, 1.f)) ;
        pointLightComponent -> setPower(0.7f) ;
        pointLightComponent -> setSpecularGenerated(false) ;
        pointLightComponent -> setQuadraticAttenuation(1.f) ;
        pointLightComponent -> setLinearAttenuation(0.f) ;
        pointLightEntity -> addComponent(pointLightComponent) ;
        (scene() -> cache()) -> registerLight(pointLightComponent) ;
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
    float camY = cos(glfwGetTime() / 2.f) * radius ;

    Mind::Vector3f camPos(camX, camY, 0.f) ;
    (m_cameraEntity -> transform()).setTranslation(camPos) ;
}

void TestWindow::postRender() {
    // Nothing to do for now!
}
