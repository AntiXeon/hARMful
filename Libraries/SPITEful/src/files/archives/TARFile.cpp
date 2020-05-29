#include <files/archives/TARFile.hpp>
#include <files/archives/TARData.hpp>
#include <utils/LogSystem.hpp>
#include <utils/StringExt.hpp>
#include <SPITEStrings.hpp>
#include <filesystem>
#include <stdexcept>

#include <third_party/microtar.h>

namespace fs = std::filesystem ;
using namespace Spite ;

TARFile::TARFile(const std::string& path)
    : File(path) {}

TARFile::~TARFile() {
    close() ;
}

bool TARFile::load(IFileData* /*filedata*/) {
    // auto* tarData = reinterpret_cast<TARData*>(fileData) ;
    // ...

    return true ;
}

bool TARFile::save(
    IFileData* fileData,
    const std::string& path
) {
    auto* tarData = reinterpret_cast<TARData*>(fileData) ;

    mtar_t tar ;
    tarData -> initialize(tar, path, "w") ;
    tarData -> beforeWrite(tar) ;
    tarData -> write(tar) ;
    tarData -> finalize(tar) ;

    return true ;
}
