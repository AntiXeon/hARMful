/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       Exception.cpp              */
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

#ifdef __cplusplus

#include <exceptions/Exception.h>
#include <utils/String.h>
#include <iostream>
#include <stdlib.h>


namespace Doom {

    Exception::Exception(std::string* name,
                         std::string message,
                         char* file,
                         char* function,
                         unsigned int line) throw() : std::exception() {
        m_exceptionName = name ;
        m_message = message ;
        m_file = std::string(file) ;
        m_function = std::string(function) ;
        m_line = line ;

        // Construct the whole message of the exception
        m_buffer = std::string(*m_exceptionName) ;
        m_buffer += " thrown in " + m_file + "::" + m_function + "(), line " + String::ToStringi(line) + "\n" ;
        m_buffer += m_message ;
    }

    Exception::~Exception() throw() {}


    const char* Exception::what() const throw() {
        return m_buffer.c_str() ;
    }

    void Exception::print() const throw() {
        std::cerr << m_buffer << std::endl ;
    }


    const std::string& Exception::getType() const {
        return *m_exceptionName ;
    }

    const std::string& Exception::getMessage() const {
        return m_message ;
    }

    const std::string& Exception::getFile() const {
        return m_file ;
    }

    const std::string& Exception::getFunction() const {
        return m_function ;
    }

    unsigned int Exception::getLine() const {
        return m_line ;
    }

} ;

#endif // __cplusplus
