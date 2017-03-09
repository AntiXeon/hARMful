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
    }

    void UTQuaternion::utilities() {}

    void UTQuaternion::operators() {}
}
