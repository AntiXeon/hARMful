#include <UnitTest.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

int UnitTest::ValidatedUnitTestSession = EXIT_SUCCESS ;
unsigned int UnitTest::AmountRunTests = 0 ;
unsigned int UnitTest::AmountSuccessfulTests = 0 ;

UnitTest::UnitTest(float epsilon) : m_epsilon(epsilon) {}

UnitTest::~UnitTest() {}

int UnitTest::Success() {
    std::cout << AmountSuccessfulTests
                << "/"
                << AmountRunTests
                << " passed tests"
                << std::endl ;

    return ValidatedUnitTestSession ;
}

void UnitTest::checkCondition(bool condition, const char* file, const  char* function, int line) {
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

bool UnitTest::compare(float a, float b) {
    float diff = std::abs(a - b) ;
    return diff < m_epsilon ;
}
