#include <writers/CPUEndiannessBinaryFileWriter.h>
#include <SPITEStrings.h>
#include <debug/Test.h>


namespace Spite {

                                              /** CONSTRUCTION / DESTRUCTION **/
    CPUEndiannessBinaryFileWriter::CPUEndiannessBinaryFileWriter() : BinaryFileWriter() {}

    CPUEndiannessBinaryFileWriter::~CPUEndiannessBinaryFileWriter() {}


                                                             /*** UTILITIES ***/
    void CPUEndiannessBinaryFileWriter::writeChar(int8_t value) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        WriterMsg::Error::EndOfFile
                       ) ;

        m_stream -> write((char*) &value, sizeof(value)) ;
    }

    void CPUEndiannessBinaryFileWriter::writeShort(int16_t value) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        WriterMsg::Error::EndOfFile
                       ) ;

        m_stream -> write((char*) &value, sizeof(value)) ;
    }

    void CPUEndiannessBinaryFileWriter::writeInt32(int32_t value) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        WriterMsg::Error::EndOfFile
                       ) ;

        m_stream -> write((char*) &value, sizeof(value)) ;
    }

    void CPUEndiannessBinaryFileWriter::writeInt64(int64_t value) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        WriterMsg::Error::EndOfFile
                       ) ;

        m_stream -> write((char*) &value, sizeof(value)) ;
    }


    void CPUEndiannessBinaryFileWriter::writeFloat(float value) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        WriterMsg::Error::EndOfFile
                       ) ;

        m_stream -> write((char*) &value, sizeof(value)) ;
    }

    void CPUEndiannessBinaryFileWriter::writeDouble(double value) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        WriterMsg::Error::EndOfFile
                       ) ;

        m_stream -> write((char*) &value, sizeof(value)) ;
    }


    void CPUEndiannessBinaryFileWriter::writeString(
                                                    const char* text,
                                                    const unsigned int length
                                                   ) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        WriterMsg::Error::EndOfFile
                       ) ;

        for (unsigned int index = 0 ; index < length ; ++index) {
            m_stream -> write((char*) &text[index], sizeof(char)) ;
        }
    }

    void CPUEndiannessBinaryFileWriter::writeString(const std::string& text) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        WriterMsg::Error::EndOfFile
                       ) ;

        size_t length = text.size() ;
        for (unsigned int index = 0 ; index < length ; ++index) {
            m_stream -> write((char*) &text[index], sizeof(char)) ;
        }
    }

} ;
