#include <iostream>
#include <scene/ogl/Window.hpp>
#include <scene/components/CameraComponent.hpp>
#include <scene/framegraph/ActiveCamera.hpp>

#define ApplicationName "Rendering test"

int main(int, char**) {
    Hope::GL::Window mainWindow(800, 480, ApplicationName) ;

    Hope::Scene* scene = mainWindow.scene() ;
    Hope::Entity* rootEntity = scene -> root() ;

    // Create a camera in the scene graph.
    Hope::Entity* cameraEntity = new Hope::Entity(rootEntity) ;
    Hope::CameraComponent* cameraComponent = new Hope::CameraComponent() ;
    cameraEntity -> addComponent(cameraComponent) ;
    const int ClearColor = 0xFF00FFFF ;
    cameraComponent -> setClearColor(Hope::Color(ClearColor)) ;

    // Set up the frame graph.
    Hope::ActiveCamera* activeCameraNode = new Hope::ActiveCamera() ;
    activeCameraNode -> setCamera(cameraComponent) ;

    // Use the frame graph.
    scene -> setFrameGraphRoot(activeCameraNode) ;

    mainWindow.run() ;

    return 0 ;
}
