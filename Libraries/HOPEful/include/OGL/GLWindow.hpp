#ifndef __HOPE__WINDOW__
#define __HOPE__WINDOW__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

namespace Hope {
    /**
     * @brief   A window containing an OpenGL application.
     */
    class GLWindow {
        private:
            /**
             * @brief   Underlying window from GLFW library.
             */
            GLFWwindow* m_window;

        public:
            /**
             * @brief   Create a new GLWindow.
             * @param   width   Width of the window.
             * @param   height  Height of the window.
             * @param   title   Title of the window.
             */
            GLWindow(const int& width,
                     const int& height,
                     const std::string& title);

            /**
             * @brief   Destruction of the GLWindow.
             */
            virtual ~GLWindow();

            /**
             * @brief Swap buffers for rendering.
             */
            void swapBuffers();

        private:
            /**
             * Create the internal window.
             * @param   width   Width of the window.
             * @param   height  Height of the window.
             * @param   title   Title of the window.
             */
            void createInternalWindow(const int& width,
                                      const int& height,
                                      const std::string& title);

            /**
             * @brief   Use the context of the window as the current OpenGL
             *          context.
             */
            void useCurrentContext();

            /**
             * Initialize GLEW to support OpenGL3.
             */
            void initializeGLEW();

            /**
             * @brief   Listen for inputs from the user.
             */
            void setInputMode();
    };
}

#endif // ifndef __HOPE__WINDOW__
