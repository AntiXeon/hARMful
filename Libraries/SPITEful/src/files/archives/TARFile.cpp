#include <files/archives/TARFile.hpp>
#include <utils/LogSystem.hpp>
#include <utils/StringExt.hpp>
#include <SPITEStrings.hpp>
#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem ;
using namespace Spite ;

TARFile::TARFile(const std::string& path)
    : File(path) {}

TARFile::~TARFile() {
    close() ;
}

template <typename T>
bool TARFile::addBinaryFile(
    const std::string& filename,
    const std::vector<T*> bytes
) {
    if (openMode() == File::OpenMode::Open_WriteAppend) {
        int success = 0 ;

        size_t dataLength = bytes.size() * sizeof(T) ;
        auto* bytes = reinterpret_cast<char*>(bytes.data()) ;
        success = mtar_write_file_header(&m_memory, filename.c_str(), dataLength) ;

        if (success != MTAR_ESUCCESS) {
            Doom::LogSystem::WriteLine(
                Doom::LogSystem::Gravity::Error,
                mtar_strerror(success),
                fs::absolute(path()).string()
            ) ;
            return false ;
        }

        success = mtar_write_data(&m_memory, bytes, dataLength) ;

        if (success != MTAR_ESUCCESS) {
            Doom::LogSystem::WriteLine(
                Doom::LogSystem::Gravity::Error,
                mtar_strerror(success),
                fs::absolute(path()).string()
            ) ;
            return false ;
        }

        return true ;
    }
    else {
        return false ;
    }
}

bool TARFile::addText(
    const std::string& filename,
    const std::string& text
) {
    if (openMode() == File::OpenMode::Open_WriteAppend) {
        int success = 0 ;

        size_t textLength = text.size() ;
        success = mtar_write_file_header(&m_memory, filename.c_str(), textLength) ;

        if (success != MTAR_ESUCCESS) {
            Doom::LogSystem::WriteLine(
                Doom::LogSystem::Gravity::Error,
                mtar_strerror(success),
                fs::absolute(path()).string()
            ) ;
            return false ;
        }

        success = mtar_write_data(&m_memory, text.c_str(), textLength) ;

        if (success != MTAR_ESUCCESS) {
            Doom::LogSystem::WriteLine(
                Doom::LogSystem::Gravity::Error,
                mtar_strerror(success),
                fs::absolute(path()).string()
            ) ;
            return false ;
        }

        return true ;
    }
    else {
        return false ;
    }
}


void TARFile::openImpl(File::OpenMode mode) {
    std::string tarOpenMode ;

    switch (mode) {
        case File::OpenMode::Open_ReadOnly:
            tarOpenMode = "r" ;
            break ;

        case File::OpenMode::Open_WriteOnly:
            tarOpenMode = "w" ;
            break ;

        case File::OpenMode::Open_Append:
            tarOpenMode = "a" ;
            break ;

        default:
            throw std::runtime_error(FileMsg::Error::BadAccessMode) ;
    }

    int success = mtar_open(
        &m_memory,
        path().string().c_str(),
        tarOpenMode.c_str()
    ) ;

    if (success != MTAR_ESUCCESS) {
        Doom::LogSystem::WriteLine(
            Doom::LogSystem::Gravity::Error,
            mtar_strerror(success),
            fs::absolute(path()).string()
        ) ;
        close() ;
    }
}

void TARFile::closeImpl() {
    if (m_memory.stream) {
        mtar_finalize(&m_memory) ;
        mtar_close(&m_memory) ;
    }
}
