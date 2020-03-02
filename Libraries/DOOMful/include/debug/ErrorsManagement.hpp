#ifndef __DOOM__ERROR_MANAGEMENT__
#define __DOOM__ERROR_MANAGEMENT__

#include <utils/Platform.hpp>
#include <memory>

#ifdef LinuxPlatform
    #include <cerrno>
#elif defined(WindowsPlatform)
    #include <windows.h>
#endif

namespace Doom {
    /**
     * Management of the errors, from the C library for example.
     */
    namespace ErrorsManagement {
        /**
         * Print an error message from the C library.
         * @param   file        File in which the error occurs.
         * @param   line        Line in the file at which the error occurs.
         * @param   function    Function in which the error occurs.
         */
        exported void PrintCError(
            const char* file,
            int line,
            const char* function
        ) ;

        /**
         * Exit the application if an error in the C library occurs.
         * @param   file        File in which the error occurs.
         * @param   line        Line in the file at which the error occurs.
         * @param   function    Function in which the error occurs.
         * @param   Message     User message to be printed when the error
         *                      occurs.
         */
        exported void ExitOnCError(
            const char* file,
            int line,
            const char* function,
            const char* message = nullptr
        ) ;
    }
}

/**
 * Check if a condition is checked.
 */
#define WARN_ON_CERROR() Doom::ErrorsManagement::PrintCError(__FILE__, __LINE__, __func__)

/**
 * Check if a condition is checked. An error message is displayed when the
 * condition is wrong and the program exits.
 */
#define STOP_ON_CERROR() Doom::ErrorsManagement::ExitOnCError(__FILE__, __LINE__, __func__)

 /**
  * Check if a condition is checked. An error message is displayed when the
  * condition is wrong and the program exits.
  * @param   msg     Add a user message.
  */
#define STOP_ON_CERROR_MSG(msg) Doom::ErrorsManagement::ExitOnCError(__FILE__, __LINE__, __func__, msg)

#endif
