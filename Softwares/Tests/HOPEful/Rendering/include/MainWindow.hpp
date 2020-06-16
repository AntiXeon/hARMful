#ifndef __DEMOHOPE__MAIN_WINDOW__
#define __DEMOHOPE__MAIN_WINDOW__

#include <scene/ogl/Window.hpp>
#include <memory>

#include "SceneGraph.hpp"
#include "FrameGraph.hpp"

/**
 * Main window of the app.
 */
class MainWindow final : public Hope::GL::Window {
    private:
        /**
         * Application name.
         */
        static const std::string AppName ;

        /**
         * Graph of the scene that is displayed in this window.
         */
        std::unique_ptr<SceneGraph> m_scenegraph = nullptr ;

        /**
         * Graph to describe how the scene is displayed in this window.
         */
        std::unique_ptr<FrameGraph> m_framegraph = nullptr ;

        /**
         * Time at which the last frame has been recorded.
         */
        float m_lastFrameTime = 0.f ;

    public:
        /**
         * Create a new MainWindow.
         */
        MainWindow(
            const int width,
            const int height
        ) ;

    protected:
        /**
         * Allow the user to perform custom actions before rendering the
         * frame.
         */
        void preRender() override ;

        /**
         * Allow the user to perform custom actions after rendering the
         * frame.
         */
        void postRender() override ;

        /**
         * Allow the user to set the keyboard inputs.
         */
        void keyboard(const float deltaTime) override ;

        /**
         * Allow the user to use mouse movements.
         */
        void mouse(const double x, const double y) override ;
} ;

#endif
