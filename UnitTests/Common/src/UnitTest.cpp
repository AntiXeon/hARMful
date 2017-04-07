#include <UnitTest.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

int UnitTest::ValidatedUnitTestSession = EXIT_SUCCESS ;
unsigned int UnitTest::AmountRunTests = 0 ;
unsigned int UnitTest::AmountSuccessfulTests = 0 ;

int UnitTest::Success() {
    std::cout << AmountSuccessfulTests
                << "/"
                << AmountRunTests
                << " passed tests"
                << std::endl ;

    return ValidatedUnitTestSession ;
}

void UnitTest::checkCondition(
    const bool condition,
    const char* file,
    const char* function,
    const int line
) {
    AmountRunTests++ ;

    if (!condition) {
        std::cerr << "Failed at "
                  << file
                  << "::"
                  << function
                  << "() on line "
                  << line
                  << std::endl ;

        ValidatedUnitTestSession = EXIT_FAILURE ;
    }
    else {
        AmountSuccessfulTests++ ;
    }
}

bool UnitTest::compare(
    const float a,
    const float b,
    const float epsilon
) {
    float diff = std::abs(a - b) ;
    return diff < epsilon ;
}
