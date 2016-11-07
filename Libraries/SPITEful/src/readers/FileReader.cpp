#include <readers/FileReader.h>


namespace Spite {

                                              /** CONSTRUCTION / DESTRUCTION **/
    FileReader::FileReader() {}

    FileReader::~FileReader() {}


                                                               /*** SETTERS ***/
    void FileReader::setFileStream(const std::fstream* stream) {
        m_stream = (std::fstream*) stream ;
    }

} ;
