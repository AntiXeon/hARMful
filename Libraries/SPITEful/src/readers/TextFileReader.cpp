#include <readers/TextFileReader.h>
#include <SPITEStrings.h>
#include <debug/Test.h>


namespace Spite {

                                              /** CONSTRUCTION / DESTRUCTION **/
    TextFileReader::TextFileReader() : FileReader() {}

    TextFileReader::~TextFileReader() {}


                                                             /*** UTILITIES ***/
    std::string& TextFileReader::readLine(std::string& readLine) {
        ABORT_CONDITION(
                        (!m_stream -> eof()),
                        ReaderMsg::Error::EndOfFile
                       ) ;

        getline(*m_stream, readLine) ;
        return readLine ;
    }

} ;
