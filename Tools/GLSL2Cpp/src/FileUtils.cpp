#include <FileUtils.hpp>
#include <StringUtils.hpp>
#include <Paths.hpp>
#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem ;

std::map<std::string, ShaderFileAggregator> FileUtils::GetShaderFiles(
    const std::string& shaderDirectory
) {
    std::map<std::string, ShaderFileAggregator> files ;

    for (auto& p: fs::recursive_directory_iterator(shaderDirectory)) {
        if (fs::is_directory(p)) {
            continue ;
        }

        fs::path filepath = p.path() ;
        fs::path dirPath = filepath ;
        std::string directory = dirPath.remove_filename() ;

        size_t PathSeparatorLength = std::string(PathSeparator).size() ;
        size_t ShadersDirectoryLength = shaderDirectory.size() ;
        size_t position = directory.find(shaderDirectory) ;

        // Make the path relative to the global shader directory.
        std::string relativeDir = directory.substr(position + ShadersDirectoryLength + PathSeparatorLength) ;
        // Remove the tail path separator.
        relativeDir = relativeDir.substr(0, relativeDir.size() - PathSeparatorLength) ;

        if (files.count(relativeDir) == 0) {
            position = relativeDir.rfind(PathSeparator) ;
            std::string shaderName = relativeDir.substr(position + PathSeparatorLength) ;
            shaderName = StringUtils::RemoveUnderscoreChars(shaderName) ;

            std::string parentDir = relativeDir.substr(0, position) ;

            files[relativeDir] = ShaderFileAggregator(
                relativeDir,
                parentDir,
                shaderName
            ) ;
        }

        ShaderFile file = {
            filepath.stem().string(),
            filepath.extension().string()
        } ;

        files[relativeDir].insert(file) ;
    }

    return files ;
}

void FileUtils::CopyIncludeModules(
    const std::string& shaderDirectory,
    const ShaderFileAggregator& includeAggregator,
    const std::string& destinationDirName,
    const char* destExtension,
    const bool removeUnderscores
) {
    fs::create_directories(destinationDirName) ;

    const std::string PathSeparatorStr = std::string(PathSeparator) ;
    std::string pathIteration = shaderDirectory + PathSeparatorStr + includeAggregator.directoryPath() ;

    // Copy each file in the original directory.
    for (auto& p: fs::recursive_directory_iterator(pathIteration)) {
        const fs::path& fromFilePath = p.path() ;

        std::string filename ;
        if (removeUnderscores) {
            filename = StringUtils::RemoveUnderscoreChars(fromFilePath.stem().string()) ;
        }
        else {
            filename = fromFilePath.stem().string() ;
        }

        // Use the right file extension.
        std::string extension ;
        if (destExtension) {
            extension = std::string(destExtension) ;
        }
        else {
            extension = fromFilePath.extension().string() ;
        }

        std::string completeFilename = filename + extension ;
        std::string toFilePath = destinationDirName + PathSeparatorStr + completeFilename ;

        fs::copy_file(
            fromFilePath,
            toFilePath,
            fs::copy_options::overwrite_existing
        ) ;
    }
}

std::string FileUtils::GetFileContent(
    const std::string& filepath,
    const bool withNewLine
) {
    std::string result ;

    std::ifstream input ;
    input.open(filepath) ;

    if (!input) {
          // Fail.
          std::cerr << "Unable to read the content of " << filepath << std::endl ;
          return result ;
    }

    std::string readline ;
    while (std::getline(input, readline)) {
        result += readline ;

        if (withNewLine) {
            result += "\\n\\" ;
        }

        result += "\n" ;
    }

    input.close() ;

    return result ;
}
