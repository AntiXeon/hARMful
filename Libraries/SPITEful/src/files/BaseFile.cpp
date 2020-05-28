#include <files/BaseFile.hpp>
#include <interfaces/IFileData.hpp>
#include <SPITEStrings.hpp>
#include <utils/LogSystem.hpp>
#include <ios>
#include <filesystem>
#include <stdexcept>

using namespace Spite ;
namespace fs = std::filesystem ;

BaseFile::BaseFile(const std::string& filepath)
    : File(filepath) {}

BaseFile::~BaseFile() {
    close() ;
}

bool BaseFile::save(
    IFileData* filedata,
    const std::string& path
) {
    if (m_stdOpenMode & std::fstream::out) {
        return saveSpecific(filedata, path) ;
    }
    else {
        throw std::ios_base::failure(
            FileMsg::Error::CannotSaveFile
                + path
                + FileMsg::Error::NoOutputMode
        ) ;
    }
}

bool BaseFile::load(IFileData* filedata) {
    if (m_stdOpenMode & std::fstream::in) {
        return loadSpecific(filedata) ;
    }
    else {
        throw std::ios_base::failure(
            FileMsg::Error::CannotReadFile
                + fs::absolute(m_path).string()
                + FileMsg::Error::NoInputMode
        ) ;
    }
}

void BaseFile::openImpl(File::OpenMode mode) {
    std::ios_base::openmode specificOpenMode ;
    std::ios_base::openmode finalOpenMode ;

    if (hasSpecificMode(specificOpenMode)) {
        finalOpenMode = defineOpenMode(mode) | specificOpenMode ;
    }
    else {
        finalOpenMode = defineOpenMode(mode) ;
    }

    open_fs(finalOpenMode) ;
}

void BaseFile::closeImpl() {
    if (m_fs.is_open()) {
        m_fs.close() ;
    }
}

void BaseFile::open_fs(std::ios_base::openmode mode) {
    // Only a valid BaseFile can be opened.
    if (!isValid()) {
        // Log error.
        Doom::LogSystem::WriteLine(
            Doom::LogSystem::Gravity::Error,
            FileMsg::Error::InsufficientMemory,
            fs::absolute(m_path).string().c_str()
         ) ;

        return ;
    }

    // If so, open it if not already accessed.
    if (!m_fs.is_open()) {
        // If it is all OK, open the file with wanted mode.
        m_fs.open(fs::absolute(m_path).string().c_str(), mode) ;

        if (!m_fs.good()) {
            m_fs.close() ;

            throw std::ios_base::failure(
                FileMsg::Error::FailureOnOpening
                     + fs::absolute(m_path).string()
            ) ;
        }
        else {
            m_stdOpenMode = mode ;

            // Internally set the filestream to the FileReader.
            FileReader* fileReader = defineFileReader() ;
            fileReader -> setFileStream(&m_fs) ;
            // Internally set the filestream to the FileWriter.
            FileWriter* fileWriter = defineFileWriter() ;
            fileWriter -> setFileStream(&m_fs) ;
        }
    }
}

std::ios_base::openmode BaseFile::defineOpenMode(File::OpenMode mode) {
    switch (mode) {
        case File::OpenMode::Open_ReadOnly :
            return std::fstream::in ;

        case File::OpenMode::Open_Append :
            return std::fstream::app ;

        case File::OpenMode::Open_WriteOnly :
            return std::fstream::out ;

        case File::OpenMode::Open_WriteAppend :
            return std::fstream::out | std::fstream::app ;

        case File::OpenMode::Open_ReadWrite :
            return std::fstream::in | std::fstream::out ;

        case File::OpenMode::Open_ReadAppend :
            return std::fstream::in | std::fstream::app ;

        default:
            throw std::logic_error(FileMsg::Error::UnknownAccessMode) ;
    }
}

std::ios_base::openmode BaseFile::openMode() const {
    return m_stdOpenMode ;
}
