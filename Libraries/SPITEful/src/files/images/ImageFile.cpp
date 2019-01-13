#include <files/images/ImageFile.hpp>
#include <SPITEStrings.hpp>
#include <cstdio>
#include <ios>
#include <filesystem>
#include <string.h>

using namespace Spite ;
namespace fs = std::filesystem ;

ImageFile::ImageFile(const std::string& path)
    : File(path),
      m_file(nullptr),
      m_dataPosition(0) {}

ImageFile::~ImageFile() {
    m_dataPosition = 0 ;

    if (m_file != nullptr) {
        close() ;
    }
}

bool ImageFile::load(IFileData* output) {
    open(File::Open_ReadOnly) ;

    if (m_file == nullptr) {
        throw std::ios_base::failure(
            FileMsg::Error::UnableToOpen
             + fs::absolute(m_path).string()
        ) ;
    }

    RawImage* rawImage = dynamic_cast<RawImage*>(output) ;
    return parse(rawImage) ;
}

bool ImageFile::save(
    IFileData*,
    const std::string&
) {
    // Needs implementation!
    return false ;
}


void ImageFile::open(OpenMode mode) {
    const char* filepath = fs::absolute(m_path).string().c_str() ;

    switch(mode) {
        case File::Open_ReadOnly:
            m_file = fopen(filepath, "rb") ;
            return ;

        case File::Open_Append:
            m_file = fopen(filepath, "ab") ;
            return ;

        case File::Open_WriteOnly:
            m_file = fopen(filepath, "wb") ;
            return ;

        case File::Open_ReadWrite:
            m_file = fopen(filepath, "rb+") ;
            return ;

        case File::Open_ReadAppend:
            m_file = fopen(filepath, "ab+") ;
            return ;

        default:
            m_file = nullptr ;
            return ;
    }
}

void ImageFile::close() {
    fclose(m_file) ;
    m_file = nullptr ;
}


FILE* ImageFile::descriptor() const {
    return m_file ;
}
