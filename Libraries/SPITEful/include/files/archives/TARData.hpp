#ifndef __SPITE__TAR_DATA__
#define __SPITE__TAR_DATA__

#include <utils/Platform.hpp>
#include <utils/LogSystem.hpp>
#include <third_party/microtar.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <filesystem>

namespace fs = std::filesystem ;

namespace Spite {
    /**
     * Class for creating a .tar archive file.
     */
    class TARData final {
        friend class TARUtils ;

        private:
            /**
             * Type of the file.
             */
            enum class FileType {
                Unknown,
                Text,
                Binary
            } ;

            /**
             * infos data in the total bytes buffer.
             */
            struct FileInfo {
                FileType type ;
                size_t begin ;
                size_t end ;
            } ;

            /**
             * Bytes of the files in memory.
             */
            std::vector<unsigned char> m_fileBytes ;

            /**
             * List of the directories in the archive.
             */
            std::set<fs::path> m_directories ;

            /**
             * Infos of the file bytes at a destination path.
             */
            std::map<fs::path, FileInfo> m_infos ;

        public:
            /**
             * Add a binary file.
             */
            template <typename T>
            exported bool addBinaryFile(
                const fs::path& filepath,
                const std::vector<T> bytes
            ) ;

            /**
             * Add a text file.
             */
            exported bool addTextFile(
                const fs::path& filepath,
                const std::string& text
            ) ;

            /**
             * Read the content of a file at a given path in the archive.
             */
            template <typename T>
            exported bool readBinaryFile(
                const fs::path& filepath,
                T& fileContent
            ) ;

            /**
             * Read the content of a file at a given path in the archive.
             */
            exported bool readBinaryFile(
                const fs::path& filepath,
                std::vector<unsigned char>& buffer
            ) ;

            /**
             * Read the content of a file at a given path in the archive.
             */
            exported bool readTextFile(
                const fs::path& filepath,
                std::string& text
            ) ;

            /**
             * Get the directory paths contained in the archive.
             */
            exported const std::set<fs::path>& directories() const ;

            /**
             * Get the file paths contained in the archive.
             */
            exported std::vector<fs::path> paths() const ;

            /**
             * Get the file raw data.
             * @return  Output the raw data of the file.
             */
            exported std::vector<unsigned char>& data() ;

        private:
            /**
             * Initialize TAR archive memory.
             */
            exported void initialize(
                mtar_t& tar,
                const std::string& path,
                const std::string& tarOpenMode
            ) ;

            /**
             * Finalize the archive memory.
             */
            exported void finalize(mtar_t& tar) ;

            /**
             * Write directory headers before writing files.
             */
            exported void beforeWrite(mtar_t& tar) ;

            /**
             * Write the full content of files into the mtar structure.
             */
            exported void write(mtar_t& tar) ;

            /**
             * Write a binary file into the archive.
             */
            exported bool writeBinary(
                mtar_t& tar,
                const std::string& filepath,
                const FileInfo& infos
            ) ;

            /**
             * Write a text file into the archive.
             */
            exported bool writeText(
                mtar_t& tar,
                const std::string& filepath,
                const FileInfo& infos
            ) ;

            /**
             * Read the content of the archive.
             */
            exported void read(mtar_t& tar) ;
    } ;

    template <typename T>
    bool TARData::addBinaryFile(
        const fs::path& filepath,
        const std::vector<T> bytes
    ) {
        if (m_infos.count(filepath) > 1) {
            return false ;
        }

        size_t begin = m_fileBytes.size() ;

        size_t dataSize = bytes.size() * sizeof(T) ;
        auto* rawBytes = reinterpret_cast<const unsigned char*>(bytes.data()) ;
        m_fileBytes.insert(m_fileBytes.end(), rawBytes, rawBytes + dataSize) ;

        size_t end = m_fileBytes.size() ;
        m_infos[filepath] = {
            .type = FileType::Binary,
            .begin = begin,
            .end = end
        } ;

        m_directories.insert(filepath.parent_path()) ;

        return true ;
    }

    template <typename T>
    bool TARData::readBinaryFile(const fs::path& filepath, T& fileContent) {
        if (m_infos.count(filepath) == 0) {
            return false ;
        }

        auto infos = m_infos[filepath] ;
        auto contentLength = infos.end - infos.begin ;
        fileContent.reserve(contentLength) ;

        std::vector<unsigned char> bytes ;
        bytes.reserve(contentLength) ;
        bytes.insert(
            bytes.begin(),
            m_fileBytes.begin() + infos.begin,
            m_fileBytes.begin() + infos.end
        ) ;

        fileContent = reinterpret_cast<T>(bytes.data()) ;

        return true ;
    }
}

#endif
