#include <ShaderFileAggregator.hpp>
#include <GLSL2CPPStrings.hpp>
#include <FileUtils.hpp>
#include <StringUtils.hpp>
#include <Paths.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem ;

ShaderFileAggregator::ShaderFileAggregator(
    const std::string& relativeDirectoryPath,
    const std::string& parentDirectoryPath,
    const std::string& shaderName
) : m_relativeDirectoryPath(relativeDirectoryPath),
    m_parentDirectoryPath(parentDirectoryPath),
    m_shaderName(shaderName) {}

void ShaderFileAggregator::storeIntoCppFiles(
    const std::string& shadersDir,
    const std::string& headersPath,
    const std::string& sourcesPath
) const {
    writeHeaderFiles(shadersDir, headersPath) ;
    writeSourceFiles(shadersDir, sourcesPath) ;
}

void ShaderFileAggregator::debug() {
    std::cout << m_shaderName << " (" << m_relativeDirectoryPath << " | " << m_parentDirectoryPath << "):" << std::endl ;
    for (ShaderFile& file: m_files) {
        std::cout << "   > " << file.stem << file.extension << std::endl ;
    }
}

void ShaderFileAggregator::writeHeaderFiles(
    const std::string& /*shadersDir*/,
    const std::string& headersPath
) const {
    std::fstream output_file ;

    std::string headerFilePath = createCppDirectory(headersPath, CppHeaderExtension) ;
    output_file.open(headerFilePath, std::ios_base::out) ;

    const std::string HeaderDefine = "__" +
                                        std::string(LibName) +
                                        "__" +
                                        StringUtils::UpperCase(m_shaderName) +
                                        "_MATERIAL_SHADER_SRC__" ;

    // Write in the file.
    {
        // Write the file header.
        output_file << WarningAutomaticGeneration << std::endl ;
        output_file << "#ifndef " << HeaderDefine << std::endl ;
        output_file << "#define " << HeaderDefine << std::endl ;
        output_file << std::endl ;
        output_file << "#include <string>" << std::endl ;
        output_file << std::endl ;

        // Write the variables corresponding to the content of the shader files.
        for (const ShaderFile& file: m_files) {
            const std::string FileNameVariable = StringUtils::RemoveUnderscoreChars(file.stem) ;
            const std::string VariableSuffix = getCppVariableSuffixFromExtension(file.extension) ;

            output_file << "extern std::string " << m_shaderName << FileNameVariable << VariableSuffix << " ;" << std::endl ;
        }

        output_file << std::endl ;
        output_file << "#endif" << std::endl ;
    }

    output_file.close() ;
}

void ShaderFileAggregator::writeSourceFiles(
    const std::string& shadersDir,
    const std::string& sourcesPath
) const {
    static const std::string PathSeparatorStr(PathSeparator) ;
    std::fstream output_file ;

    std::string srcFilePath = createCppDirectory(sourcesPath, CppSourceExtension) ;
    output_file.open(srcFilePath, std::ios_base::out) ;

    // Write in the file.
    {
        // Write the #include <header.hpp> directive.
        const std::string IncludeHeaderPath = std::string(CppPath) +
                                                std::string(ShadersDirectoryName) +
                                                PathSeparatorStr +
                                                m_parentDirectoryPath +
                                                PathSeparatorStr +
                                                m_shaderName +
                                                std::string(CppHeaderExtension) ;

        output_file << WarningAutomaticGeneration << std::endl ;
        output_file << "#include <" << IncludeHeaderPath << ">" << std::endl ;
        output_file << std::endl ;

        // Write the variables corresponding to the content of the shader files.
        for (const ShaderFile& file: m_files) {
            const std::string FilePath = shadersDir +
                                            PathSeparatorStr +
                                            m_relativeDirectoryPath +
                                            PathSeparatorStr +
                                            file.stem + file.extension ;
            const std::string FileNameVariable = StringUtils::RemoveUnderscoreChars(file.stem) ;
            const std::string VariableSuffix = getCppVariableSuffixFromExtension(file.extension) ;

            output_file << "std::string " << m_shaderName << FileNameVariable << VariableSuffix << " =" << std::endl ;
            output_file << "\"\\" << std::endl ;
            output_file << FileUtils::GetFileContent(FilePath) ;
            output_file << "\" ;" << std::endl ;
            output_file << std::endl ;
        }
    }

    output_file.close() ;
}


std::string ShaderFileAggregator::createCppDirectory(
    const std::string& cppDirectory,
    const std::string& cppExtension
) const {
    static const std::string PathSeparatorStr = std::string(PathSeparator) ;

    std::string srcDir = cppDirectory + PathSeparatorStr + m_parentDirectoryPath ;
    fs::create_directories(srcDir) ;

    return (srcDir + PathSeparatorStr + m_shaderName + cppExtension) ;
}

std::string ShaderFileAggregator::getCppVariableSuffixFromExtension(const std::string& extension) const {
    static const std::map<std::string, std::string> ExtensionSuffix =
    {
        { VertexShaderExtension,    VertexShaderVarSuffix },
        { FragmentShaderExtension,  FragmentShaderVarSuffix },
        { GeometryShaderExtension,  GeometryShaderVarSuffix },
        { GLSLModuleExtension,      GLSLModuleVarSuffix }
    } ;

    if (ExtensionSuffix.count(extension) == 1) {
        return ExtensionSuffix.at(extension) ;
    }
    else {
        return std::string() ;
    }
}
