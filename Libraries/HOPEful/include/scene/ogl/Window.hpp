#ifndef __HOPE__GL_WINDOW__
#define __HOPE__GL_WINDOW__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <scene/Scene.hpp>
#include <scene/ogl/visitors/OpenGLFrameGraphVisitor.hpp>
#include <memory>
#include <string>

namespace Hope { namespace GL {
    /**
     * A window containing an OpenGL application.
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
            Window(
                const int width,
                const int height,
                const std::string& title
            ) ;

            /**
             * Destruction of the GLWindow.
             */
            virtual ~Window() ;

            /**
             * Run the rendering/input acquisition loop of the window.
             */
            void run() ;

            /**
             * Get the root entity of the scene.
             */
            Entity* root() const {
                return m_scene -> root() ;
            }

            /**
             * Set the root of the framegraph.
             */
            void setFrameGraphRoot(FrameGraphNode* root) {
                m_scene -> setFrameGraphRoot(root) ;
            }

            /**
             * Switch to windowed window.
             */
            void windowed() const ;

            /**
             * Switch to fullscreen.
             */
            void fullscreen() const ;

            /**
             * Show the mouse cursor.
             */
            void showMouseCursor() const ;

            /**
             * Hide the mouse cursor.
             */
            void hideMouseCursor() const ;

            /**
             * Hide and lock the mouse cursor inside the window.
             */
            void disableMouseCursor() const ;

            // Remove copy/move operations.
            Window(const Window& copied) = delete ;
            Window(Window&& moved) = delete ;
            Window& operator=(const Window& copied) = delete ;
            Window& operator=(Window&& moved) = delete ;

        protected:
            /**
             * Allow the user to perform custom actions before rendering the
             * frame.
             */
            virtual void preRender() {}

            /**
             * Allow the user to perform custom actions after rendering the
             * frame.
             */
            virtual void postRender() {}

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
