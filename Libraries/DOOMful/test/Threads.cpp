#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <DOOMful.h>
#include <list>

using namespace Doom ;
using namespace std;

#define MAX_THREADS 12

void* Function(void*) {
    int wait = (rand() % 100) ;
    usleep(wait) ;

    return NULL ;
}

int main() {
    Log::InitSystem("threads.log", Log::LogCritical) ;

    Random::Initialize() ;

    string ThreadNames[MAX_THREADS] ;
    for (int str = 0 ; str < MAX_THREADS ; ++str) {
        ThreadNames[str] = String::Random(16) ;
        cout << "Thread name = " << ThreadNames[str] << endl ;
    }

    // Create useless threads for a long time.
    for (int i = 0 ; i < 1000000 ; ++i) {
        for (int t = 0 ; t < MAX_THREADS ; ++t) {
            ThreadManager::Run(
                               ThreadNames[t],
                               &Function,
                               NULL,
                               NULL
                              ) ;
        }

        for (int t = 0 ; t < MAX_THREADS ; ++t) {
            ThreadManager::Join(ThreadNames[t]) ;
        }
    }

    Log::Stop() ;
    return 0 ;
}
