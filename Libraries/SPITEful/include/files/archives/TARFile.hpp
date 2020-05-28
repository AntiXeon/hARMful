#ifndef __SPITE__TAR_FILE__
#define __SPITE__TAR_FILE__

#include <File.hpp>
#include <third_party/microtar.h>
#include <string>
#include <vector>

namespace Spite {
    /**
     * Class for creating a .tar archive file.
     */
    class TARFile final : public File {
        private:
            /**
             * Inner data structure in memory.
             */
            mtar_t m_memory ;

        public:
            /**
             * Create a new TARFile instance.
             * @path    Path to the file.
             */
            exported TARFile(const std::string& path) ;

            /**
             * Destruction of the TARFile instance.
             */
            exported ~TARFile() ;

            /**
             * Add a binary file into the archive.
             */
            template <typename T>
            exported bool addBinaryFile(
                const std::string& filename,
                const std::vector<T*> bytes
            ) ;

            /**
             * A a text file into the archive.
             */
            exported bool addText(
                const std::string& filename,
                const std::string& text
            ) ;

        private:
            /**
             * Open the File in the given mode.
             * @param   mode    Mode to access File and perform some
             *                  operations on it.
             */
            exported void openImpl(File::OpenMode mode) override ;

            /**
             * Close the File.
             */
            exported void closeImpl() override ;

            // Disable copy and move.
            exported TARFile(const TARFile&) = delete ;
            exported TARFile(TARFile&&) = delete ;
            exported TARFile& operator=(const TARFile&) = delete ;
            exported TARFile& operator=(TARFile&&) = delete ;
    } ;
}

#endif
