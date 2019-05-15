#ifndef __GLSL2CPP__FILE_UTILS__
#define __GLSL2CPP__FILE_UTILS__

#include <ShaderFileAggregator.hpp>
#include <string>
#include <map>

namespace FileUtils {
    /**
     * Get the shader files.
     * @param   directory   Input directory path.
     */
    std::map<std::string, ShaderFileAggregator> GetShaderFiles(const std::string& shaderDirectory) ;

    /**
     * Copy the includes into the shader modules.
     * @param   directory           Input directory path.
     * @param   includeAggregator   Aggregator of the include files.
     * @param   destinationDirName  Name of the directory in which the includes
     *                              are copied.
     * @param   destExtension       Extension of the destination files. nullptr
     *                              is a valid value and keeps the original file
     *                              extension.
     * @param   removeUnderscores   Remove underscore characters from the file
     *                              name.
     */
    void CopyIncludeModules(
        const std::string& shaderDirectory,
        const ShaderFileAggregator& includeAggregator,
        const std::string& destinationDirName,
        const char* destExtension = nullptr,
        const bool removeUnderscores = false
    ) ;

    /**
     * Get the content of a file.
     * @param   filepath    Path to the file to get the content.
     * @param   withNewLine If true, each line is ended with a new line
     *                      character.
     * @return  The content of the file.
     */
    std::string GetFileContent(
        const std::string& filepath,
        const bool withNewLine = true
    ) ;
}

#endif
