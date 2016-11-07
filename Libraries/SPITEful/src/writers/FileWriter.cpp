#include <writers/FileWriter.h>


namespace Spite {

                                              /** CONSTRUCTION / DESTRUCTION **/
    FileWriter::FileWriter() {}

    FileWriter::~FileWriter() {}


                                                               /*** SETTERS ***/
    void FileWriter::setFileStream(const std::fstream* stream) {
        m_stream = (std::fstream*) stream ;
    }

} ;
