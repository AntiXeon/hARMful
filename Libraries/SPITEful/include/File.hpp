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
            enum OpenMode {
                Open_None        = 0,
                Open_ReadOnly    = 1,
                Open_Append      = 2,
                Open_WriteOnly   = 4,
                Open_ReadWrite   = Open_ReadOnly | Open_WriteOnly,
                Open_ReadAppend  = Open_ReadOnly | Open_Append
            } ;

        protected:
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
             * Open the File in the given mode.
             * @param   mode    Mode to access File and perform some
             *                  operations on it.
             */
            exported virtual void open(OpenMode mode) = 0 ;

            /**
             * Close the File.
             */
            exported virtual void close() = 0 ;

            /**
             * Get the path to the File.
             * @return  The path of the File.
             */
            exported const std::filesystem::path& path() const {
                return m_path ;
            }
    } ;
}

#endif
