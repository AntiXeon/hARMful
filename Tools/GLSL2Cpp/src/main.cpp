#include <Paths.hpp>
#include <FileUtils.hpp>
#include <StringUtils.hpp>
#include <iostream>
#include <unistd.h>

using namespace std ;

int main() {
    const std::string PathSeparatorStr = std::string(PathSeparator) ;


    // Create the local symlink to the HOPEful library folder.
    symlink(LibDirectory, SimLinkDirectory) ;

    // Get the shader files.
    auto shaderFiles = FileUtils::GetShaderFiles(ShadersDirectory) ;

    // Copy GLSL includes into GLSL modules/includes...
    {
        std::string fullDestinationPath = std::string(ShadersDirectory) + PathSeparatorStr +
                                            GLSL4xModulesDirectory + PathSeparatorStr +
                                            IncludesDirectory ;

        FileUtils::CopyIncludeModules(
            ShadersDirectory,
            shaderFiles[GLSLIncludesDirectory],
            fullDestinationPath
        ) ;
    }

    {
        const bool RemoveUnderscoreChars = true ;
        std::string fullDestinationPath = std::string(GLSLCppHeadersDirectory) +
                                            PathSeparatorStr +
                                            std::string(IncludesDirectory) ;

        // Copy GLSL includes into CPP headers (in "shaders" folder)...
        FileUtils::CopyIncludeModules(
            ShadersDirectory,
            shaderFiles[GLSLIncludesDirectory],
            fullDestinationPath,
            CppHeaderExtension,
            RemoveUnderscoreChars
        ) ;
    }

    // Remove GLSL/includes from the map.
    shaderFiles.erase(GLSLIncludesDirectory) ;

    // Convert GLSL source code to C++ HPP/CPP files.
    for (auto& [dir, files]: shaderFiles) {
        files.storeIntoCppFiles(
            ShadersDirectory,
            ShadersCppHeadersDirectory,
            ShadersCppSourcesDirectory
        ) ;
    }
}
