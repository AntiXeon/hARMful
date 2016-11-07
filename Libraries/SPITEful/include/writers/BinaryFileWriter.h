#ifndef __SPITE_BINARY_FILE_WRITER__
#define __SPITE_BINARY_FILE_WRITER__


#include <stdint.h>
#include <string>
#include <writers/FileWriter.h>


namespace Spite {

    /**
     * @brief   A BinaryFileWriter is used to write binary files.
     *
     * @author  Denis CARLUS
     * @version 1.0     08/25/2015
     */
    class BinaryFileWriter : public FileWriter {
        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /** @brief  Creation of a BinaryFileWriter. */
            BinaryFileWriter() ;

            /** @brief  Destruction of a BinaryFileWriter. */
            virtual ~BinaryFileWriter() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Write a 8-bit integer value.
             * @param   value   The value to write.
             */
            virtual void writeChar(int8_t value) = 0 ;

            /**
             * @brief   Write a 16-bit integer value.
             * @param   value   The value to write.
             */
            virtual void writeShort(int16_t value) = 0 ;

            /**
             * @brief   Write a 32-bit integer value.
             * @param   value   The value to write.
             */
            virtual void writeInt32(int32_t value) = 0 ;

            /**
             * @brief   Write a 64-bit integer value.
             * @param   value   The value to write.
             */
            virtual void writeInt64(int64_t value) = 0 ;

            /**
             * @brief   Write a 32-bit float value.
             * @param   value   The value to write.
             */
            virtual void writeFloat(float value) = 0 ;

            /**
             * @brief   Write a 64-bit float value.
             * @param   value   The value to write.
             */
            virtual void writeDouble(double value) = 0 ;

            /**
             * @brief   Write a string byte by byte.
             * @param   text    Text to write in the File.
             * @param   length  Length of the string in byte.
             */
            virtual void writeString(
                                    const char* text,
                                    const unsigned int length
                                   ) = 0 ;

            /**
             * @brief   Write a string byte by byte.
             * @param   text    Text to write in the File.
             */
            virtual void writeString(
                                    const std::string& text
                                   ) = 0 ;
    } ;

} ;


#endif
