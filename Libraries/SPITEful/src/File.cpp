#include <File.h>
#include <Platform.h>
#include <SPITEStrings.h>
#include <debug/Log.h>
#include <debug/Test.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <utils/String.h>


namespace Spite {

                                              /** CONSTRUCTION / DESTRUCTION **/
#ifdef ON_UNIX
    File::File(const std::string& filepath) {
        // Create the full path to the file.
        m_path = Path(filepath) ;

        // Check if file/path exists and get informations on file if it is the
        // case. stat returns 0 on success, -1 on fail (with errno correctly
        // set).
        errno = 0 ;
        struct stat fileInfos ;
        char failedStat = stat(filepath.c_str(), &fileInfos) ;

        if (!failedStat) {
            if (errno == ENOENT) {
                // At least one element in the path does not exist.
                // Check every part of the path and create right directories
                // until the file.
                createTreeToFile() ;
            }
            else {
                // Another -unhandled- error occured...
                STOP_ON_ERRNO_MSG((FileMsg::Error::UnableToOpen + filepath).c_str()) ;
            }
        }
        else {
            ABORT_CONDITION(
                            (fileInfos.st_mode & S_IFREG),
                            FileMsg::Error::OnlyRegularFiles
                           ) ;
        }
    }
#else
    File::File(const std::string& filepath) {
        ABORT_CONDITION(false, FileMsg::Error::UnsupportedPlatform) ;
    }
#endif

    File::~File() {}


                                                             /*** UTILITIES ***/
    void File::createTreeToFile() {
        std::vector<std::string> parts ;
        Doom::String::Split(m_path.getAbsolutePath(), "/\\", parts) ;

        // Recreate step-by-step the path to the file creating missing folders.
        std::string path ;
        path.reserve(m_path.getAbsolutePath().size()) ;

        bool checkFolder = true ;
        size_t maxIndex = parts.size() - 1 ;
        for (size_t index = 0 ; index < maxIndex ; ++index) {
            path.append("/") ;
            path.append(parts[index]) ;

            // Check if the folder exists.
            if (checkFolder) {
                errno = 0 ;
                struct stat folderInfo ;
                stat(path.c_str(), &folderInfo) ;

                // If the folder does not exist, create it.
                if (errno == ENOENT) {
                    // Do not check anymore if the next folders exist : they
                    // dont as the current one does not exist.
                    // So on next iterations, the check will be bypassed.
                    checkFolder = false ;

                    errno = 0 ;
                    char failedMkDir = mkdir(path.c_str(), 0700) ;

                    if (failedMkDir) {
                        STOP_ON_ERRNO_MSG((FileMsg::Error::MkdirFailed + path).c_str()) ;
                    }
                }
            }
            else {
                errno = 0 ;
                char failedMkDir = mkdir(path.c_str(), 0700) ;

                if (failedMkDir) {
                    STOP_ON_ERRNO_MSG((FileMsg::Error::MkdirFailed + path).c_str()) ;
                }
            }
        }
    }


                                                               /*** GETTERS ***/
    const Path& File::getPath() const {
        return m_path ;
    }

} ;
