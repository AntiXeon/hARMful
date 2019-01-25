#ifndef __HOPE__API__
#define __HOPE__API__

#define OGL // use OpenGL API
//#define VK    // Not yet implemented.

#ifdef OGL
    namespace Hope::GL {}
    namespace API = Hope::GL ;
#elif defined VK
    #error "Unsupported graphics API"
#endif

#endif  // __HOPE__API__
