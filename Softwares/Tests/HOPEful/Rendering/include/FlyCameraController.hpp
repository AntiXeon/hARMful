#ifndef __HOPE__FLY_CAMERA_CONTROLLER__
#define __HOPE__FLY_CAMERA_CONTROLLER__

#include <scene/Transform.hpp>
#include <scene/components/cameras/CameraComponent.hpp>
#include <geometry/points/Point3Df.hpp>
#include <vector>

/**
 * Controller of a camera as if it is flying in the world.
 * No gravity is applied to it nor any other physics constraint.
 */
class FlyCameraController final {
    public:
        static const float WalkSpeed ;
        static const float RunSpeed ;

        /**
         * Move direction of the camera.
         */
        enum class MoveDirection {
            Forward,
            Backward,
            Right,
            Left,
            Up,
            Down
        } ;

    private:
        /**
         * Camera to apply controller to.
         */
        Hope::CameraComponent* m_camera = nullptr ;

        /**
         * Transform of the camera.
         */
        std::reference_wrapper<Hope::Transform> m_cameraTransform ;

        /**
         * Camera speed.
         */
        float m_speed = 1.f ;

        /**
         * Set the mouse sensibility for changing look direction of the camera.
         */
        float m_mouseSensibility = 0.1f ;

        /**
         * View Euler angle of the camera.
         */
        Mind::Vector2f m_cameraViewAngles ;

        /**
         * Previous mouse cursor offset from window center, used for computing
         * the look direction of the camera when moving the mouse device.
         */
        Mind::Vector2f m_oldCursorOffset ;

    public:
        /**
         * Create a new FlyCameraController instance.
         * @param   camera  Camera to which the controller is applied.
         */
        FlyCameraController(Hope::CameraComponent* camera) ;

        /**
         * Set the speed value.
         * @param speed Speed of the camera when moving.
         */
        void setSpeed(const float speed) ;

        /**
         * Move the camera forward.
         * @param moveDirection   Direction to move camera towards.
         * @param deltaTime       Elapsed time since last frame to compute the
         *                        displacement distance of the camera.
         */
        void move(
            const MoveDirection moveDirection,
            const float deltaTime
        ) ;

        /**
         * Set the look direction of the camera.
         * @param cursorOffset  Offset of the cursor from the center of the
         *                      window.
         */
        void look(const Mind::Vector2f& cursorOffset) ;
} ;

#endif
