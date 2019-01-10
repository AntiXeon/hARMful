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

void BaseFile::open(File::OpenMode mode) {
    std::ios_base::openmode specificOpenMode ;
    std::ios_base::openmode finalOpenMode ;

    if (hasSpecificMode(specificOpenMode)) {
        finalOpenMode = defineOpenMode(mode) | specificOpenMode ;
    }
    else {
        finalOpenMode = defineOpenMode(mode) ;
    }

    open(finalOpenMode) ;
}

void BaseFile::close() {
    if (isOpen()) {
        m_fs.close() ;
    }
}

bool BaseFile::save(
    IFileData* filedata,
    const std::string& path
) {
    if (m_openMode & std::fstream::out) {
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
    if (m_openMode & std::fstream::in) {
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

void BaseFile::open(std::ios_base::openmode mode) {
    // Only a valid BaseFile can be opened.
    if (!isValid()) {
        // Log error.
        std::weak_ptr<Doom::LogSystem> logWeakPtr = Doom::LogSystem::GetInstance() ;
        std::shared_ptr<Doom::LogSystem> logSystem = logWeakPtr.lock() ;

        if (!logSystem) {
            return ;
        }

        logSystem -> writeLine(
            Doom::LogSystem::Gravity::Error,
            FileMsg::Error::InsufficientMemory,
            fs::absolute(m_path).string().c_str()
         ) ;

        return ;
    }

    // If so, open it if not already accessed.
    if (!isOpen()) {
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
            m_openMode = mode ;

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
        case File::Open_ReadOnly :
            return std::fstream::in ;

        case File::Open_Append :
            return std::fstream::app ;

        case File::Open_WriteOnly :
            return std::fstream::out ;

        case File::Open_ReadWrite :
            return std::fstream::in | std::fstream::out ;

        case File::Open_ReadAppend :
            return std::fstream::in | std::fstream::app ;

        default:
            throw std::logic_error(FileMsg::Error::UnknownAccessMode) ;
    }
}

bool BaseFile::isOpen() const {
    return m_fs.is_open() ;
}

std::ios_base::openmode BaseFile::openMode() const {
    return m_openMode ;
}
