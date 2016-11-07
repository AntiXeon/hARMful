#include <readers/ReversedCPUEndiannessBinaryFileReader.h>
#include <SPITEStrings.h>
#include <debug/Test.h>


namespace Spite {

                                              /** CONSTRUCTION / DESTRUCTION **/
    ReversedCPUEndiannessBinaryFileReader::ReversedCPUEndiannessBinaryFileReader() : BinaryFileReader() {}

    ReversedCPUEndiannessBinaryFileReader::~ReversedCPUEndiannessBinaryFileReader() {}


                                                             /*** UTILITIES ***/
    int8_t ReversedCPUEndiannessBinaryFileReader::readChar() {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        ReaderMsg::Error::EndOfFile
                       ) ;

        int8_t tmp ;
        m_stream -> read((char*) &tmp, sizeof(tmp)) ;
        return tmp ;
    }

    int16_t ReversedCPUEndiannessBinaryFileReader::readShort() {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        ReaderMsg::Error::EndOfFile
                       ) ;

        int16_t tmp ;
        m_stream -> read((char*) &tmp, sizeof(tmp)) ;

        // Switch bytes for good endianness [HIGH | LOW] --> [LOW | HIGH]
        int16_t little = ((tmp << 8) | (tmp >> 8)) ;
        return little ;
    }

    int32_t ReversedCPUEndiannessBinaryFileReader::readInt32() {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        ReaderMsg::Error::EndOfFile
                       ) ;

        int32_t tmp ;
        m_stream -> read((char*) &tmp, sizeof(tmp)) ;
        return swapInt32(tmp) ;
    }

    int64_t ReversedCPUEndiannessBinaryFileReader::readInt64() {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        ReaderMsg::Error::EndOfFile
                       ) ;

        int64_t tmp ;
        m_stream -> read((char*) &tmp, sizeof(tmp)) ;
        return swapInt64(tmp) ;
    }


    float ReversedCPUEndiannessBinaryFileReader::readFloat() {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        ReaderMsg::Error::EndOfFile
                       ) ;

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

    double ReversedCPUEndiannessBinaryFileReader::readDouble() {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        ReaderMsg::Error::EndOfFile
                       ) ;

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


    void ReversedCPUEndiannessBinaryFileReader::readString(
                                                           char string[],
                                                           const unsigned int length
                                                          ) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        ReaderMsg::Error::EndOfFile
                       ) ;

        for (unsigned int index = 0 ; index < length ; ++index) {
            m_stream -> read((char*) &string[index], sizeof(char)) ;
        }
    }

    void ReversedCPUEndiannessBinaryFileReader::readString(
                                                           std::string& buffer,
                                                           const unsigned int length
                                                          ) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        ReaderMsg::Error::EndOfFile
                       ) ;

        buffer.clear() ;
        buffer.reserve(length) ;

        char read ;
        for (unsigned int index = 0 ; index < length ; ++index) {
            m_stream -> read((char*) &read, sizeof(read)) ;
            buffer.push_back(read) ;
        }
    }


    int32_t ReversedCPUEndiannessBinaryFileReader::swapInt32(int32_t value) {
        // Switch bytes for good endianness:
        // [ 1 | 2 | 3 | 4 ] --> [ 4 | 3 | 2 | 1 ]
        return ((value & 0x000000FF) << 24
                    | (value & 0x0000FF00) << 8
                    | (value & 0x00FF0000) >> 8
                    | (value & 0xFF000000) >> 24) ;
    }

    int64_t ReversedCPUEndiannessBinaryFileReader::swapInt64(int64_t value) {
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
