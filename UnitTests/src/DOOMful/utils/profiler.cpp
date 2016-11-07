#include <mock_assert.h>
#include <utils/Profiler.h>
#include <unistd.h>

using namespace std ;
using namespace Doom ;

#define INTERVAL    200         //us

void test_profiler_1ms() {
    const int wait = 1000 ;     // us
    Profiler_Start("unittest") ;
    usleep(wait) ;
    Profiler_Stop("unittest") ;
    Profiler_Flush() ;
    int spent_time = Profiler_GetTime("unittest") ;

    int min_interval = wait - INTERVAL ;
    int max_interval = wait + INTERVAL ;
    assert(spent_time > min_interval) ;
    assert(spent_time < max_interval) ;
}

void test_profiler_10ms() {
    const int wait = 10000 ;    // us
    Profiler_Start("unittest") ;
    usleep(wait) ;
    Profiler_Stop("unittest") ;
    Profiler_Flush() ;
    int spent_time = Profiler_GetTime("unittest") ;

    int min_interval = wait - INTERVAL ;
    int max_interval = wait + INTERVAL ;
    assert(spent_time > min_interval) ;
    assert(spent_time < max_interval) ;
}

void test_profiler_100ms() {
    const int wait = 100000 ;   // us
    Profiler_Start("unittest") ;
    usleep(wait) ;
    Profiler_Stop("unittest") ;
    Profiler_Flush() ;
    int spent_time = Profiler_GetTime("unittest") ;

    int min_interval = wait - INTERVAL ;
    int max_interval = wait + INTERVAL ;
    assert(spent_time > min_interval) ;
    assert(spent_time < max_interval) ;
}

void test_profiler_1000ms() {
    const int wait = 1000000 ;  // us
    Profiler_Start("unittest") ;
    usleep(wait) ;
    Profiler_Stop("unittest") ;
    Profiler_Flush() ;
    int spent_time = Profiler_GetTime("unittest") ;

    int min_interval = wait - INTERVAL ;
    int max_interval = wait + INTERVAL ;
    assert(spent_time > min_interval) ;
    assert(spent_time < max_interval) ;
}

int main() {
    Profiler_Initialize() ;
    Profiler_AddSource("unittest") ;

    test_profiler_1ms() ;
    test_profiler_10ms() ;
    test_profiler_100ms() ;
    test_profiler_1000ms() ;

    Profiler_Close() ;

    return TestResult ; // Defined in <mock_assert.h>
}
