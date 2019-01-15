#ifndef __SPITE__BINARY_FILE_READER__
#define __SPITE__BINARY_FILE_READER__

#include <utils/Platform.hpp>
#include <stdint.h>
#include <string>
#include <vector>
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
            exported virtual int8_t readChar() = 0 ;

            /**
             * Read a 16-bit integer value.
             * @return  The read value.
             */
            exported virtual int16_t readShort() = 0 ;

            /**
             * Read a 32-bit integer value.
             * @return  The read value.
             */
            exported virtual int32_t readInt32() = 0 ;

            /**
             * Read a 64-bit integer value.
             * @return  The read value.
             */
            exported virtual int64_t readInt64() = 0 ;

            /**
             * Read a 32-bit float value.
             * @return  The read value.
             */
            exported virtual float readFloat() = 0 ;

            /**
             * Read a 64-bit float value.
             * @return  The read value.
             */
            exported virtual double readDouble() = 0 ;

            /**
             * Read a string byte by byte.
             * @param   string  Buffer to store the content of the string.
             * @param   length  Length of the string in byte.
             */
            exported virtual void readString(
                char string[],
                const unsigned int length
            ) = 0 ;

            /**
             * Read a string byte by byte.
             * @param   buffer  Buffer to store the characters of the string.
             * @param   length  Length of the string in byte.
             */
            exported virtual void readString(
                std::string& buffer,
                const unsigned int length
            ) = 0 ;

            /**
             * Read all the bytes from a binary file.
             * @param   blob    Blob data got from the file.
             */
            exported void readAllBytes(char* blob, const size_t size) ;

            /**
             * Read all the bytes from a binary file.
             * @param   blob    Blob data got from the file.
             */
            exported void readAllBytes(std::vector<char>& blob) ;

            /**
             * Read all the bytes from a binary file.
             * @param   blob    Blob data got from the file.
             */
            exported void readAllBytes(std::vector<unsigned char>& blob) ;
    } ;
}

#endif
