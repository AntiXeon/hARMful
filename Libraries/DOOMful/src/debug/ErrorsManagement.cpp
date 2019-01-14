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
    std::weak_ptr<LogSystem> logWeakPtr = LogSystem::GetInstance() ;
    std::shared_ptr<LogSystem> logSys = logWeakPtr.lock() ;

    if (!logSys) {
        return ;
    }

    if (message) {
        logSys -> writeLine<const char*, const char*, int, const char*, const char*, const char*, char*, const char*, const char*>(
            LogSystem::Gravity::Error,
            file,
            "::",
            line,
            "@",
            function,
            ": ",
            ErrorFunction(errno),
            "\nMESSAGE: ",
            message
        ) ;
    }
    else {
        logSys -> writeLine<const char*, const char*, int, const char*, const char*, const char*, char*>(
            LogSystem::Gravity::Error,
            file,
            "::",
            line,
            "@",
            function,
            ": ",
            ErrorFunction(errno)
        ) ;
    }
}

void Doom::ErrorsManagement::PrintCError(
    const char* file,
    int line,
    const char* function
) {
    if (ErrorNumber != 0) {
        PrintErrno(file, line, function) ;
    }
}

void Doom::ErrorsManagement::ExitOnCError(
    const char* file,
    int line,
    const char* function,
    const char* message
) {
    if (ErrorNumber != 0) {
        PrintErrno(file, line, function, message) ;
        exit(-1) ;
    }
}
