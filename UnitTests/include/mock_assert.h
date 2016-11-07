#ifndef __MOCK_ASSERT__
#define __MOCK_ASSERT__

#include <stdio.h>
#include <stdlib.h>


#define SUCCESSFUL_TEST 1
#define ERROR_TEST      0

static int TestResult = SUCCESSFUL_TEST ;

#ifdef assert
    #undef assert
#endif

#define assert(cond) {                                                              \
    if (!(cond)) {                                                                  \
        printf("Failed at %s::%s() on line %d\n", __FILE__, __func__, __LINE__) ;   \
        TestResult = ERROR_TEST ;    /* FAIL */                                     \
    }                                                                               \
}

#endif
