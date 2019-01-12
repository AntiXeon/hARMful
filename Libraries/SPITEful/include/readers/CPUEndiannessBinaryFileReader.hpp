#ifndef __SPITE__CPU_ENDIANNESS_BINARY_FILE_READER__
#define __SPITE__CPU_ENDIANNESS_BINARY_FILE_READER__

#include <readers/BinaryFileReader.hpp>

namespace Spite {

    /**
     * A CPUEndiannessBinaryFileReader can read data from binary files written
     * using the same endianness than the processor.
     */
    class CPUEndiannessBinaryFileReader : public BinaryFileReader {
        public:
            /**
             * Read a 8-bit integer value.
             * @return  The read value.
             */
            int8_t readChar() {
                int8_t tmp ;
                char* buffer = static_cast<char*> &tmp ;
                m_stream -> read(buffer, sizeof(tmp)) ;
                return tmp ;
            }

            /**
             * Read a 16-bit integer value.
             * @return  The read value.
             */
            int16_t readShort() {
                int16_t tmp ;
                m_stream -> read((char*) &tmp, sizeof(tmp)) ;
                return tmp ;
            }

            /**
             * Read a 32-bit integer value.
             * @return  The read value.
             */
            int32_t readInt32() {
                int32_t tmp ;
                m_stream -> read((char*) &tmp, sizeof(tmp)) ;
                return tmp ;
            }

            /**
             * Read a 64-bit integer value.
             * @return  The read value.
             */
            int64_t readInt64() {
                int64_t tmp ;
                m_stream -> read((char*) &tmp, sizeof(tmp)) ;
                return tmp ;
            }

            /**
             * Read a 32-bit float value.
             * @return  The read value.
             */
            float readFloat() {
                float tmp ;
                m_stream -> read((char*) &tmp, sizeof(tmp)) ;
                return tmp ;
            }

            /**
             * Read a 64-bit float value.
             * @return  The read value.
             */
            double readDouble() {
                double tmp ;
                m_stream -> read((char*) &tmp, sizeof(tmp)) ;
                return tmp ;
            }

            /**
             * Read a string byte by byte.
             * @param   string  Buffer to store the content of the string.
             * @param   length  Length of the string in byte.
             * @warning No null character inserted at the end of the string.
             */
            void readString(char string[], const unsigned int length) {
                for (unsigned int index = 0 ; index < length ; ++index) {
                    m_stream -> read((char*) &string[index], sizeof(char)) ;
                }
            }

            /**
             * Read a string byte by byte.
             * @param   buffer  Buffer to store the characters of the string.
             * @param   length  Length of the string in byte.
             */
            void readString(std::string& buffer, const unsigned int length) {
                buffer.clear() ;
                buffer.reserve(length) ;

                char read ;
                for (unsigned int index = 0 ; index < length ; ++index) {
                    m_stream -> read((char*) &read, sizeof(read)) ;
                    buffer.push_back(read) ;
                }
            }
    } ;
}

#endif
