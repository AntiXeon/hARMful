#ifndef __SPITE__CPU_ENDIANNESS_BINARY_FILE_WRITER__
#define __SPITE__CPU_ENDIANNESS_BINARY_FILE_WRITER__

#include <writers/BinaryFileWriter.hpp>

namespace Spite {

    /**
     * A CPUEndiannessBinaryFileWriter can write data in binary files using the
     * same endianness than the processor.
     */
    class CPUEndiannessBinaryFileWriter : public BinaryFileWriter {
        public:
            /**
             * Write a 8-bit integer value.
             * @param   value   The value to write.
             */
            void writeChar(int8_t value) {
                m_stream -> write((char*) &value, sizeof(value)) ;
            }

            /**
             * Write a 16-bit integer value.
             * @param   value   The value to write.
             */
            void writeShort(int16_t value) {
                m_stream -> write((char*) &value, sizeof(value)) ;
            }

            /**
             * Write a 32-bit integer value.
             * @param   value   The value to write.
             */
            void writeInt32(int32_t value) {
                m_stream -> write((char*) &value, sizeof(value)) ;
            }

            /**
             * Write a 64-bit integer value.
             * @param   value   The value to write.
             */
            void writeInt64(int64_t value) {
                m_stream -> write((char*) &value, sizeof(value)) ;
            }

            /**
             * Write a 32-bit float value.
             * @param   value   The value to write.
             */
            void writeFloat(float value) {
                m_stream -> write((char*) &value, sizeof(value)) ;
            }

            /**
             * Write a 64-bit float value.
             * @param   value   The value to write.
             */
            void writeDouble(double value) {
                m_stream -> write((char*) &value, sizeof(value)) ;
            }

            /**
             * Write a string byte by byte.
             * @param   text    Text to write in the File.
             * @param   length  Length of the string in byte.
             */
            void writeString(
                const char* text,
                const unsigned int length
            ) {
                for (unsigned int index = 0 ; index < length ; ++index) {
                    m_stream -> write((char*) &text[index], sizeof(char)) ;
                }
            }

            /**
             * Write a string byte by byte.
             * @param   text    Text to write in the File.
             */
            void writeString(const std::string& text) {
                size_t length = text.size() ;
                for (unsigned int index = 0 ; index < length ; ++index) {
                    m_stream -> write((char*) &text[index], sizeof(char)) ;
                }
            }
    } ;
}

#endif
