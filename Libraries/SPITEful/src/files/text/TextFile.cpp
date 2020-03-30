#include <files/text/TextFile.hpp>
#include <files/text/TextData.hpp>
#include <utils/LogSystem.hpp>
#include <SPITEStrings.hpp>

using namespace Spite ;

TextFile::TextFile(const std::string& filepath)
    : BaseFile(filepath) {}

bool TextFile::isValid() const {
    return true ;
}

bool TextFile::saveSpecific(
    IFileData* filedata,
    const std::string& /*path*/
) {
    TextData* textData = static_cast<TextData*>(filedata) ;
    m_writer.clear() ;
    m_writer.write(textData -> toString()) ;
    return true ;
}

bool TextFile::loadSpecific(IFileData* filedata) {
    TextData* textData = static_cast<TextData*>(filedata) ;
    std::string content ;
    m_reader.readAll(content) ;
    textData -> setData(content) ;
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
