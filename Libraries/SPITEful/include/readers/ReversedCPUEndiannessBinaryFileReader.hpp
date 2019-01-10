#ifndef __SPITE__REVERSED_CPU_ENDIANNESS_BINARY_FILE_READER__
#define __SPITE__REVERSED_CPU_ENDIANNESS_BINARY_FILE_READER__

#include <readers/BinaryFileReader.hpp>

namespace Spite {

    /**
     * A ReversedCPUEndiannessBinaryFileReader can read data from binary files
     * written using the other known endianness from the processor.
     * For example, use a ReversedCPUEndiannessBinaryFileReader to read a Big
     * Endian file on a Little Endian CPU.
     */
    class ReversedCPUEndiannessBinaryFileReader : public BinaryFileReader {
        public:
            /**
             * Read a 8-bit integer value.
             * @return  The read value.
             */
            int8_t readChar() {
                int8_t tmp ;
                m_stream -> read((char*) &tmp, sizeof(tmp)) ;
                return tmp ;
            }

            /**
             * Read a 16-bit integer value.
             * @return  The read value.
             */
            int16_t readShort() {
                int16_t tmp ;
                m_stream -> read((char*) &tmp, sizeof(tmp)) ;

                // Switch bytes for good endianness [HIGH | LOW] --> [LOW | HIGH]
                int16_t little = ((tmp << 8) | (tmp >> 8)) ;
                return little ;
            }

            /**
             * Read a 32-bit integer value.
             * @return  The read value.
             */
            int32_t readInt32() {
                int32_t tmp ;
                m_stream -> read((char*) &tmp, sizeof(tmp)) ;
                return swapInt32(tmp) ;
            }

            /**
             * Read a 64-bit integer value.
             * @return  The read value.
             */
            int64_t readInt64() {
                int64_t tmp ;
                m_stream -> read((char*) &tmp, sizeof(tmp)) ;
                return swapInt64(tmp) ;
            }

            /**
             * Read a 32-bit float value.
             * @return  The read value.
             */
            float readFloat() {
                // Union used to swap the float value bytes.
                union SwapEndianness {
                    float fValue ;
                    int32_t iValue ;
                } swapper ;

                // Read the float.
                m_stream -> read((char*) &swapper.fValue, sizeof(swapper.fValue)) ;
                // Swap its bytes.
                swapper.iValue = swapInt32(swapper.iValue) ;
                return swapper.fValue ;
            }

            /**
             * Read a 64-bit float value.
             * @return  The read value.
             */
            double readDouble() {
                // Union used to swap the float value bytes.
                union SwapEndianness {
                    double dValue ;
                    int64_t lValue ;
                } swapper ;

                // Read the float.
                m_stream -> read((char*) &swapper.dValue, sizeof(swapper.dValue)) ;
                // Swap its bytes.
                swapper.lValue = swapInt64(swapper.lValue) ;
                return swapper.dValue ;
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


        private:
            /**
             * Swap the bytes of a 32-bit integer value.
             * @param   value   The value to swap.
             * @return  The swapped value.
             */
            int32_t swapInt32(int32_t value) {
                // Switch bytes for good endianness:
                // [ 1 | 2 | 3 | 4 ] --> [ 4 | 3 | 2 | 1 ]
                return ((value & 0x000000FF) << 24
                            | (value & 0x0000FF00) << 8
                            | (value & 0x00FF0000) >> 8
                            | (value & 0xFF000000) >> 24) ;
            }

            /**
             * Swap the bytes of a 64-bit integer value.
             * @param   value   The value to swap.
             * @return  The swapped value.
             */
            int64_t swapInt64(int64_t value) {
                // Switch bytes for good endianness
                // [ 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 ] --> [ 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 ]
                return ((value & 0x00000000000000FF) << 56
                            | (value & 0x000000000000FF00) << 40
                            | (value & 0x0000000000FF0000) << 24
                            | (value & 0x00000000FF000000) << 8
                            | (value & 0x000000FF00000000) >> 8
                            | (value & 0x0000FF0000000000) >> 24
                            | (value & 0x00FF000000000000) >> 40
                            | (value & 0xFF00000000000000) >> 56) ;
            }
    } ;
}

#endif
