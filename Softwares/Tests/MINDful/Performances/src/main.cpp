#include <utils/Chrono.hpp>
#include <geometry/quaternions/Quaternion.hpp>
#include <iostream>

using namespace Doom ;
using namespace Mind ;

int main(int, char**) {
    Chrono chr ;

    Quaternion quat(0.f, 0.f, 0.f, 1.f) ;
    Matrix3x3f matrix ;


    chr.start() ;
    for (int i = 0 ; i < 100'000'000 ; ++i) {
        quat.to(matrix) ;
    }
    chr.stop() ;

    std::cout << matrix << std::endl ;
    std::cout << "Elapsed time: " << chr.elapsedTime<std::chrono::milliseconds>() << "ms" << std::endl ;
    return 0 ;
}
