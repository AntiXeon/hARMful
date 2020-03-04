#include <scene/ogl/rendering/glsl/shaders/Shader.hpp>
#include <files/text/TextFile.hpp>
#include <files/text/TextData.hpp>
#include <utils/LogSystem.hpp>
#include <algorithm>
#include <array>

using namespace Hope::GL ;

Shader::Shader(const GLenum shaderType)
    : m_shaderType(shaderType) {

}

Shader::~Shader() {
    if (isValid()) {
        glDeleteShader(m_shaderID) ;
    }
}

void Shader::addSourceFile(const std::string& filepath) {
    Spite::TextFile shaderFile(filepath) ;
    shaderFile.open(Spite::File::OpenMode::Open_ReadOnly) ;

    Spite::TextData textData ;
    shaderFile.load(&textData) ;
    addSourceCode(textData.data()) ;
}

bool Shader::compile() {
    if (m_shaderID != GL_INVALID_VALUE) {
        return false ;
    }

    // Initialize the shader.
    m_shaderID = glCreateShader(m_shaderType) ;

    // Convert std::string to C strings.
    std::vector<const char*> sourceCodes ;
    std::transform(
        m_sources.begin(),
        m_sources.end(),
        std::back_inserter(sourceCodes),
        SourceToCStr
    ) ;

    // Set the source code of the shader.
    glShaderSource(
        m_shaderID,
        static_cast<int>(sourceCodes.size()),
        &sourceCodes[0],
        nullptr
    ) ;

    // Compile and check errors.
    glCompileShader(m_shaderID) ;

    GLint isCompiled = 0 ;
    glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &isCompiled) ;

    if (isCompiled == GL_FALSE) {
        printCompilationError() ;
    }

    // Free the space used by the source code as it is not required anymore.
    m_sources.clear() ;

    return (isCompiled == GL_TRUE) ;
}

void Shader::printCompilationError() {
    GLint logSize = 0 ;
    glGetShaderiv(m_shaderID, GL_INFO_LOG_LENGTH, &logSize) ;

    if (logSize > 0) {
        std::string errorLog ;
        errorLog.resize(logSize) ;
        glGetShaderInfoLog(m_shaderID, logSize, &logSize, &errorLog[0]) ;

        // Write the error in the log.
        auto logWeakPtr = Doom::LogSystem::GetInstance() ;
        auto logSharedPtr = logWeakPtr.lock() ;
        if (logSharedPtr) {
            Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Error ;
            logSharedPtr -> writeLine(level, errorLog) ;
        }
    }

    // Delete the shader as it failed.
    glDeleteShader(m_shaderID) ;
    m_shaderID = GL_INVALID_VALUE ;
}
