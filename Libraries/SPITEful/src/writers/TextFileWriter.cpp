#include <writers/TextFileWriter.h>
#include <SPITEStrings.h>
#include <debug/Test.h>


namespace Spite {

                                              /** CONSTRUCTION / DESTRUCTION **/
    TextFileWriter::TextFileWriter() : FileWriter() {}

    TextFileWriter::~TextFileWriter() {}


                                                             /*** UTILITIES ***/
    void TextFileWriter::write(const std::string& text) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        WriterMsg::Error::EndOfFile
                       ) ;

        (*m_stream) << text ;
    }

} ;
