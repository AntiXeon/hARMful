#include <UnitTest.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

int UnitTest::ValidatedUnitTestSession = EXIT_SUCCESS ;

UnitTest::UnitTest(float epsilon) : m_epsilon(epsilon) {}

UnitTest::~UnitTest() {}

int UnitTest::Success() {
    return ValidatedUnitTestSession ;
}

void UnitTest::assert(bool condition) {
    if (!condition) {
        std::cerr << "Failed at "
                  << __FILE__
                  << "::"
                  << __func__
                  << "() on line "
                  << __LINE__
                  << std::endl ;

        ValidatedUnitTestSession = EXIT_FAILURE ;
    }
}

bool UnitTest::compare(float a, float b) {
    float diff = std::abs(a - b) ;
    return diff < m_epsilon ;
}
