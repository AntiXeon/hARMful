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

        static const int ClearColorOdd = 0x123456FF ;
        static const int ClearColorEven = 0x654321FF ;

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
