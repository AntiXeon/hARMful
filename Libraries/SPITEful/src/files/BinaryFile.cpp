#include <files/BinaryFile.hpp>
#include <readers/CPUEndiannessBinaryFileReader.hpp>
#include <readers/ReversedCPUEndiannessBinaryFileReader.hpp>
#include <writers/CPUEndiannessBinaryFileWriter.hpp>
#include <writers/ReversedCPUEndiannessBinaryFileWriter.hpp>
#include <utils/LogSystem.hpp>
#include <SPITEStrings.hpp>
#include <filesystem>

using namespace Spite ;
namespace fs = std::filesystem ;

BinaryFile::BinaryFile(
    const std::string& filepath,
    const bool isCPUEndian
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
    catch(std::bad_alloc&) {
        // Log error.
        std::weak_ptr<Doom::LogSystem> logWeakPtr = Doom::LogSystem::GetInstance() ;
        std::shared_ptr<Doom::LogSystem> logSystem = logWeakPtr.lock() ;

        if (!logSystem) {
            return ;
        }

        logSystem -> writeLine(
            Doom::LogSystem::Gravity::Error,
            FileMsg::Error::InsufficientMemory,
            fs::absolute(filepath).string().c_str()
        ) ;
    }
}

BinaryFile::~BinaryFile() {
    if (m_reader != nullptr) {
        delete m_reader ;
    }

    if (m_writer != nullptr) {
        delete m_writer ;
    }
}

bool BinaryFile::isValid() const {
    return ((m_reader != nullptr) && (m_writer != nullptr)) ;
}

bool BinaryFile::hasSpecificMode(std::ios_base::openmode& mode) {
    mode = std::ios::binary ;
    return true ;
}

FileReader* BinaryFile::defineFileReader() {
    return m_reader ;
}

FileWriter* BinaryFile::defineFileWriter() {
    return m_writer ;
}
