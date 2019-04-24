#ifndef __HOPE__GL_WINDOW__
#define __HOPE__GL_WINDOW__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <scene/Scene.hpp>
#include <string>

namespace Hope { namespace GL {
    /**
     * A window containing an OpenGL application.
     */
    class Window {
        private:
            /**
             * Title of the window / name of the application.
             */
            std::string m_title ;

            /**
             * Underlying window from GLFW library.
             */
            GLFWwindow* m_window = nullptr ;

            /**
             * Scene to be displayed in the window.
             */
            Scene* m_scene = nullptr ;

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
             * Get the scene that is rendered in the current window.
             */
            Scene* scene() const {
                return m_scene ;
            }


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

        // Callbacks
        private:
            /**
             * Print errors from GLFW.
             */
            static void GLFWErrorCallback(
                int error,
                const char* description
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
