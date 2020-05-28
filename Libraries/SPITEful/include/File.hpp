#ifndef __SPITE__FILE__
#define __SPITE__FILE__

#include <utils/Platform.hpp>
#include <filesystem>
#include <interfaces/ILoadable.hpp>
#include <interfaces/ISavable.hpp>

namespace Spite {

    /**
     * A File is the representation of a file in file system.
     * A File can be saved and loaded.
     */
    class File : public ILoadable, public ISavable {
        public:
            /**
             * Mode in which the BaseFile can be opened.
             */
            enum class OpenMode {
                Open_None        = 0,
                Open_ReadOnly    = 1,
                Open_Append      = 2,
                Open_WriteOnly   = 4,
                Open_WriteAppend = Open_WriteOnly | Open_Append,
                Open_ReadWrite   = Open_ReadOnly | Open_WriteOnly,
                Open_ReadAppend  = Open_ReadOnly | Open_Append
            } ;

        protected:
            /**
             * To know if the file has already been closed.
             */
            bool m_isClosed = false ;

            /**
             * Mode in which the file has been opened. If the file is not
             * opened, its mode is set to Open_None.
             */
            OpenMode m_openMode = OpenMode::Open_None ;

            /**
             * Path to the file.
             */
            std::filesystem::path m_path ;

        public:
            /**
             * Creation a File from a string.
             * @param   filepath    Path to the file to open.
             */
            exported File(const std::string& filepath) {
                m_path = std::filesystem::path(filepath) ;
            }

            /**
             * Destruction of the File in memory.
             */
            exported ~File() = default ;

            /**
             * Open the File in the given mode.
             * @param   mode    Mode to access File and perform some
             *                  operations on it.
             */
            exported void open(OpenMode mode) {
                if (!isOpened()) {
                    m_openMode = mode ;
                    openImpl(mode) ;
                }
            }

            /**
             * Close the File.
             */
            exported void close() {
                if (isOpened()) {
                    m_isClosed = true ;
                    m_openMode = OpenMode::Open_None ;
                    closeImpl() ;
                }
            }

            /**
             * Get the path to the File.
             * @return  The path of the File.
             */
            exported const std::filesystem::path& path() const {
                return m_path ;
            }

            /**
             * To know if the file is opened.
             */
            exported bool isOpened() const {
                return m_openMode != OpenMode::Open_None ;
            }

            /**
             * To know if the file is closed.
             */
            exported bool isClosed() const {
                return m_isClosed ;
            }

            /**
             * Mode in which the file has been opened. If the file is not
             * opened, its mode is set to Open_None.
             */
            exported OpenMode openMode() const {
                return m_openMode ;
            }

        protected:
            /**
             * Open the File in the given mode.
             * @param   mode    Mode to access File and perform some
             *                  operations on it.
             */
            exported virtual void openImpl(OpenMode mode) = 0 ;

            /**
             * Close the File.
             */
            exported virtual void closeImpl() = 0 ;

        private:
            // Disable copy and move.
            exported File(const File&) = delete ;
            exported File(File&&) = delete ;
            exported File& operator=(const File&) = delete ;
            exported File& operator=(File&&) = delete ;
    } ;
}

#endif
