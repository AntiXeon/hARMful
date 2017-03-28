#include <utils/Chrono.hpp>
#include <utils/Random.hpp>
#include <matrices/Matrix3x3f.hpp>
#include <geometry/points/Point3Df.hpp>
#include <geometry/quaternions/Quaternion.hpp>
#include <iostream>

using namespace Doom ;
using namespace Mind ;

static Matrix3x3f generateRandomMatrix() {
    Vector3f row1(
        Random::GetNormalizedFloat(),
        Random::GetNormalizedFloat(),
        Random::GetNormalizedFloat()
    ) ;

    Vector3f row2(
        Random::GetNormalizedFloat(),
        Random::GetNormalizedFloat(),
        Random::GetNormalizedFloat()
    ) ;

    Vector3f row3(
        Random::GetNormalizedFloat(),
        Random::GetNormalizedFloat(),
        Random::GetNormalizedFloat()
    ) ;

    Matrix3x3f mat ;
    mat.setRowValues(0, row1) ;
    mat.setRowValues(1, row2) ;
    mat.setRowValues(2, row3) ;
    return mat ;
}

int main(int, char**) {
    #ifdef FORCE_EMULATED_SIMD
        #pragma message("EMULATED SIMD")
    #else
        #pragma message("CPU SIMD")
    #endif

    const bool UseShortestPath = true ;
    Quaternion result ;
    Vector3f vectorQ2(
        Random::GetNormalizedFloat(),
        Random::GetNormalizedFloat(),
        Random::GetNormalizedFloat()
    ) ;

    Chrono chr ;
    chr.start() ;
    for (int i = 0 ; i < 10000000 ; ++i) {
        // Setup the matrix to create quaternion q1.
        Matrix3x3f matQ1 = generateRandomMatrix() ;
        Quaternion q1(matQ1) ;
        q1.normalize() ;

        // Setup vector and angle to create quaternion q2.
        Scalar angleQ2 = Random::GetNormalizedFloat() * Math::Pi ;
        Quaternion q2(vectorQ2, angleQ2) ;
        q2.normalize() ;

        result += Quaternion::nlerp(
            Random::GetNormalizedFloat(),
            q1,
            q2,
            UseShortestPath
        ) ;

        Quaternion q3(0.1f, 0.1f, 0.1f, 0.1f) ;
        result *= q3 ;
        vectorQ2 = result * vectorQ2 ;
    }
    chr.stop() ;

    std::cout << result << std::endl ;
    std::cout << "Elapsed time: " << chr.elapsedTime<std::chrono::milliseconds>() << "ms" << std::endl ;
    return 0 ;
}
