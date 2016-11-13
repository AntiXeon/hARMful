/**
 * Printer.hpp
 * GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
 *
 * @Author:      Denis CARLUS
 * @Created on:  13-Nov-2016
 * @Last change: 13-Nov-2016
 */

#ifndef __DOOM__BASE_PRINTER__
#define __DOOM__BASE_PRINTER__

#include <iostream>

namespace Doom {
    /**
     * Base class to make a printer in a output stream.
     */
    class Printer {
        protected:
            /**
             * A class to print a value on its creation.
             */
            class ValuePrinter final {
                public:
                    /**
                     * Print the provided value in the provided output stream.
                     * @param   stream  Stream in which the @a value is printed.
                     * @param   value   Value to print in the @a stream.
                     */
                    template<class T, class ... Args>
                    ValuePrinter(std::ostream& stream, const T& value, const Args& ... args) {
                        stream << value ;
                    }

                    template<class T>
                    ValuePrinter(std::ostream& stream, const T& value) {
                        stream << value ;
                    }

                    /**
                     * Print the provided value in the provided output stream.
                     * @param   stream  Stream in which the @a value is printed.
                     */
                    ValuePrinter(std::ostream&) {}

                    /**
                     * Destruction of the BasicPrinter instance.
                     */
                    virtual ~ValuePrinter() {}
            } ;

        public:
            /**
             * Destruction of the Printer.
             */
            virtual ~Printer() {}
    } ;
} ;

#endif
