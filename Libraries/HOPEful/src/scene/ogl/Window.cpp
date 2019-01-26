#include <HOPEStrings.hpp>
#include <scene/ogl/Window.hpp>
#include <scene/ogl/Options.hpp>
#include <utils/LogSystem.hpp>
#include <iostream>
#include <cstdlib>
#include <functional>

using namespace Hope ;
using namespace Hope::GL ;

Window::Window(
    const int width,
    const int height,
    const std::string& title
) {
    createInternalWindow(width, height, title) ;
    useCurrentContext() ;
    initializeGLEW() ;
    setInputMode() ;
    setCallbacks() ;
}

Window::~Window() {}

void Window::run() {
    while (!glfwWindowShouldClose(m_window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
        glfwSwapBuffers(m_window) ;
        glfwPollEvents() ;
    }

    glfwTerminate() ;
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

    // Use GLFW 2.1.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2) ;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1) ;

    m_window = glfwCreateWindow(
        width,
        height,
        title.c_str(),
        nullptr,
        nullptr
    ) ;

    if (m_window == nullptr) {
        glfwTerminate() ;
        exit(EXIT_FAILURE) ;
    }

    glfwSetWindowUserPointer(m_window, this) ;
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
    glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE) ;
}

void Window::setCallbacks() {
    // Set the error callback to print errors while GLFW is running.
    glfwSetErrorCallback(&Window::GLFWErrorCallback) ;

    // [!] Keep this code in case it can be re/used for /another callback! [!]
    // // Callback for window resizing.
    // auto resizeCallbackFunc = [](GLFWwindow* window, int width, int height) {
    //     Window* that = static_cast<Window*>(glfwGetWindowUserPointer(window)) ;
    //     that -> resizedWindow(window, width, height) ;
    // } ;
    // glfwSetWindowSizeCallback(m_window, resizeCallbackFunc) ;
}

void Window::GLFWErrorCallback(
    int /*error*/,
    const char* description
) {
    auto logWeakPtr = Doom::LogSystem::GetInstance() ;
    Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Error ;

    auto logSharedPtr = logWeakPtr.lock() ;
    if (logSharedPtr) {
        logSharedPtr -> writeLine(level, description) ;
    }
}

void Window::resizedWindow(
    GLFWwindow* /*window*/,
    int /*width*/,
    int /*height*/
) {
    // May be used one day?
}
