#include <files/archives/TARData.hpp>
#include <utils/StringExt.hpp>
#include <SPITEStrings.hpp>
#include <algorithm>
#include <filesystem>
#include <stdexcept>

using namespace Spite ;

bool TARData::addTextFile(
    const fs::path& filepath,
    const std::string& text
) {
    if (m_infos.count(filepath) > 1) {
        return false ;
    }

    size_t begin = m_fileBytes.size() ;

    size_t dataSize = text.size() ;
    auto* rawBytes = text.data() ;
    m_fileBytes.insert(m_fileBytes.end(), rawBytes, rawBytes + dataSize) ;

    size_t end = m_fileBytes.size() ;
    m_infos[filepath] = {
        .type = FileType::Text,
        .begin = begin,
        .end = end
    } ;

    m_directories.insert(filepath.parent_path()) ;

    return true ;
}

bool TARData::readTextFile(
    const fs::path& filepath,
    std::string& text
) {
    if (m_infos.count(filepath) == 0) {
        return false ;
    }

    text.clear() ;

    auto infos = m_infos[filepath] ;
    auto contentLength = infos.end - infos.begin ;
    auto bytes = reinterpret_cast<char*>(m_fileBytes.data()) ;
    text.copy(bytes, infos.begin, contentLength) ;

    return true ;
}

const std::set<fs::path>& TARData::directories() const {
    return m_directories ;
}

std::vector<fs::path> TARData::paths() const {
    std::vector<fs::path> listPaths ;

    std::transform(
        std::begin(m_infos),
        std::end(m_infos),
        std::back_inserter(listPaths),
        [](auto const& pair) {
            return pair.first ;
        }
    ) ;

    return listPaths ;
}

std::vector<unsigned char>& TARData::data() {
    return m_fileBytes ;
}

void TARData::initialize(
    mtar_t& tar,
    const std::string& path,
    const std::string& tarOpenMode
) {
    int success = mtar_open(
        &tar,
        path.c_str(),
        tarOpenMode.c_str()
    ) ;

    if (success != MTAR_ESUCCESS) {
        Doom::LogSystem::WriteLine(
            Doom::LogSystem::Gravity::Error,
            mtar_strerror(success),
            path
        ) ;
        finalize(tar) ;
    }
}

void TARData::finalize(mtar_t& tar) {
    if (tar.stream) {
        mtar_finalize(&tar) ;
    }

    mtar_close(&tar) ;
}

void TARData::beforeWrite(mtar_t& tar) {
    std::set<std::string> addedPaths ;

    for (auto const& [path, info] : m_infos) {
        auto dirPath = path.parent_path().string() ;
        if (addedPaths.count(dirPath) == 0) {
            mtar_write_dir_header(&tar, dirPath.c_str()) ;
            addedPaths.insert(dirPath) ;
        }
    }
}

void TARData::write(mtar_t& tar) {
    for (auto const& [path, info] : m_infos) {
        auto type = info.type ;

        switch (type) {
            default:
            case FileType::Binary:
                writeBinary(tar, path.string(), info) ;
                break ;

            case FileType::Text:
                writeText(tar, path.string(), info) ;
                break ;
        }
    }
}

bool TARData::writeBinary(
    mtar_t& tar,
    const std::string& filepath,
    const FileInfo& infos
) {
    int success = 0 ;
    size_t dataLength = infos.end - infos.begin ;

    success = mtar_write_file_header(
        &tar,
        filepath.c_str(),
        dataLength
    ) ;

    if (success != MTAR_ESUCCESS) {
        Doom::LogSystem::WriteLine(
            Doom::LogSystem::Gravity::Error,
            mtar_strerror(success),
            filepath
        ) ;
        return false ;
    }

    success = mtar_write_data(
        &tar,
        m_fileBytes.data() + infos.begin,
        dataLength
    ) ;

    if (success != MTAR_ESUCCESS) {
        Doom::LogSystem::WriteLine(
            Doom::LogSystem::Gravity::Error,
            mtar_strerror(success),
            filepath
        ) ;
        return false ;
    }

    return true ;
}

bool TARData::writeText(
    mtar_t& tar,
    const std::string& filepath,
    const FileInfo& infos
) {
    int success = 0 ;

    size_t textLength = infos.end - infos.begin ;
    success = mtar_write_file_header(
        &tar,
        filepath.c_str(),
        textLength
    ) ;

    if (success != MTAR_ESUCCESS) {
        Doom::LogSystem::WriteLine(
            Doom::LogSystem::Gravity::Error,
            mtar_strerror(success),
            filepath
        ) ;
        return false ;
    }

    success = mtar_write_data(
        &tar,
        reinterpret_cast<char*>(m_fileBytes.data() + infos.begin),
        textLength
    ) ;

    if (success != MTAR_ESUCCESS) {
        Doom::LogSystem::WriteLine(
            Doom::LogSystem::Gravity::Error,
            mtar_strerror(success),
            filepath
        ) ;
        return false ;
    }

    return true ;
}

void TARData::read(mtar_t& tar) {
    mtar_header_t fileHeader ;

    while ((mtar_read_header(&tar, &fileHeader)) != MTAR_ENULLRECORD) {
        if (m_infos.count(fileHeader.name) > 0) {
            continue ;
        }

        if (fileHeader.size == 0) {
            // It is a directory.
            m_directories.insert(fileHeader.name) ;
        }
        else {
            // It is a file.
            FileInfo info = {
                .type = FileType::Unknown,
                .begin = tar.pos,
                .end = tar.pos + fileHeader.size,
            } ;

            std::vector<char*> fileBytes ;
            fileBytes.resize(fileHeader.size) ;
            mtar_read_data(&tar, fileBytes.data(), fileHeader.size) ;
            auto* fileBytesUC = reinterpret_cast<unsigned char*>(fileBytes.data()) ;

            m_infos[fileHeader.name] = info ;
            m_fileBytes.insert(m_fileBytes.end(), fileBytesUC, fileBytesUC + fileHeader.size) ;
        }

        mtar_next(&tar) ;
    }
}
