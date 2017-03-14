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

    Quaternion quat(0.f, 0.f, 0.f, 1.f) ;
    Scalar dot ;

    chr.start() ;
    for (int i = 0 ; i < 1'000'000'000 ; ++i) {
        dot = quat.dot(quat) ;
    }
    chr.stop() ;

    std::cout << dot << std::endl ;
    std::cout << "Elapsed time: " << chr.elapsedTime<std::chrono::milliseconds>() << "ms" << std::endl ;
    return 0 ;
}
