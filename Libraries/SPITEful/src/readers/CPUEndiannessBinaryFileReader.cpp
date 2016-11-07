#include <readers/CPUEndiannessBinaryFileReader.h>
#include <SPITEStrings.h>
#include <debug/Test.h>


namespace Spite {

                                              /** CONSTRUCTION / DESTRUCTION **/
    CPUEndiannessBinaryFileReader::CPUEndiannessBinaryFileReader() : BinaryFileReader() {}

    CPUEndiannessBinaryFileReader::~CPUEndiannessBinaryFileReader() {}


                                                             /*** UTILITIES ***/
    int8_t CPUEndiannessBinaryFileReader::readChar() {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        ReaderMsg::Error::EndOfFile
                       ) ;

        int8_t tmp ;
        m_stream -> read((char*) &tmp, sizeof(tmp)) ;
        return tmp ;
    }

    int16_t CPUEndiannessBinaryFileReader::readShort() {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        ReaderMsg::Error::EndOfFile
                       ) ;

        int16_t tmp ;
        m_stream -> read((char*) &tmp, sizeof(tmp)) ;
        return tmp ;
    }

    int32_t CPUEndiannessBinaryFileReader::readInt32() {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        ReaderMsg::Error::EndOfFile
                       ) ;

        int32_t tmp ;
        m_stream -> read((char*) &tmp, sizeof(tmp)) ;
        return tmp ;
    }

    int64_t CPUEndiannessBinaryFileReader::readInt64() {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        ReaderMsg::Error::EndOfFile
                       ) ;

        int64_t tmp ;
        m_stream -> read((char*) &tmp, sizeof(tmp)) ;
        return tmp ;
    }


    float CPUEndiannessBinaryFileReader::readFloat() {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        ReaderMsg::Error::EndOfFile
                       ) ;

        float tmp ;
        m_stream -> read((char*) &tmp, sizeof(tmp)) ;
        return tmp ;
    }

    double CPUEndiannessBinaryFileReader::readDouble() {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        ReaderMsg::Error::EndOfFile
                       ) ;

        double tmp ;
        m_stream -> read((char*) &tmp, sizeof(tmp)) ;
        return tmp ;
    }


    void CPUEndiannessBinaryFileReader::readString(
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

    void CPUEndiannessBinaryFileReader::readString(
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

} ;
