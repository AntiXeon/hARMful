#include <files/TextFile.h>


namespace Spite {

                                              /** CONSTRUCTION / DESTRUCTION **/
    TextFile::TextFile(const std::string& filepath) : BaseFile(filepath) {}

    TextFile::~TextFile() {}


                                                               /*** GETTERS ***/
    bool TextFile::isValid() const {
        return true ;
    }


                                                             /*** UTILITIES ***/
    bool TextFile::hasSpecificMode(std::ios_base::openmode&) {
        return false ;
    }

    FileReader* TextFile::defineFileReader() {
        return &m_reader ;
    }

    FileWriter* TextFile::defineFileWriter() {
        return &m_writer ;
    }

} ;
