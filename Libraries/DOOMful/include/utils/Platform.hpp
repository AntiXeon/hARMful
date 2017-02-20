#ifndef __DOOM__PLATFORM__
#define __DOOM__PLATFORM__

    #ifdef __linux__
        #define LinuxPlatform
        #define exported
    #elif _WIN32 || _WIN64
        #define WindowsPlatform
        // Required on Visual C++ to generate a .lib file alongside the .dll.
        #defined exported __declspec(dllexport)
    #else
        #error "Unsupported compiler and/or platform"
    #endif

#endif
