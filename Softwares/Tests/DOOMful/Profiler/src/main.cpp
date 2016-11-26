#define DEBUG

#include <utils/Profiler.hpp>
#include <iostream>

const std::string profilingSourceName = "Fibonacci" ;

int fibonacci(int n) {
    if (n < 3) {
        return 1 ;
    }

    return fibonacci(n - 1) + fibonacci(n - 2) ;
}

int chronoFibonacci(int n) {
    Profiler_Start(profilingSourceName) ;
    int result = fibonacci(n) ;
    Profiler_Stop(profilingSourceName) ;
}

int main(int, char** argv) {
    Profiler_AddSource(profilingSourceName) ;

    chronoFibonacci(32) ;
    chronoFibonacci(36) ;
    chronoFibonacci(42) ;

    Profiler_Flush() ;

    std::cout << "Fibonacci computed in "
              << Profiler_GetTime(profilingSourceName)
              << " milliseconds."
              << std::endl ;

    return EXIT_SUCCESS ;
}
