#ifndef __DOOM__PLATFORM__
#define __DOOM__PLATFORM__

    #ifdef __linux__
        #define LinuxPlatform
    #elif _WIN32 || _WIN64
        #define WindowsPlatform
    #else
        #error "Unsupported compiler and/or platform"
    #endif

#endif
