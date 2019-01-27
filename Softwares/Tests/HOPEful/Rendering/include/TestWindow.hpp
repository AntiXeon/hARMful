#ifndef __HOPE__TEST_WINDOW__
#define __HOPE__TEST_WINDOW__

#include <scene/ogl/Window.hpp>
#include <scene/components/CameraComponent.hpp>

/**
 * Window for testing the framework.
 */
class TestWindow final : public Hope::GL::Window {
    private:
        /**
         * Application name.
         */
        static const std::string AppName ;

        /**
         * Default color to clear screen at each frame.
         */
        static const int DefaultClearColor = 0x000000FF ;

        /**
         * A frame counter.
         */
        int m_frameCounter = 0 ;

        /**
         * Camera component.
         */
        Hope::CameraComponent* m_cameraComponent ;

    public:
        /**
         * Create a TestWindow instance.
         */
        TestWindow() ;

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
} ;

#endif
