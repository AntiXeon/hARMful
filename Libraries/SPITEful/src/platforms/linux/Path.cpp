#ifdef LinuxPlatform

#include <Path.hpp>
#include <SPITEStrings.hpp>
#include <utils/Platform.hpp>
#include <utils/LogSystem.hpp>
#include <utils/StringExt.hpp>
#include <debug/ErrorsManagement.hpp>
#include <cstdlib>
#include <cstddef>
#include <unistd.h>

using namespace Spite;

Path::Path(const std::string& filepath) {
    if (filepath.size() > 0) {
        convertToAbsolutePath(filepath) ;
        extractFilenameAndExtension() ;
    }
}

const std::string& Path::absolutePath() const {
    return m_absolutePath ;
}

const std::string& Path::filename() const {
    return m_filename ;
}

const std::string& Path::extension() const {
    return m_extension ;
}


void Path::CurrentDirectory(std::string& outCWD) {
    char cwd[256] ;

    errno = 0 ;
    static_cast<void>(getcwd(cwd, 256)) ;
    STOP_ON_CERROR() ;

    outCWD.assign(cwd) ;
}

void Path::convertToAbsolutePath(const std::string& filepath) {
    if (filepath[0] != '/') {
        // Optimization of the string construction to avoid reallocations
        m_absolutePath.reserve(256) ;

        // Split the string with the path separator characters (either "/"
        // or "\" according to OSes).
        std::vector<std::string> partsRelativePath ;
        partsRelativePath = Doom::StringExt::Split(filepath, "/\\") ;


        // Get the absolute path to the directory from which the software is
        // launched. This will be used as a base to generate the full path
        // from the given relative one (filepath variable).
        std::string currentDirectory ;
        CurrentDirectory(currentDirectory) ;

        // Split the absolute path to software to create the absolute path
        // from relative one (removing ./ and ../, etc).
        std::vector<std::string> partsAbsolutePath ;
        partsAbsolutePath = Doom::StringExt::Split(currentDirectory, "/\\") ;


        // Parse all the parts of the relative path, removing or adding
        // directories to the absolute base path.
        size_t maxPartIndex = partsRelativePath.size() ;
        for (size_t partIndex = 0 ; partIndex < maxPartIndex ; ++partIndex) {
            if (partsRelativePath[partIndex] == "..") {
                // Previous folder : remove the last element in the splitted
                // absolute path
                partsAbsolutePath.pop_back() ;
            }
            else if (partsRelativePath[partIndex] != ".") {
                // Ignore the current folder character (.).
                partsAbsolutePath.push_back(partsRelativePath[partIndex]) ;
            }
        }

        // Create the full path.
        maxPartIndex = partsAbsolutePath.size() ;
        for (size_t partIndex = 0 ; partIndex < maxPartIndex ; ++partIndex) {
            m_absolutePath.append("/") ;
            m_absolutePath.append(partsAbsolutePath[partIndex]) ;
        }
    }
    else {
        // Optimization of the string construction to avoid reallocations
        m_absolutePath.reserve(256) ;

        // Split the string with the path separator characters (either "/"
        // or "\" according to OSes).
        std::vector<std::string> parts ;
        parts = Doom::StringExt::Split(filepath, "/\\") ;

        // Parse all the parts of the relative path, removing . and ..
        // directories.
        std::vector<std::string>::iterator itPath = parts.begin() ;
        for (; itPath != parts.end() ; ++itPath) {
            if ((*itPath) == ".") {
                itPath = parts.erase(itPath) ;
            }
            else if ((*itPath) == "..") {
                itPath = parts.erase(itPath) ;
                itPath = parts.erase(itPath) ;
            }
        }

        // Create the cleaned full path.
        size_t maxPartIndex = parts.size() ;
        for (size_t partIndex = 0 ; partIndex < maxPartIndex ; ++partIndex) {
            m_absolutePath.append("/") ;
            m_absolutePath.append(parts[partIndex]) ;
        }
    }
}

void Path::extractFilenameAndExtension() {
    std::size_t lastPathCharPosition = m_absolutePath.find_last_of("/\\") ;
    std::size_t extensionPosition = m_absolutePath.find_last_of(".") ;

    // If the extension is found
    if ((extensionPosition != std::string::npos)
            && (extensionPosition > lastPathCharPosition)) {
        // Extract just the name, excluding the extension
        size_t filenameLength = extensionPosition - lastPathCharPosition - 1 ;
        m_filename = m_absolutePath.substr(lastPathCharPosition + 1, filenameLength) ;
        m_extension = m_absolutePath.substr(extensionPosition + 1) ;
    }
    else {
        m_filename = m_absolutePath.substr(lastPathCharPosition) ;
        m_extension.clear() ;
    }
}

#endif
