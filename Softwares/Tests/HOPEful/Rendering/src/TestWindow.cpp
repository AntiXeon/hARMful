#include <TestWindow.hpp>
#include <scene/framegraph/ActiveCamera.hpp>

const std::string TestWindow::AppName = "Rendering test" ;

TestWindow::TestWindow()
    : Hope::GL::Window(800, 480, AppName) {
    // Create a camera in the scene graph.
    Hope::Entity* cameraEntity = new Hope::Entity(scene() -> root()) ;
    m_cameraComponent = new Hope::CameraComponent() ;
    cameraEntity -> addComponent(m_cameraComponent) ;

    // Set up the frame graph.
    Hope::ActiveCamera* activeCameraNode = new Hope::ActiveCamera() ;
    activeCameraNode -> setCamera(m_cameraComponent) ;

    // Use the frame graph.
    scene() -> setFrameGraphRoot(activeCameraNode) ;
}

void TestWindow::preRender() {
    m_frameCounter++ ;
    if (m_frameCounter % 2) {
        m_cameraComponent -> setClearColor(Hope::Color(ClearColorEven)) ;
    }
    else {
        m_cameraComponent -> setClearColor(Hope::Color(ClearColorOdd)) ;
    }
}

void TestWindow::postRender() {
    // Nothing to do for now!
}
