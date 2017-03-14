#include <modules/quaternions/UTQuaternion.hpp>
#include <geometry/quaternions/Quaternion.hpp>
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
        {
            Quaternion q1 ;
            Scalar roll, pitch, yaw ;
            q1.to(roll, pitch, yaw) ;
            check(roll == 0.f) ;
            check(pitch == 0.f) ;
            check(yaw == 0.f) ;
        }

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

            Quaternion q2(matrix) ;
            check(compare(q2[Quaternion::Axis::X], expectedX)) ;
            check(compare(q2[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q2[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q2[Quaternion::Axis::W], expectedW)) ;

            Quaternion q3(q2) ;
            check(compare(q3[Quaternion::Axis::X], expectedX)) ;
            check(compare(q3[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q3[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q3[Quaternion::Axis::W], expectedW)) ;
        }
    }

    void UTQuaternion::utilities() {}

    void UTQuaternion::operators() {}
}
