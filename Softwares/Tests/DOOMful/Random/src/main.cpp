#define DEBUG

#include <utils/Random.hpp>
#include <iostream>

int main(int, char** argv) {
    Doom::Random::Initialize() ;

    std::cout << "Random integer = "
              << Doom::Random::GetInteger()
              << std::endl ;

    const int min = 3 ;
    const int max = 96 ;
    std::cout << "Random integer[" << min << ";" << max << "] = "
              << Doom::Random::GetInteger(min, max)
              << std::endl ;

    std::cout << "Random float = "
              << Doom::Random::GetNormalizedFloat()
              << std::endl ;

    return EXIT_SUCCESS ;
}
