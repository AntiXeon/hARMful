#include <debug/ErrorsManagement.hpp>
#include <utils/LogSystem.hpp>
#include <cassert>
#include <cstdlib>
#include <cstring>

using namespace Doom ;
using namespace Doom::ErrorsManagement ;

static void PrintErrno(
    const char* file,
    int line,
    const char* function,
    const char* message = nullptr
) {
    if (!LogSystem::Ready()) {
        return ;
    }

#ifdef LinuxPlatform
    if (message) {
        LogSystem::WriteLine<const char*, const char*, int, const char*, const char*, const char*, char*, const char*, const char*>(
            LogSystem::Gravity::Error,
            file,
            "::",
            line,
            "@",
            function,
            ": ",
            ::strerror(errno),
            "\nMESSAGE: ",
            message
        ) ;
    }
    else {
        LogSystem::WriteLine<const char*, const char*, int, const char*, const char*, const char*, char*>(
            LogSystem::Gravity::Error,
            file,
            "::",
            line,
            "@",
            function,
            ": ",
            ::strerror(errno)
        ) ;
    }
#elif defined(WindowsPlatform)
    if (message) {
        LogSystem::WriteLine<const char*, const char*, const char*, const char*, int, const char*, const char*>(
            LogSystem::Gravity::Error,
            message,
            "\n",
            file,
            "::",
            line,
            "@",
            function
        );
    }
    else {
        LogSystem::WriteLine<const char*, const char*, int, const char*, const char*>(
            LogSystem::Gravity::Error,
            file,
            "::",
            line,
            "@",
            function
        );
    }
#endif
}

void Doom::ErrorsManagement::PrintCError(
    const char* file,
    int line,
    const char* function
) {
    if (errno != 0) {
        PrintErrno(file, line, function) ;
    }
}

void Doom::ErrorsManagement::ExitOnCError(
    const char* file,
    int line,
    const char* function,
    const char* message
) {
    if (errno != 0) {
        PrintErrno(file, line, function, message) ;
        exit(-1) ;
    }
}
