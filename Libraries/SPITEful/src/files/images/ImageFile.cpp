#include <files/images/ImageFile.hpp>
#include <debug/ErrorsManagement.hpp>
#include <SPITEStrings.hpp>
#include <ios>
#include <filesystem>
#include <string>
#include <cstring>

using namespace Spite ;
namespace fs = std::filesystem ;

// ifstream is not possible as underlying libraries are written in C. So...
#ifdef WindowsPlatform
    #define OpenFile(desc, path, mode)    fopen_s(&desc, path, mode)
#else
    #define OpenFile(desc, path, mode)    desc = fopen(path, mode)
#endif

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
            OpenFile(m_file, filepath, "rb") ;
            break ;

        case File::Open_Append:
            OpenFile(m_file, filepath, "ab") ;
            break ;

        case File::Open_WriteOnly:
            OpenFile(m_file, filepath, "wb") ;
            break ;

        case File::Open_ReadWrite:
            OpenFile(m_file, filepath, "rb+") ;
            break ;

        case File::Open_ReadAppend:
            OpenFile(m_file, filepath, "ab+") ;
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
