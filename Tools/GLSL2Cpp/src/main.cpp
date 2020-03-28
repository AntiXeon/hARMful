#include <FileUtils.hpp>
#include <StringUtils.hpp>
#include <iostream>
#include <filesystem>
#include <system_error>
#include <Paths.hpp>
#include <cstdlib>

bool createSymLink(const std::string& harmfulDir) {
    const std::string PathSeparatorStr = std::string(PathSeparator) ;

	fs::path libDirectoryPath(harmfulDir + PathSeparator + LibDirectory) ;
	libDirectoryPath = libDirectoryPath ;

	fs::path symlibDirectoryPath(SimLinkDirectory) ;
	symlibDirectoryPath = symlibDirectoryPath ;

	if (fs::exists(symlibDirectoryPath)) {
	    return true ;
    }

    // Create the local symlink to the HOPEful library folder.
	std::error_code error ;
	fs::create_directory_symlink(libDirectoryPath, symlibDirectoryPath, error) ;

	if (error) {
		auto errorMsg = error.message() ;
		std::cerr << "ERROR: " << error << errorMsg << std::endl ;
        return false ;
	}

    return true ;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        return EXIT_FAILURE ;
    }

    std::string harmfulDir(argv[1]) ;

    if (!createSymLink(harmfulDir)) {
        return EXIT_FAILURE ;
    }

    const std::string PathSeparatorStr = std::string(PathSeparator) ;

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

    return EXIT_SUCCESS ;
}
