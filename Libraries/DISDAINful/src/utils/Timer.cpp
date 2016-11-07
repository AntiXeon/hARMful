#include "Timer.h"

#include <assert.h>

Timer::Timer(int wait) {
	assert(wait > 1) ;

    m_initValue = wait ;
    m_counter = wait ;
}

Timer::~Timer() {}
