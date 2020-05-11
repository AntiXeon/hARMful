#ifndef __HOPE__GL_WINDOW__
#define __HOPE__GL_WINDOW__

#include <HopeAPI.hpp>
#include <utils/Platform.hpp>

#include <GLFW/glfw3.h>
#include <scene/Scene.hpp>
#include <scene/ogl/visitors/OpenGLFrameGraphVisitor.hpp>
#include <memory>
#include <string>

namespace Hope { namespace GL {
    /**
     * A standalone window containing an OpenGL application. Based on GLFW.
     * You can implement your own window class for any other use.
     */
    class Window {
        private:
            /**
             * Major version of the OpenGL API to use.
             */
            static const int OpenGLMajorVersion = 4 ;

            /**
             * Minor version of the OpenGL API to use.
             */
            static const int OpenGLMinorVersion = 5 ;

            /**
             * Title of the window / name of the application.
             */
            std::string m_title ;

            /**
             * Underlying window from GLFW library.
             */
            GLFWwindow* m_window = nullptr ;

            /**
             * Frame graph visitor for rendering the scene.
             */
            std::shared_ptr<OpenGLFrameGraphVisitor> m_frameGraphVisitor = nullptr ;

            /**
             * Scene to be displayed in the window.
             */
            std::unique_ptr<Scene> m_scene = nullptr ;

        public:
            /**
             * Create a new Window.
             * @param   width   Width of the window.
             * @param   height  Height of the window.
             * @param   title   Title of the window.
             */
            exported Window(
                const int width,
                const int height,
                const std::string& title
            ) ;

            /**
             * Destruction of the GLWindow.
             */
            exported virtual ~Window() ;

            /**
             * Run the rendering/input acquisition loop of the window.
             */
            exported void run() ;

            /**
             * Get the root transform of the scene.
             */
            exported Transform* root() const {
                return m_scene -> root() ;
            }

            /**
             * Get the width of the window.
             */
            exported int width() const {
                int width;
                glfwGetWindowSize(m_window, &width, nullptr);
                return width;
            }

            /**
             * Get the height of the window.
             */
            exported int height() const {
                int height;
                glfwGetWindowSize(m_window, nullptr, &height);
                return height;
            }

            /**
             * Set the root of the framegraph.
             */
            exported void setFrameGraphRoot(FrameGraphNode* root) {
                m_scene -> setFrameGraphRoot(root) ;
            }

            /**
             * Switch to windowed window.
             */
            exported void windowed() const ;

            /**
             * Switch to fullscreen.
             */
            exported void fullscreen() const ;

            /**
             * Show the mouse cursor.
             */
            exported void showMouseCursor() const ;

            /**
             * Hide the mouse cursor.
             */
            exported void hideMouseCursor() const ;

            /**
             * Hide and lock the mouse cursor inside the window.
             */
            exported void disableMouseCursor() const ;

            // Remove copy/move operations.
            Window(const Window& copied) = delete ;
            Window(Window&& moved) = delete ;
            Window& operator=(const Window& copied) = delete ;
            Window& operator=(Window&& moved) = delete ;

        protected:
            /**
             * Get the underlying low-level window handler.
             */
            exported GLFWwindow* handler() const {
                return m_window;
            }

            /**
             * Allow the user to perform custom actions before rendering the
             * frame.
             */
            exported virtual void preRender() {}

            /**
             * Allow the user to perform custom actions after rendering the
             * frame.
             */
            exported virtual void postRender() {}

            /**
             * Allow the user to set the keyboard inputs.
             */
            exported virtual void keyboard(
                [[maybe_unused]] const int key,
                [[maybe_unused]] const int scancode,
                [[maybe_unused]] const int action,
                [[maybe_unused]] const int mods
            ) {}

            /**
             * Allow the user to use mouse movements.
             */
            exported virtual void mouse(
                [[maybe_unused]] const double x,
                [[maybe_unused]] const double y
            ) {}

        private:
            /**
             * Create the internal window.
             * @param   width   Width of the window.
             * @param   height  Height of the window.
             * @param   title   Title of the window.
             */
            void createInternalWindow(
                const int width,
                const int height,
                const std::string& title
            ) ;

            /**
             * Use the context of the window as the current OpenGL
             * context.
             */
            void useCurrentContext() ;

            /**
             * Initialize GLEW to support OpenGL3.
             */
            void initializeGLEW() ;

            /**
             * Listen for inputs from the user.
             */
            void setInputMode() ;

            /**
             * Set up the callback functions.
             */
            void setCallbacks() ;

            /**
             * Set the version of the graphics API.
             */
            void setGraphicsAPIVersion() ;

        private:
            /**
             * Set up debug messages from OpenGL and GLFW.
             */
            void setupDebugMessages() ;

            // Callbacks
            /**
             * Print errors from GLFW.
             */
            static void GLFWErrorCallback(
                int error,
                const char* description
            ) ;

            /**
             * Print errors and other messages from OpenGL.
             */
            static void GLErrorCallback(
                GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar* message,
                const void* parameters
            ) ;

            /**
             * Callback when the window is resized.
             */
            void resizedWindow(
                GLFWwindow* window,
                int width,
                int height
            ) ;
    } ;
}}

#endif
