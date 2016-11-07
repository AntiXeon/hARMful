#include <files/BinaryFile.h>
#include <readers/CPUEndiannessBinaryFileReader.h>
#include <readers/ReversedCPUEndiannessBinaryFileReader.h>
#include <writers/CPUEndiannessBinaryFileWriter.h>
#include <writers/ReversedCPUEndiannessBinaryFileWriter.h>
#include <debug/Log.h>
#include <debug/Test.h>
#include <SPITEStrings.h>


namespace Spite {

                                              /** CONSTRUCTION / DESTRUCTION **/
    BinaryFile::BinaryFile(
                           const std::string& filepath,
                           bool isCPUEndian
                          ) : BaseFile(filepath) {
        try {
            if (isCPUEndian) {
                m_reader = new CPUEndiannessBinaryFileReader() ;
                m_writer = new CPUEndiannessBinaryFileWriter() ;
            }
            else {
                m_reader = new ReversedCPUEndiannessBinaryFileReader() ;
                m_writer = new ReversedCPUEndiannessBinaryFileWriter() ;
            }
        }
        catch(std::bad_alloc& e) {
            Doom::Log::Write(
                             Doom::Log::LogError,
                             FileMsg::Error::InsufficientMemory,
                             filepath.c_str()
                            ) ;
            LOG_FILEINFO(Doom::Log::LogError) ;
        }
    }

    BinaryFile::~BinaryFile() {
        if (m_reader != NULL) {
            delete m_reader ;
        }

        if (m_writer != NULL) {
            delete m_writer ;
        }
    }


                                                               /*** GETTERS ***/
    bool BinaryFile::isValid() const {
        return ((m_reader != NULL) && (m_writer != NULL)) ;
    }


                                                             /*** UTILITIES ***/
    bool BinaryFile::hasSpecificMode(std::ios_base::openmode& mode) {
        mode = std::fstream::binary ;
        return true ;
    }

    FileReader* BinaryFile::defineFileReader() {
        return m_reader ;
    }

    FileWriter* BinaryFile::defineFileWriter() {
        return m_writer ;
    }

} ;
