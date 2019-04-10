#include <TestWindow.hpp>
#include <scene/framegraph/ActiveCamera.hpp>
#include <scene/framegraph/Viewport.hpp>
#include <scene/components/MeshComponent.hpp>
#include <scene/components/materials/PhongMaterialComponent.hpp>
#include <scene/components/lights/DirectionalLightComponent.hpp>
#include <scene/components/test/TriangleTestComponent.hpp>

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

    // Create a directional light.
    Hope::Entity* lightEntity = new Hope::Entity(scene() -> root()) ;
    Hope::DirectionalLightComponent* dirLightComponent = new Hope::DirectionalLightComponent() ;
    lightEntity -> addComponent(dirLightComponent) ;

    // Load a mesh.
    Hope::Entity* cubeEntity = new Hope::Entity(scene() -> root()) ;
    Hope::MeshComponent* meshComponent = new Hope::MeshComponent("../data/meshes/suzanne.dae") ;
    // Hope::TriangleTestComponent* meshComponent = new Hope::TriangleTestComponent() ;
    cubeEntity -> addComponent(meshComponent) ;

    // Add a material.
    Hope::PhongMaterialComponent* material = new Hope::PhongMaterialComponent() ;
    // Hope::Color ambientColor(1.f, 0.f, 0.f, 1.f) ;
    // material -> setAmbient(ambientColor) ;
    cubeEntity -> addComponent(material) ;


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
    float camX = sin(glfwGetTime()) * radius ;
    float camY = cos(glfwGetTime()) * radius ;

    Mind::Vector3f camPos(camX, camY, 0.f) ;
    (m_cameraEntity -> transform()).setTranslation(camPos) ;
}

void TestWindow::postRender() {
    // Nothing to do for now!
}
