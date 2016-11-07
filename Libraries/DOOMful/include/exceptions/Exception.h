/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       Exception.h                */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    26/02/2015                 */
/* UPDATE:      26/02/2015                 */
/*                                         */
/* An Exception can be thrown to signal an */
/* unexepected behavior in the program. It */
/* can be caught to generate a response    */
/* inside the function stack. It can be    */
/* either thrown to end the execution or   */
/* to catch up the situation.              */
/*******************************************/


#ifndef __DOOM__EXCEPTION__
#define __DOOM__EXCEPTION__


#include "ExceptionSkeleton.h"
#include <exception>
#include <string>


namespace Doom {

    /**
     * @brief   An Exception can be thrown to signal an unexepected behavior in the
     *          program. It can be caught to generate a response inside the function
     *          stack. It can be either thrown to end the execution or to catch up
     *          the situation.
     * @version 1.0 04/22/2014
     * @author  Denis CARLUS
     */
    class Exception : public std::exception {
        protected:
            /** @brief  Pointer to the name of the exception. */
            std::string* m_exceptionName ;

            /** @brief  Message of the exception. */
            std::string m_message ;
            /** @brief  File from which the exception was thrown. */
            std::string m_file ;
            /** @brief  Function from which the exception was thrown. */
            std::string m_function ;
            /** @brief  Line where the exception was thrown. */
            unsigned int m_line ;

            /** @brief  Buffer containing th whole message of the exception. */
            std::string m_buffer ;


        public:
            /**
             * @brief   Create an exception on Input/Output streams.
             * @param   name        Name of the exception.
             * @param   message     Message of the exception.
             * @param   file        File from which the exception was thrown.
             * @param   function    Function from which the exception was thrown.
             * @param   line        Line where the exception was thrown.
             */
            Exception(std::string* name,
                      std::string message,
                      char* file,
                      char* function,
                      unsigned int line) throw() ;

            /** @brief  Destruction of Input/Output exception. */
            virtual ~Exception() throw() ;


            /** @brief  Get the exception complete message. */
            virtual const char* what() const throw() ;

            /** @brief  Print the complete message on terminal. */
            void print() const throw() ;


            /** @brief Get the type of exception. */
            const std::string& getType() const ;

            /** @brief  Get the message of the exception. */
            const std::string& getMessage() const ;

            /** @brief  Get the file from which the exception has been thrown. */
            const std::string& getFile() const ;

            /** @brief  Get the function from which the exception has been thrown. */
            const std::string& getFunction() const ;

            /** @brief  Get the line from which the exception has been thrown. */
            unsigned int getLine() const ;

        protected:
            /** @brief   Perform an additional initialization task. */
            virtual void additionalInitializationTask() = 0 ;
    } ;

} ;


#define ThrowException(type, msg) throw type(msg, (char*) __FILE__, (char*) __func__, __LINE__)


#endif
