#include <UnitTest.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

int UnitTest::ValidatedUnitTestSession = EXIT_SUCCESS ;

UnitTest::UnitTest(float epsilon) : m_epsilon(epsilon) {}

UnitTest::~UnitTest() {}

int UnitTest::Success() {
    if (ValidatedUnitTestSession == EXIT_SUCCESS) {
        std::cout << "Unit test: passed" << std::endl ;
    }
    else {
        std::cerr << "Unit test: failed" << std::endl ;
    }

    return ValidatedUnitTestSession ;
}

void UnitTest::checkCondition(bool condition, const char* file, const  char* function, int line) {
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
}

bool UnitTest::compare(float a, float b) {
    float diff = std::abs(a - b) ;
    return diff < m_epsilon ;
}
