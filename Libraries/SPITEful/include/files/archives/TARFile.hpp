#ifndef __SPITE__TAR_FILE__
#define __SPITE__TAR_FILE__

#include <File.hpp>
#include <string>
#include <vector>

namespace Spite {
    /**
     * Class for creating a .tar archive file.
     */
    class TARFile final : public File {
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
             * Load a data at a given place on disk.
             * @param   filedata    File data to store data in.
             * @return  TRUE on success, FALSE on failure.
             */
            exported bool load(IFileData* fileData) override ;

            /**
             * Save a data at a given place on disk.
             * @param   filedata    Raw data to write on disk. They can be
             *                      processed before saving.
             * @param   path        Path to the location on filesystem.
             * @return  TRUE on success, FALSE on failure.
             */
            exported bool save(
                IFileData* fileData,
                const std::string& path = ""
            ) override ;

        private:
            /**
             * Open the File in the given mode.
             * @param   mode    Mode to access File and perform some
             *                  operations on it.
             */
            exported void openImpl(File::OpenMode) override {}

            /**
             * Close the File.
             */
            exported void closeImpl() override {}

            // Disable copy and move.
            exported TARFile(const TARFile&) = delete ;
            exported TARFile(TARFile&&) = delete ;
            exported TARFile& operator=(const TARFile&) = delete ;
            exported TARFile& operator=(TARFile&&) = delete ;
    } ;
}

#endif
