#include <Path.h>
#include <SPITEStrings.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <vector>
#include <Platform.h>
#include <debug/Log.h>
#include <debug/Test.h>
#include <utils/String.h>


namespace Spite {
                                              /** CONSTRUCTION / DESTRUCTION **/
    Path::Path() {}

    Path::Path(const std::string& filepath) {
        if (filepath.size() > 0) {
            convertToAbsolutePath(filepath) ;
            extractFilenameAndExtension() ;
        }
    }

    Path::~Path() {}


                                                               /*** GETTERS ***/
    const std::string& Path::getAbsolutePath() const {
        return m_absolutePath ;
    }

    const std::string& Path::getFilename() const {
        return m_filename ;
    }

    const std::string& Path::getExtension() const {
        return m_extension ;
    }


                                                             /*** UTILITIES ***/
#ifdef ON_UNIX
    void Path::GetCurrentDirectory(std::string& outCWD) {
        char cwd[256] ;

        errno = 0 ;
        getcwd(cwd, 256) ;
        STOP_ON_ERRNO() ;

        outCWD.assign(cwd) ;
    }

    void Path::convertToAbsolutePath(const std::string& filepath) {
        if (filepath[0] != '/') {
            // Optimization of the string construction to avoid reallocations
            m_absolutePath.reserve(256) ;

            // Split the string with the path separator characters (either "/"
            // or "\" according to OSes).
            std::vector<std::string> partsRelativePath ;
            Doom::String::Split(filepath, "/\\", partsRelativePath) ;


            // Get the absolute path to the directory from which the software is
            // launched. This will be used as a base to generate the full path
            // from the given relative one (filepath variable).
            std::string currentDirectory ;
            GetCurrentDirectory(currentDirectory) ;

            // Split the absolute path to software to create the absolute path
            // from relative one (removing ./ and ../, etc).
            std::vector<std::string> partsAbsolutePath ;
            Doom::String::Split(currentDirectory, "/\\", partsAbsolutePath) ;


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
            Doom::String::Split(filepath, "/\\", parts) ;

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
#else
    void Path::convertToAbsolutePath(const std::string& filepath) {
        ABORT_CONDITION(false, FileMsg::Error::UnsupportedPlatform) ;
    }
#endif


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

} ;
