#ifndef __MIND__TYPES__
#define __MIND__TYPES__

namespace Mind {
    #if MIND_DOUBLE_PRECISION == 1
        typedef double Scalar ;
    #else
        typedef float Scalar ;
    #endif
} ;

#endif
