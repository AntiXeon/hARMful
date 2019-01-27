#include <TestWindow.hpp>
#include <scene/framegraph/ActiveCamera.hpp>
#include <scene/framegraph/Viewport.hpp>

const std::string TestWindow::AppName = "Rendering test" ;

TestWindow::TestWindow()
    : Hope::GL::Window(800, 480, AppName) {
    // Create a camera in the scene graph.
    Hope::Entity* cameraEntity = new Hope::Entity(scene() -> root()) ;
    m_cameraComponent = new Hope::CameraComponent() ;
    m_cameraComponent -> setClearColor(Hope::Color(DefaultClearColor)) ;
    cameraEntity -> addComponent(m_cameraComponent) ;

    // Set up the frame graph.
    // Set the viewport.
    Hope::Viewport* viewportNode = new Hope::Viewport() ;
    viewportNode -> setPosition(Mind::Point2Df(0.25f, 0.25f)) ;
    viewportNode -> setDimension(Mind::Dimension2Df(0.5f, 0.5f)) ;

    // Set the camera in use.
    Hope::ActiveCamera* activeCameraNode = new Hope::ActiveCamera(viewportNode) ;
    activeCameraNode -> setCamera(m_cameraComponent) ;

    // Use the frame graph.
    scene() -> setFrameGraphRoot(viewportNode) ;
}

void TestWindow::preRender() {
    // Nothing to do for now!
}

void TestWindow::postRender() {
    // Nothing to do for now!
}
