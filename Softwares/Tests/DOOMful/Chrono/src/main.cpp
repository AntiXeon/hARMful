#include <utils/Chrono.hpp>
#include <iostream>

int fibonacci(int n) {
    if (n < 3) {
        return 1 ;
    }

    return fibonacci(n - 1) + fibonacci(n - 2) ;
}

int main(int, char** argv) {
    Doom::Chrono chrono ;

    chrono.start() ;
    int result = fibonacci(46) ;
    chrono.stop() ;

    std::cout << "Fibonacci computed in "
              << chrono.elapsedTime<std::chrono::milliseconds>()
              << " milliseconds."
              << std::endl ;

    return EXIT_SUCCESS ;
}
