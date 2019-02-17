#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <map>

using namespace std ;
namespace fs = filesystem ;

const string PathSeparator = "/" ;
const string LibName = "HOPE" ;
const string ShadersDirectory = "shaders" ;
const string CppPath = "scene/components/materials/" ;
const string HeaderCppDirectory = LibName + "/include/" + CppPath ;
const string SourceCppDirectory = LibName + "/src/" + CppPath ;

const string CppHeaderExtension = ".hpp" ;
const string CppSourceExtension = ".cpp" ;

const string VertexShaderType = "vert" ;
const string FragmentShaderType = "frag" ;

/**
 * Structure to keep together all the shader program files.
 */
struct ShaderProgramFiles {
    string directory ;

    string vertex ;
    string fragment ;
} ;

// Set the first letter of a string upper case, the other characters are lower
// case.
string firstUpLetter(const string& input) {
    string output = input ;
    output[0] = toupper(output[0]) ;

    size_t length = input.size() ;
    for (size_t index = 1 ; index < length ; index++) {
        output[index] = tolower(output[index]) ;
    }

    return output ;
}

// Set all the letters of a string upper case.
string upperCase(const string& input) {
    string output = input ;

    size_t length = input.size() ;
    for (size_t index = 0 ; index < length ; index++) {
        output[index] = toupper(output[index]) ;
    }

    return output ;
}

// Get the list of the shader files.
void getShaderFiles(map<fs::path, ShaderProgramFiles>& shaderFiles) {
    string directory ;

    for (auto& p: fs::recursive_directory_iterator(ShadersDirectory)) {
        if (fs::is_directory(p)) {
            directory = p.path().string() ;
            continue ;
        }

        // To store in the right structure.
        string shaderName = p.path().stem().string() ;
        // To store the file path to the right shader type.
        string shaderType = p.path().extension().string().erase(0,1) ;
        // Filepath to read later.
        string shaderPath = p.path().string() ;

        std::size_t posUselessDir = directory.rfind("/materials/") ;
        shaderFiles[shaderName].directory = directory.substr(0, posUselessDir) ;

        if (shaderType == VertexShaderType) {
            shaderFiles[shaderName].vertex = shaderPath ;
        }
        else if (shaderType == FragmentShaderType) {
            shaderFiles[shaderName].fragment = shaderPath ;
        }
        else {
            // Unknown shader type, abord.
            cerr << "Unknown shader type: " << shaderType << ". ABORT." << endl ;
            exit(-1) ;
        }
    }
}

// Write the CPP header file.
void writeHeader(const fs::path& program, const ShaderProgramFiles& files) {
    const string FullDirPath = HeaderCppDirectory + files.directory ;
    fs::create_directories(FullDirPath) ;

    const string HeaderFilename = firstUpLetter(program.string()) ;
    const string HeaderDefine = "__" + LibName + "__" + upperCase(program.string()) + "_MATERIAL_SHADER_SRC__" ;

    // Open the output file.
    const string FullFilePath = FullDirPath + PathSeparator + HeaderFilename + CppHeaderExtension ;
    fstream output_file ;
    output_file.open(FullFilePath, ios_base::out) ;

    // Write in the file.
    output_file << "#ifndef " << HeaderDefine << endl ;
    output_file << "#define " << HeaderDefine << endl ;
    output_file << endl ;
    output_file << "#include <string>" << endl ;
    output_file << endl ;

    if (!files.vertex.empty()) {
        output_file << "extern std::string " << HeaderFilename << "VertexCode ;" << endl ;
    }

    if (!files.fragment.empty()) {
        output_file << "extern std::string " << HeaderFilename << "FragmentCode ;" << endl ;
    }

    output_file << endl ;
    output_file << "#endif" << endl ;

    output_file.close() ;
}

// Write the CPP header file.
void writeSource(const fs::path& program, const ShaderProgramFiles& files) {
    const string FullDirPath = SourceCppDirectory + files.directory ;
    fs::create_directories(FullDirPath) ;

    const string SourceFilename = firstUpLetter(program.string()) ;

    // Open the output file.
    const string FullFilePath = FullDirPath + PathSeparator + SourceFilename + CppSourceExtension ;
    fstream output_file ;
    output_file.open(FullFilePath, ios_base::out) ;


    // #include <header.hpp>
    const string IncludeHeaderPath = CppPath + files.directory + PathSeparator + SourceFilename + CppHeaderExtension ;
    output_file << "#include <" << IncludeHeaderPath << ">" << endl ;
    output_file << endl ;

    if (!files.vertex.empty()) {
        output_file << "std::string " << SourceFilename << "VertexCode =" << endl ;
        output_file << "\"\\" << endl ;
        // Put file content here!
        output_file << "\" ;" << endl ;
        output_file << endl ;
    }

    if (!files.fragment.empty()) {
        output_file << "std::string " << SourceFilename << "FragmentCode =" << endl ;
        output_file << "\"\\" << endl ;
        // Put file content here!
        output_file << "\" ;" << endl ;
        output_file << endl ;
    }

    output_file.close() ;
}

// Write the CPP files that will contain the code of the shaders.
void writeCppFiles(const fs::path& program, const ShaderProgramFiles& files) {
    writeHeader(program, files) ;
    writeSource(program, files) ;
}

// Main function.
int main() {
    // Map to associate a shader program to its related files.
    map<fs::path, ShaderProgramFiles> shaderFiles ;
    getShaderFiles(shaderFiles) ;

    for (const auto& kv : shaderFiles) {
        writeCppFiles(kv.first, kv.second) ;
    }

    return 0 ;
}
