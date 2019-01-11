#include <files/TextFile.hpp>

using namespace Spite ;

TextFile::TextFile(const std::string& filepath)
    : BaseFile(filepath) {}

bool TextFile::isValid() const {
    return true ;
}

bool TextFile::hasSpecificMode(std::ios_base::openmode&) {
    return false ;
}

FileReader* TextFile::defineFileReader() {
    return &m_reader ;
}

FileWriter* TextFile::defineFileWriter() {
    return &m_writer ;
}
