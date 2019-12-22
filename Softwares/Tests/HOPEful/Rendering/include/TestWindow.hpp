#ifndef __HOPE__TEST_WINDOW__
#define __HOPE__TEST_WINDOW__

#include <scene/ogl/Window.hpp>
#include <scene/components/cameras/PerspectiveCameraComponent.hpp>
#include <scene/components/cameras/OrthographicCameraComponent.hpp>

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
        static const int DefaultClearColor = 0x050505FF ;

        /**
         * A frame counter.
         */
        int m_frameCounter = 0 ;

        /**
         * Camera entity.
         */
        Hope::Entity* m_cameraEntity = nullptr ;

        /**
         * Camera component.
         */
        Hope::PerspectiveCameraComponent* m_cameraComponent = nullptr ;
        //Hope::OrthographicCameraComponent* m_cameraComponent = nullptr ;

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
