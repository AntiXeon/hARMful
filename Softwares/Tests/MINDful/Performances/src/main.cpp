#include <utils/Chrono.hpp>
#include <geometry/quaternions/Quaternion.hpp>
#include <iostream>

using namespace Doom ;
using namespace Mind ;

int main(int, char**) {
    #ifdef FORCE_EMULATED_SIMD
        #pragma message("EMULATED SIMD")
    #else
        #pragma message("CPU SIMD")
    #endif

    Chrono chr ;

    const bool UseShortestPath = true ;
    Quaternion quat(0.f, 0.f, 0.f, 1.f) ;
    Scalar dot ;

    chr.start() ;
    for (int i = 0 ; i < 100'000'000 ; ++i) {
        dot = quat.dot(quat) ;
        Quaternion ln = quat.ln() ;
        Quaternion exp = quat.exp() ;
        exp *= dot ;
        exp.normalize() ;

        ln.normalize() ;

        static const Scalar SlerpTime = 0.32f ;
        Quaternion slerped = Quaternion::slerp(SlerpTime, exp, ln, UseShortestPath) ;
        quat = slerped ;
    }
    chr.stop() ;

    std::cout << quat << std::endl ;
    std::cout << "Elapsed time: " << chr.elapsedTime<std::chrono::milliseconds>() << "ms" << std::endl ;
    return 0 ;
}
