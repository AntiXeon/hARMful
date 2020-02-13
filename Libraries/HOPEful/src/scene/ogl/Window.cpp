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

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE) ;

    createInternalWindow(width, height, m_title) ;
    useCurrentContext() ;
    initializeGLEW() ;
    setInputMode() ;
    setCallbacks() ;
    setupDebugMessages() ;

    m_frameGraphVisitor = std::make_shared<OpenGLFrameGraphVisitor>() ;
    m_scene = std::make_unique<Scene>(m_frameGraphVisitor) ;
    m_frameGraphVisitor -> setWindowSize(Mind::Dimension2Df(width, height)) ;
}

Window::~Window() {
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

        m_frameGraphVisitor -> nextFrame() ;

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

void Window::setupDebugMessages() {
    // Set the message callback from OpenGL/GLFW to print logs while the app is
    // running.
    glEnable(GL_DEBUG_OUTPUT) ;
    const GLenum DebugSource = GL_DONT_CARE ;
    const GLenum DebugType = GL_DONT_CARE ;
    const GLenum DebugNotificationSeverity = GL_DEBUG_SEVERITY_NOTIFICATION ;
    const GLenum DebugLowSeverity = GL_DEBUG_SEVERITY_LOW ;
    const GLenum DebugMediumSeverity = GL_DEBUG_SEVERITY_MEDIUM ;
    const GLenum DebugHighSeverity = GL_DEBUG_SEVERITY_HIGH ;
    const GLsizei DebugCount = 0 ;
    const GLuint* DebugIDs = nullptr ;
    const GLboolean DebugEnabled = GL_TRUE ;
    glDebugMessageCallback(&Window::GLErrorCallback, nullptr) ;
    glDebugMessageControl(DebugSource, DebugType, DebugNotificationSeverity, DebugCount, DebugIDs, !DebugEnabled) ;
    glDebugMessageControl(DebugSource, DebugType, DebugLowSeverity, DebugCount, DebugIDs, !DebugEnabled) ;
    glDebugMessageControl(DebugSource, DebugType, DebugMediumSeverity, DebugCount, DebugIDs, !DebugEnabled) ;
    glDebugMessageControl(DebugSource, DebugType, DebugHighSeverity, DebugCount, DebugIDs, !DebugEnabled) ;

    glfwSetErrorCallback(&Window::GLFWErrorCallback) ;
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

void Window::GLErrorCallback(
    GLenum,
    GLenum,
    GLuint,
    GLenum severity,
    GLsizei,
    const GLchar* message,
    const void*
) {
    Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Debug ;

    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH :
            level = Doom::LogSystem::Gravity::Error ;
            break ;
        case GL_DEBUG_SEVERITY_MEDIUM :
            level = Doom::LogSystem::Gravity::Warning ;
            break ;
        case GL_DEBUG_SEVERITY_LOW :
            level = Doom::LogSystem::Gravity::Info ;
            break ;
        default:
            break;
    }

    auto logWeakPtr = Doom::LogSystem::GetInstance() ;
    auto logSharedPtr = logWeakPtr.lock() ;
    if (logSharedPtr) {
        logSharedPtr -> writeLine(
            level,
            message, "\n"
        ) ;
    }
}

void Window::resizedWindow(
    GLFWwindow* /*window*/,
    int width,
    int height
) {
    m_frameGraphVisitor -> setWindowSize(Mind::Dimension2Df(width, height)) ;
}
