#include <MainWindow.hpp>

const std::string MainWindow::AppName = "hARMful Demo v2.0-alpha" ;

MainWindow::MainWindow(
    const int width,
    const int height
) : Hope::GL::Window(width, height, AppName) {
    m_scenegraph = std::make_unique<SceneGraph>(root()) ;

    m_framegraph = std::make_unique<FrameGraph>(
        Mind::Dimension2Di(width, height),
        m_scenegraph.get()
    ) ;

    setFrameGraphRoot(m_framegraph -> root.get()) ;
    disableMouseCursor() ;
}

void MainWindow::preRender() {}

void MainWindow::postRender() {}

void MainWindow::keyboard(const float deltaTime) {
    if (glfwGetKey(handler(), GLFW_KEY_W) == GLFW_PRESS) {
        m_scenegraph -> camera.controller -> move(
            FlyCameraController::MoveDirection::Forward,
            deltaTime
        ) ;
    }

    if (glfwGetKey(handler(), GLFW_KEY_S) == GLFW_PRESS) {
        m_scenegraph -> camera.controller -> move(
            FlyCameraController::MoveDirection::Backward,
            deltaTime
        ) ;
    }

    if (glfwGetKey(handler(), GLFW_KEY_D) == GLFW_PRESS) {
        m_scenegraph -> camera.controller -> move(
            FlyCameraController::MoveDirection::Right,
            deltaTime
        ) ;
    }

    if (glfwGetKey(handler(), GLFW_KEY_A) == GLFW_PRESS) {
        m_scenegraph -> camera.controller -> move(
            FlyCameraController::MoveDirection::Left,
            deltaTime
        ) ;
    }

    if (glfwGetKey(handler(), GLFW_KEY_SPACE) == GLFW_PRESS) {
        m_scenegraph -> camera.controller -> move(
            FlyCameraController::MoveDirection::Up,
            deltaTime
        ) ;
    }

    if (glfwGetKey(handler(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        m_scenegraph -> camera.controller -> move(
            FlyCameraController::MoveDirection::Down,
            deltaTime
        ) ;
    }


    if (glfwGetKey(handler(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        m_scenegraph -> camera.controller -> setSpeed(FlyCameraController::RunSpeed) ;
    }
    else if (glfwGetKey(handler(), GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
        m_scenegraph -> camera.controller -> setSpeed(FlyCameraController::WalkSpeed) ;
    }

    if (glfwGetKey(handler(), GLFW_KEY_INSERT) == GLFW_PRESS) {
        showMouseCursor() ;
    }

    if (glfwGetKey(handler(), GLFW_KEY_HOME) == GLFW_PRESS) {
        disableMouseCursor() ;
    }

    if (glfwGetKey(handler(), GLFW_KEY_F) == GLFW_PRESS) {
        fullscreen() ;
    }

    if (glfwGetKey(handler(), GLFW_KEY_N) == GLFW_PRESS) {
        windowed() ;
    }

    if (glfwGetKey(handler(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(handler(), true) ;
    }
}

void MainWindow::mouse(const double x, const double y) {
    float halfWidth = width() / 2.f ;
    float halfHeight = height() / 2.f ;

    float adjustedX = static_cast<float>(x) - halfWidth ;
    float adjustedY = static_cast<float>(y) - halfHeight ;

    Mind::Vector2f cursorOffset(adjustedX, adjustedY) ;
    m_scenegraph -> camera.controller -> look(cursorOffset) ;
}
