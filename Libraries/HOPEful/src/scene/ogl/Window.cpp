#include <HOPEStrings.hpp>
#include <scene/ogl/Window.hpp>
#include <scene/ogl/Options.hpp>
#include <utils/LogSystem.hpp>
#include <FastMath.hpp>
#include <cstdlib>
#include <functional>

using namespace Hope ;
using namespace Hope::GL ;

Window::Window(
    const int width,
    const int height,
    const std::string& title
) : m_title(title) {
    Doom::LogSystem::Initialize(m_title, Doom::LogSystem::Gravity::Info) ;

    // Set the error callback to print errors while GLFW is running.
    glfwSetErrorCallback(&Window::GLFWErrorCallback) ;

    createInternalWindow(width, height, m_title) ;
    useCurrentContext() ;
    initializeGLEW() ;
    setInputMode() ;
    setCallbacks() ;

    m_scene = new Scene() ;
    m_scene -> setWindowSize(Mind::Dimension2Df(width, height)) ;
}

Window::~Window() {
    delete m_scene ;
    glfwDestroyWindow(m_window) ;
    glfwTerminate() ;
}

void Window::run() {
    m_scene -> lockEntities(true) ;

    while (!glfwWindowShouldClose(m_window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
        preRender() ;
        m_scene -> render() ;
        postRender() ;
        glfwPollEvents() ;
        glfwSwapBuffers(m_window) ;
    }

    m_scene -> lockEntities(false) ;
}

void Window::windowed() const {
    int xpos, ypos ;
    glfwGetWindowPos(m_window, &xpos, &ypos) ;

    int width, height ;
    glfwGetWindowSize(m_window, &width, &height) ;

    glfwSetWindowMonitor(m_window, nullptr, xpos, ypos, width, height, 0) ;
}

void Window::fullscreen() const {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor() ;
    const GLFWvidmode* mode = glfwGetVideoMode(monitor) ;
    glfwSetWindowMonitor(m_window, monitor, 0, 0, mode -> width, mode -> height, mode -> refreshRate) ;
}

void Window::showMouseCursor() const {
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL) ;
}

void Window::hideMouseCursor() const {
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN) ;
}

void Window::disableMouseCursor() const {
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED) ;
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

        exit(EXIT_FAILURE) ;
    }

    setGraphicsAPIVersion() ;

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
    glfwMakeContextCurrent(m_window) ;
}

void Window::initializeGLEW()    {
    auto logWeakPtr = Doom::LogSystem::GetInstance() ;
    auto logSharedPtr = logWeakPtr.lock() ;

    // Required for the core profile set in the main window.
    glewExperimental = true ;

    GLenum initEror = glewInit() ;

    if (initEror != GLEW_OK) {
        if (logSharedPtr) {
            Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;

            logSharedPtr -> writeLine(
                level,
                Texts::Init_Bad_GLEW,
                glewGetErrorString(initEror)
            ) ;
        }

        exit(EXIT_FAILURE) ;
    }

    glEnable(GL_DEPTH_TEST) ;
    glDepthFunc(GL_LESS) ;

    // Get version info.
    const GLubyte* renderer = glGetString(GL_RENDERER) ;
    const GLubyte* version = glGetString(GL_VERSION) ;
    if (logSharedPtr) {
        Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Info ;

        logSharedPtr -> writeLine(
            level,
            Texts::Init_GL_Renderer,
            renderer
        ) ;

        logSharedPtr -> writeLine(
            level,
            Texts::Init_GL_Vendor,
            version
        ) ;
    }
}

void Window::setInputMode() {
    glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE) ;
}

void Window::setCallbacks() {
    // Callback for window resizing.
    auto resizeCallbackFunc = [](GLFWwindow* window, int width, int height) {
        Window* that = static_cast<Window*>(glfwGetWindowUserPointer(window)) ;
        that -> resizedWindow(window, width, height) ;
    } ;
    glfwSetWindowSizeCallback(m_window, resizeCallbackFunc) ;
}

void Window::setGraphicsAPIVersion() {
    Options::SetGLVersion(OpenGLMajorVersion, OpenGLMinorVersion) ;
    Options::SetSamplingFactor(Options::Sampling::X4) ;
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
    int width,
    int height
) {
    m_scene -> setWindowSize(Mind::Dimension2Df(width, height)) ;
}
