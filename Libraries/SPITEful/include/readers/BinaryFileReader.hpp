#ifndef __SPITE__BINARY_FILE_READER__
#define __SPITE__BINARY_FILE_READER__

#include <stdint.h>
#include <string>
#include <readers/FileReader.hpp>

namespace Spite {

    /**
     * A BinaryFileReader is used to read binary files.
     */
    class BinaryFileReader : public FileReader {
        public:
            /**
             * Read a 8-bit integer value.
             * @return  The read value.
             */
            virtual int8_t readChar() = 0 ;

            /**
             * Read a 16-bit integer value.
             * @return  The read value.
             */
            virtual int16_t readShort() = 0 ;

            /**
             * Read a 32-bit integer value.
             * @return  The read value.
             */
            virtual int32_t readInt32() = 0 ;

            /**
             * Read a 64-bit integer value.
             * @return  The read value.
             */
            virtual int64_t readInt64() = 0 ;

            /**
             * Read a 32-bit float value.
             * @return  The read value.
             */
            virtual float readFloat() = 0 ;

            /**
             * Read a 64-bit float value.
             * @return  The read value.
             */
            virtual double readDouble() = 0 ;

            /**
             * Read a string byte by byte.
             * @param   string  Buffer to store the content of the string.
             * @param   length  Length of the string in byte.
             */
            virtual void readString(
                char string[],
                const unsigned int length
            ) = 0 ;

            /**
             * Read a string byte by byte.
             * @param   buffer  Buffer to store the characters of the string.
             * @param   length  Length of the string in byte.
             */
            virtual void readString(
                std::string& buffer,
                const unsigned int length
            ) = 0 ;
    } ;
}

#endif
