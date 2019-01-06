#ifndef __HOPE__API__
#define __HOPE__API__

#define OGL
//#define VK    // Not yet implemented.

#ifdef OGL
    #define API GL
#elif defined VK
    #define API Vulkan
#endif

#endif
