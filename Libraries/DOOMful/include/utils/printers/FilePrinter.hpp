/**
 * FilePrinter.hpp
 * GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
 *
 * @Author:      Denis CARLUS
 * @Created on:  11-Nov-2016
 * @Last change: 13-Nov-2016
 */

#ifndef __DOOM__FILE_PRINTER__
#define __DOOM__FILE_PRINTER__

#include <utils/printers/Printer.hpp>
#include <fstream>
#include <string>
#include <mutex>

namespace Doom {
    /**
     * A FilePrinter to write values in a file.
     */
    class FilePrinter final : public Printer {
        private:
            /**
             * Avoid concurrent accesses to the Console.
             */
            std::mutex m_mutex ;

            /**
             * Output stream to print values.
             */
            std::ofstream m_output ;

        public:
            /**
             * Instantiate a new FilePrinter object that prints in a file.
             * This constructor makes the file be overwritten if already
             * existing.
             * @param   filepath    Path to the file in which values are
             *                      written.
             */
            FilePrinter(const std::string& filepath) throw(std::ios_base::failure) ;

           /**
            * Instantiate a new FilePrinter object that prints in a file.
            * @param   filepath     Path to the file in which values are
            *                       written.
            * @param    append      TRUE to append values at the end of the file
            *                       if existing. FALSE to overwrite the full
            *                       content of the file.
            */
            FilePrinter(
                const std::string& filepath,
                const bool& append
            ) throw(std::ios_base::failure) ;

            /**
             * Destruction of the FilePrinter instance.
             */
            virtual ~FilePrinter() noexcept ;

            /**
             * Write a message on the FilePrinter and create a new line in the
             * output stream.
             * @param   value   The value to be printed.
             */
            template<class T>
            void writeLine(const T& value) {
                m_mutex.lock() ;
                    m_output << value << std::endl ;
                m_mutex.unlock() ;
            }

            /**
             * Write messages on the FilePrinter and create a new line in the
             * output stream.
             * @param   value   The value to be printed.
             * @param   args    Remaining arguments to be printed.
             */
            template<class T, class ... Args>
            void writeLine(const T& value, const Args& ... args) {
                m_mutex.lock() ;
                    m_output << value ;
                    auto printer = { Printer::ValuePrinter(m_output, args)... } ;
                    m_output << std::endl ;
                m_mutex.unlock() ;
            }

            /**
             * Write a message on the FilePrinter.
             * @param   value   The value to be printed.
             */
            template<class T>
            void write(const T& value) {
                m_mutex.lock() ;
                    m_output << value << std::flush ;
                m_mutex.unlock() ;
            }

            /**
             * Write messages on the FilePrinter.
             * @param   value   The value to be printed.
             * @param   args    Remaining arguments to be printed.
             */
            template<class T, class ... Args>
            void write(const T& value, const Args& ... args) {
                m_mutex.lock() ;
                    m_output << value ;
                    auto printer = { Printer::ValuePrinter(m_output, args)... } ;
                    m_output << std::flush ;
                m_mutex.unlock() ;
            }

        private:
            /**
             * Get the access mode to the file according. It depends on the @a
             * append value.
             * @param  append TRUE to append new values at the end of the file,
             *                FALSE to overwrite the content of the file.
             * @return        The access mode to the file.
             */
            std::ios_base::openmode getAccessMode(const bool& append) ;
    } ;
} ;

#endif
