#ifndef __MIND_TYPES__
#define __MIND_TYPES__


namespace Mind {
    #if MIND_DOUBLE_PRECISION == 1
        typedef double Scalar ;
    #else
        typedef float Scalar ;
    #endif
} ;


#endif
