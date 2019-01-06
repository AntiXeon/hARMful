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
             * Underlying window from GLFW library.
             */
            GLFWwindow* m_window;

            /**
             * Scene to be displayed in the window.
             */
            Scene m_scene ;

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
            );

            /**
             * Destruction of the GLWindow.
             */
            virtual ~Window();

            /**
             * Swap buffers for rendering.
             */
            void swapBuffers();

            /**
             * Get the scene that is rendered in the current window.
             */
            Scene& scene() ;


            // Remove copy/move operations.
            Window(const Window& copied) = delete ;
            Window(Window&& moved) = delete ;
            Window& operator=(const Window& copied) = delete ;
            Window& operator=(Window&& moved) = delete ;

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
            );

            /**
             * Use the context of the window as the current OpenGL
             * context.
             */
            void useCurrentContext();

            /**
             * Initialize GLEW to support OpenGL3.
             */
            void initializeGLEW();

            /**
             * Listen for inputs from the user.
             */
            void setInputMode();
    };
}}

#endif
