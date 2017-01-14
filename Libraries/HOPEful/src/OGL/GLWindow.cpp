#include <HOPEStrings.hpp>
#include <OGL/GLWindow.hpp>
#include <OGL/GLOptions.hpp>
#include <utils/LogSystem.hpp>
#include <iostream>
#include <cstdlib>

namespace Hope {
    GLWindow::GLWindow(
        const int& width,
        const int& height,
        const std::string& title
    ) {
        createInternalWindow(width, height, title);
        useCurrentContext();
        initializeGLEW();
        setInputMode();
    }

    GLWindow::~GLWindow() {}

    void GLWindow::swapBuffers() {
        glfwSwapBuffers(m_window);
    }

    void GLWindow::createInternalWindow(
        const int& width,
        const int& height,
        const std::string& title
    ) {
        if (!glfwInit()) {
            std::shared_ptr<Doom::LogSystem> log = Doom::LogSystem::GetInstance() ;
            Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;
            log -> writeLine(level, Texts::Init_Bad_GLFW) ;
            exit(EXIT_FAILURE);
        }

        m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        if (m_window == nullptr) {
            std::shared_ptr<Doom::LogSystem> log = Doom::LogSystem::GetInstance() ;
            Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;
            log -> writeLine(level, Texts::Init_GL_Window) ;

            glfwTerminate();
            exit(EXIT_FAILURE);
        }
    }

    void GLWindow::useCurrentContext() {
        glfwMakeContextCurrent(m_window);
    }

    void GLWindow::initializeGLEW()    {
        // Required for the core profile set in the main window.
        glewExperimental = true;

        GLenum initEror = glewInit();

        if (initEror != GLEW_OK) {
            std::shared_ptr<Doom::LogSystem> log = Doom::LogSystem::GetInstance() ;
            Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;
            log -> writeLine(level, Texts::Init_Bad_GLEW, glewGetErrorString(initEror)) ;
            exit(EXIT_FAILURE);
        }
    }

    void GLWindow::setInputMode() {
        glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
    }
}
