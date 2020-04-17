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
        struct MouseCursor {
            double x = 0.f;
            double y = 0.f;
        };

        double m_lastTime = 0.f;

        float m_cameraYaw = 0.f;
        float m_cameraPitch = 0.f;
        float m_mouseSensibility = 0.05f;

        Mind::Vector3f m_cameraDirection;
        Mind::Vector3f m_cameraPosition;
        MouseCursor m_oldCursorPosition;


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
        Hope::Transform* m_cameraTransform = nullptr ;

        /**
         * Cube entity.
         */
        Hope::Transform* m_cubeTransform = nullptr ;

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

        /**
         * Allow the user to set the keyboard inputs.
         */
        void keyboard(
            const int key,
            const int scancode,
            const int action,
            const int mods
        ) override ;

        /**
         * Allow the user to use mouse movements.
         */
        void mouse(
            const double x,
            const double y
        ) override ;
} ;

#endif
