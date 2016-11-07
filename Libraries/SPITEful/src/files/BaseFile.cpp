#include <files/BaseFile.h>
#include <SPITEStrings.h>
#include <debug/Test.h>
#include <debug/Log.h>


namespace Spite {

    BaseFile::BaseFile(const std::string& filepath) : File(filepath) {}

    BaseFile::~BaseFile() {
        close() ;
    }


                                                             /*** UTILITIES ***/
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
                       ) throw(Doom::IOException) {
        if (m_openMode & std::fstream::out) {
            return saveSpecific(filedata, path) ;
        }
        else {
            ThrowException(
                           Doom::IOException,
                           FileMsg::Error::CannotSaveFile
                                + path
                                + FileMsg::Error::NoOutputMode
                          ) ;
        }
    }

    bool BaseFile::load(IFileData* filedata) throw(Doom::IOException) {
        if (m_openMode & std::fstream::in) {
            return loadSpecific(filedata) ;
        }
        else {
            ThrowException(
                           Doom::IOException,
                           FileMsg::Error::CannotReadFile
                                + m_path.getAbsolutePath()
                                + FileMsg::Error::NoInputMode
                          ) ;
        }
    }


    void BaseFile::open(std::ios_base::openmode mode) throw(Doom::IOException) {
        // Only a valid BaseFile can be opened.
        if (!isValid()) {
            Doom::Log::Write(
                             Doom::Log::LogWarning,
                             FileMsg::Error::InsufficientMemory,
                             m_path.getAbsolutePath().c_str()
                            ) ;

            return ;
        }

        // If so, open it if not already accessed.
        if (!isOpen()) {
            // If it is all OK, open the file with wanted mode.
            m_fs.open(m_path.getAbsolutePath().c_str(), mode) ;

            if (!m_fs.good()) {
                m_fs.close() ;
                ThrowException(
                               Doom::IOException,
                               FileMsg::Error::FailureOnOpening
                                    + m_path.getAbsolutePath()
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


    std::ios_base::openmode BaseFile::defineOpenMode(File::OpenMode mode) throw(Doom::UnexpectedValueException) {
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
                ThrowException(
                               Doom::UnexpectedValueException,
                               FileMsg::Error::UnknownAccessMode
                              ) ;
        }
    }


                                                               /*** GETTERS ***/
    bool BaseFile::isOpen() const {
        return m_fs.is_open() ;
    }

    std::ios_base::openmode BaseFile::getOpenMode() const {
        return m_openMode ;
    }

} ;
