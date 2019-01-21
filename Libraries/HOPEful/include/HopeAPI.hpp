#ifndef __HOPE__API__
    #ifndef API
        namespace Hope::GL {}
        #define API GL
    #endif
#define __HOPE__API__

#define OGL
//#define VK    // Not yet implemented.

#ifdef OGL
    // ???
#elif defined VK
    #error "Unsupported graphics API"
#endif

#endif
