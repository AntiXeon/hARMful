#include <writers/ReversedCPUEndiannessBinaryFileWriter.h>
#include <SPITEStrings.h>
#include <debug/Test.h>


namespace Spite {

                                              /** CONSTRUCTION / DESTRUCTION **/
    ReversedCPUEndiannessBinaryFileWriter::ReversedCPUEndiannessBinaryFileWriter() : BinaryFileWriter() {}

    ReversedCPUEndiannessBinaryFileWriter::~ReversedCPUEndiannessBinaryFileWriter() {}


                                                             /*** UTILITIES ***/
    void ReversedCPUEndiannessBinaryFileWriter::writeChar(int8_t value) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        STR_ERROR__WRITERS__EOF
                       ) ;

        m_stream -> write((char*) &value, sizeof(value)) ;
    }

    void ReversedCPUEndiannessBinaryFileWriter::writeShort(int16_t value) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        STR_ERROR__WRITERS__EOF
                       ) ;

        value = ((value << 8) | (value >> 8)) ;
        m_stream -> read((char*) &value, sizeof(value)) ;
    }

    void ReversedCPUEndiannessBinaryFileWriter::writeInt32(int32_t value) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        STR_ERROR__WRITERS__EOF
                       ) ;

        value = swapInt32(value) ;
        m_stream -> read((char*) &value, sizeof(value)) ;
    }

    void ReversedCPUEndiannessBinaryFileWriter::writeInt64(int64_t value) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        STR_ERROR__WRITERS__EOF
                       ) ;

        value = swapInt64(value) ;
        m_stream -> read((char*) &value, sizeof(value)) ;
    }


    void ReversedCPUEndiannessBinaryFileWriter::writeFloat(float value) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        STR_ERROR__WRITERS__EOF
                       ) ;

        // Union used to swap the float value bytes.
        union SwapEndianness {
            float fValue ;
            int32_t iValue ;
        } swapper ;

        swapper.fValue = value ;
        // Swap its bytes.
        swapper.iValue = swapInt32(swapper.iValue) ;

        m_stream -> read((char*) &swapper.iValue, sizeof(swapper.iValue)) ;
    }

    void ReversedCPUEndiannessBinaryFileWriter::writeDouble(double value) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        STR_ERROR__WRITERS__EOF
                       ) ;

        // Union used to swap the float value bytes.
        union SwapEndianness {
            double dValue ;
            int64_t lValue ;
        } swapper ;

        swapper.dValue = value ;
        // Swap its bytes.
        swapper.lValue = swapInt64(swapper.lValue) ;

        m_stream -> read((char*) &swapper.lValue, sizeof(swapper.lValue)) ;
    }


    void ReversedCPUEndiannessBinaryFileWriter::writeString(
                                                            const char* text,
                                                            const unsigned int length
                                                           ) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        STR_ERROR__WRITERS__EOF
                       ) ;

        for (unsigned int index = 0 ; index < length ; ++index) {
            m_stream -> write((char*) &text[index], sizeof(char)) ;
        }
    }

    void ReversedCPUEndiannessBinaryFileWriter::writeString(const std::string& text) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        STR_ERROR__WRITERS__EOF
                       ) ;

        size_t length = text.size() ;
        for (unsigned int index = 0 ; index < length ; ++index) {
            m_stream -> write((char*) &text[index], sizeof(char)) ;
        }
    }


    int32_t ReversedCPUEndiannessBinaryFileWriter::swapInt32(int32_t value) {
        // Switch bytes for good endianness:
        // [ 1 | 2 | 3 | 4 ] --> [ 4 | 3 | 2 | 1 ]
        return ((value & 0x000000FF) << 24
                    | (value & 0x0000FF00) << 8
                    | (value & 0x00FF0000) >> 8
                    | (value & 0xFF000000) >> 24) ;
    }

    int64_t ReversedCPUEndiannessBinaryFileWriter::swapInt64(int64_t value) {
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
