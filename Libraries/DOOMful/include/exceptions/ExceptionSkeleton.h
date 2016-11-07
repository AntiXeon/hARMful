/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       ExceptionSkeleton.h        */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    26/02/2015                 */
/* UPDATE:      26/02/2015                 */
/*                                         */
/* Common code to all Exception subclasses.*/
/*******************************************/


#ifndef EXCEPTION_SKELETON_MACRO
    #include <string>

    #define EXCEPTION_SKELETON_MACRO
    #define DECLARE_EXCEPTION_NAME      static std::string Name ;
    // To easyly set the exception name
    #define SET_EXCEPTION_NAME(name)    std::string name::Name = #name


    /**
     * @brief   Declaration of a direct Exception subclass.
     * @param   class   Name of the subclass.
     */
    #define DECLARE_EXCEPTION(class)                                            \
        private:                                                                \
            /** @brief  Name of the exception class. */                         \
            DECLARE_EXCEPTION_NAME                                              \
                                                                                \
        public:                                                                 \
            /**                                                                 \
             * @brief   Create an exception on gamut construction error.        \
             * @param   message     Message of the exception.                   \
             * @param   file        File from which the exception was thrown.   \
             * @param   function    Function from which the exception was       \
             *          thrown.                                                 \
             * @param   line        Line where the exception was thrown.        \
             * @warning Do not use directly this constructor. Use the macro     \
             *          ThrowIOException(msg) instead to throw an exception.    \
             */                                                                 \
            class(std::string message,                                          \
                  char* file,                                                   \
                  char* function,                                               \
                  unsigned int line) throw() ;                                  \
                                                                                \
            /** @brief  Destruction of gamut exception. */                      \
            virtual ~class() throw() ;                                          \
                                                                                \
                                                                                \
        protected:                                                              \
            /** @brief   Perform an additional initialization task. */          \
            virtual void additionalInitializationTask() ;

    /**
     * @brief   Implementation of the exception subclass (for a direct
     *          inheritance from Exception). Constructor and destructor.
     * @brief   class   The class to quickly implement.
     */
    #define IMPLEMENT_EXCEPTION(class)                                          \
        SET_EXCEPTION_NAME(class) ;                                             \
                                                                                \
        class::class(std::string message,                                       \
                     char* file,                                                \
                     char* function,                                            \
                     unsigned int line) throw() : Exception(&Name,              \
                                                            message,            \
                                                            file,               \
                                                            function,           \
                                                            line) {}            \
                                                                                \
        class::~class() throw() {}
#endif
