#include <files/images/ImageFile.hpp>
#include <debug/ErrorsManagement.hpp>
#include <SPITEStrings.hpp>
#include <cstdio>
#include <ios>
#include <filesystem>
#include <string>
#include <cstring>

#include <iostream>

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

void ImageFile::open(OpenMode mode) {
    std::string absolutePath = fs::absolute(m_path).string() ;
    const char* filepath = absolutePath.c_str() ;

    switch(mode) {
        case File::Open_ReadOnly:
            fopen_s(&m_file, filepath, "rb") ;
            break ;

        case File::Open_Append:
            fopen_s(&m_file, filepath, "ab") ;
            break ;

        case File::Open_WriteOnly:
            fopen_s(&m_file, filepath, "wb") ;
            break ;

        case File::Open_ReadWrite:
            fopen_s(&m_file, filepath, "rb+") ;
            break ;

        case File::Open_ReadAppend:
            fopen_s(&m_file, filepath, "ab+") ;
            break ;

        default:
            m_file = nullptr ;
            break ;
    }

    if (!m_file) {
        STOP_ON_CERROR_MSG(filepath) ;
    }
}

void ImageFile::close() {
    fclose(m_file) ;
    m_file = nullptr ;
}

bool ImageFile::load(IFileData* filedata) {
    RawImage* rawImage = dynamic_cast<RawImage*>(filedata) ;
    return parse(rawImage) ;
}

bool ImageFile::save(
    IFileData*,
    const std::string&
) {
    // Needs implementation!
    return false ;
}
