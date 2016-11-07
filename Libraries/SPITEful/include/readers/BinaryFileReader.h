#ifndef __SPITE_BINARY_FILE_READER__
#define __SPITE_BINARY_FILE_READER__

#include <stdint.h>
#include <string>
#include <readers/FileReader.h>

namespace Spite {

    /**
     * @brief   A BinaryFileReader is used to read binary files.
     *
     * @author  Denis CARLUS
     * @version 1.0     08/23/2015
     */
    class BinaryFileReader : public FileReader {
        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /** @brief  Creation of a BinaryFileReader. */
            BinaryFileReader() ;

            /** @brief  Destruction of a BinaryFileReader. */
            virtual ~BinaryFileReader() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Read a 8-bit integer value.
             * @return  The read value.
             */
            virtual int8_t readChar() = 0 ;

            /**
             * @brief   Read a 16-bit integer value.
             * @return  The read value.
             */
            virtual int16_t readShort() = 0 ;

            /**
             * @brief   Read a 32-bit integer value.
             * @return  The read value.
             */
            virtual int32_t readInt32() = 0 ;

            /**
             * @brief   Read a 64-bit integer value.
             * @return  The read value.
             */
            virtual int64_t readInt64() = 0 ;

            /**
             * @brief   Read a 32-bit float value.
             * @return  The read value.
             */
            virtual float readFloat() = 0 ;

            /**
             * @brief   Read a 64-bit float value.
             * @return  The read value.
             */
            virtual double readDouble() = 0 ;

            /**
             * @brief   Read a string byte by byte.
             * @param   string  Buffer to store the content of the string.
             * @param   length  Length of the string in byte.
             */
            virtual void readString(
                                    char string[],
                                    const unsigned int length
                                   ) = 0 ;

            /**
             * @brief   Read a string byte by byte.
             * @param   buffer  Buffer to store the characters of the string.
             * @param   length  Length of the string in byte.
             */
            virtual void readString(
                                    std::string& buffer,
                                    const unsigned int length
                                   ) = 0 ;
    } ;

} ;


#endif
