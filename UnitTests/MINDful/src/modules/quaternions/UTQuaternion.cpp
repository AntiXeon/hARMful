#include <modules/quaternions/UTQuaternion.hpp>
#include <geometry/quaternions/Quaternion.hpp>
#include <Math.hpp>
#include <string>
#include <iostream>

#include <utils/Chrono.hpp>

using namespace Mind ;

namespace UTMind {
    UTQuaternion::UTQuaternion() {}

    UTQuaternion::~UTQuaternion() {}

    void UTQuaternion::runTests() {
        allocation() ;
        utilities() ;
        operators() ;
    }

    void UTQuaternion::allocation() {
        // Default.
        {
            Quaternion q1 ;
            Scalar roll, pitch, yaw ;
            q1.to(roll, pitch, yaw) ;
            check(roll == 0.f) ;
            check(pitch == 0.f) ;
            check(yaw == 0.f) ;
        }

        // Values.
        {
            Scalar x = 0.478f ;
            Scalar y = -0.3784f ;
            Scalar z = 0.92f ;
            Scalar w = -0.004f ;
            Quaternion q2(x, y, z, w) ;
            check(q2[Quaternion::Axis::X] == x) ;
            check(q2[Quaternion::Axis::Y] == y) ;
            check(q2[Quaternion::Axis::Z] == z) ;
            check(q2[Quaternion::Axis::W] == w) ;
        }

        // Rotation matrix.
        {
            Matrix3x3f matrix ;
            matrix.at(0,0, +0.8f) ;
            matrix.at(0,1, +0.1f) ;
            matrix.at(0,2, -0.5f) ;
            matrix.at(1,0, +0.7f) ;
            matrix.at(1,1, -1.0f) ;
            matrix.at(1,2, +0.6f) ;
            matrix.at(2,0, +0.0f) ;
            matrix.at(2,1, -0.1f) ;
            matrix.at(2,2, +0.7f) ;

            /*
            Octave result:
            q2 = 0.6124 - 0.2858i - 0.2041j + 0.2449k
            */
            Scalar expectedX = -0.285773803324704 ;
            Scalar expectedY = -0.204124145231932 ;
            Scalar expectedZ =  0.244948974278318 ;
            Scalar expectedW =  0.612372435695794 ;

            Quaternion q3(matrix) ;
            check(compare(q3[Quaternion::Axis::X], expectedX)) ;
            check(compare(q3[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q3[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q3[Quaternion::Axis::W], expectedW)) ;

            Quaternion q4(q3) ;
            check(compare(q4[Quaternion::Axis::X], expectedX)) ;
            check(compare(q4[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q4[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q4[Quaternion::Axis::W], expectedW)) ;
        }

        // Axis and rotation.
        {
            Vector3f axis(0.f, 0.5f, 0.78f) ;
            axis.normalize() ;
            Scalar angle = Math::Pi / 4.f ;

            /*
            Octave result:
            q5 = 0.9239 + 0i + 0.2065j + 0.3222k
            */
            Scalar expectedX =  0.f ;
            Scalar expectedY =  0.206521281112347 ;
            Scalar expectedZ =  0.322173198535262 ;
            Scalar expectedW =  0.923879532511287 ;

            Quaternion q5(axis, angle) ;
            std::cout << q5 << std::endl ;
            check(compare(q5[Quaternion::Axis::X], expectedX)) ;
            check(compare(q5[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q5[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q5[Quaternion::Axis::W], expectedW)) ;
        }
    }

    void UTQuaternion::utilities() {
        // Dot product.
        {
            Quaternion q1(-0.47f, 0.1474f, 0.657f, 0.24f) ;
            Quaternion q2(-0.24f, 0.3f, -0.176f, -0.709f) ;
            Quaternion qr = q1 * q2 ;

            /*
            Octave result:
            >> q1 .* q2
            ans = -0.2115 + 0.05259i - 0.2729j - 0.6137k
            */
            Scalar expectedX =  0.0525876f ;
            Scalar expectedY = -0.2729066 ;
            Scalar expectedZ = -0.613677 ;
            Scalar expectedW = -0.211548 ;

            check(compare(qr[Quaternion::Axis::X], expectedX)) ;
            check(compare(qr[Quaternion::Axis::Y], expectedY)) ;
            check(compare(qr[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(qr[Quaternion::Axis::W], expectedW)) ;
        }
    }

    void UTQuaternion::operators() {}
}
