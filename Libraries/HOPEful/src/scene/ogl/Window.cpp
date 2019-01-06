#include <HOPEStrings.hpp>
#include <scene/ogl/Window.hpp>
#include <scene/ogl/Options.hpp>
#include <utils/LogSystem.hpp>
#include <iostream>
#include <cstdlib>

using namespace Hope ;
using namespace Hope::GL ;

Window::Window(
    const int width,
    const int height,
    const std::string& title
) {
    createInternalWindow(width, height, title);
    useCurrentContext();
    initializeGLEW();
    setInputMode();
}

Window::~Window() {}

void Window::swapBuffers() {
    glfwSwapBuffers(m_window);
}

Scene& Window::scene() {
    return m_scene ;
}

void Window::createInternalWindow(
    const int width,
    const int height,
    const std::string& title
) {
    if (!glfwInit()) {
        auto logWeakPtr = Doom::LogSystem::GetInstance() ;
        Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;

        auto logSharedPtr = logWeakPtr.lock() ;
        if (logSharedPtr) {
            logSharedPtr -> writeLine(level, Texts::Init_Bad_GLFW) ;
        }

        exit(EXIT_FAILURE);
    }

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (m_window == nullptr) {
        auto logWeakPtr = Doom::LogSystem::GetInstance() ;
        Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;

        auto logSharedPtr = logWeakPtr.lock() ;
        if (logSharedPtr) {
            logSharedPtr -> writeLine(level, Texts::Init_GL_Window) ;
        }

        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

void Window::useCurrentContext() {
    glfwMakeContextCurrent(m_window);
}

void Window::initializeGLEW()    {
    // Required for the core profile set in the main window.
    glewExperimental = true;

    GLenum initEror = glewInit();

    if (initEror != GLEW_OK) {
        auto logWeakPtr = Doom::LogSystem::GetInstance() ;
        Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;

        auto logSharedPtr = logWeakPtr.lock() ;
        if (logSharedPtr) {
            logSharedPtr -> writeLine(
                level,
                Texts::Init_Bad_GLEW,
                glewGetErrorString(initEror)
            ) ;
        }

        exit(EXIT_FAILURE);
    }
}

void Window::setInputMode() {
    glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
}
