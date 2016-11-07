#ifndef __SPITE_CPU_ENDIANNESS_BINARY_FILE_WRITER__
#define __SPITE_CPU_ENDIANNESS_BINARY_FILE_WRITER__


#include <writers/BinaryFileWriter.h>


namespace Spite {

    /**
     * @brief   A CPUEndiannessBinaryFileWriter can write data in binary files
     *          using the same endianness than the processor.
     *
     * @author  Denis CARLUS
     * @version 1.0     08/25/2015
     */
    class CPUEndiannessBinaryFileWriter : public BinaryFileWriter {
        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /** @brief  Creation of a CPUEndiannessBinaryFileWriter. */
            CPUEndiannessBinaryFileWriter() ;

            /** @brief  Destruction of a CPUEndiannessBinaryFileWriter. */
            ~CPUEndiannessBinaryFileWriter() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Write a 8-bit integer value.
             * @param   value   The value to write.
             */
            void writeChar(int8_t value) ;

            /**
             * @brief   Write a 16-bit integer value.
             * @param   value   The value to write.
             */
            void writeShort(int16_t value) ;

            /**
             * @brief   Write a 32-bit integer value.
             * @param   value   The value to write.
             */
            void writeInt32(int32_t value) ;

            /**
             * @brief   Write a 64-bit integer value.
             * @param   value   The value to write.
             */
            void writeInt64(int64_t value) ;

            /**
             * @brief   Write a 32-bit float value.
             * @param   value   The value to write.
             */
            void writeFloat(float value) ;

            /**
             * @brief   Write a 64-bit float value.
             * @param   value   The value to write.
             */
            void writeDouble(double value) ;

            /**
             * @brief   Write a string byte by byte.
             * @param   text    Text to write in the File.
             * @param   length  Length of the string in byte.
             */
            void writeString(
                             const char* text,
                             const unsigned int length
                            ) ;

            /**
             * @brief   Write a string byte by byte.
             * @param   text    Text to write in the File.
             */
            void writeString(const std::string& text) ;
    } ;

} ;


#endif
