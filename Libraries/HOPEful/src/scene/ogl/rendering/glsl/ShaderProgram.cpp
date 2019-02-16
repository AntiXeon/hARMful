#include <scene/ogl/rendering/glsl/ShaderProgram.hpp>
#include <utils/LogSystem.hpp>

using namespace Hope::GL ;

void ShaderProgram::log(GLenum reason) {
    GLint isLinked = 0 ;
    glGetProgramiv(m_programID, reason, &isLinked) ;

    if (isLinked == GL_FALSE) {
        GLint logSize = 0 ;
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &logSize) ;

        if (logSize > 0) {
            std::string errorLog ;
            errorLog.resize(logSize) ;
            glGetProgramInfoLog(m_programID, logSize, &logSize, &errorLog[0]) ;

            // Write the error in the log.
            auto logWeakPtr = Doom::LogSystem::GetInstance() ;
            auto logSharedPtr = logWeakPtr.lock() ;
            if (logSharedPtr) {
                Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Error ;
                logSharedPtr -> writeLine(level, errorLog) ;
            }
        }

        // Delete the shader as it failed.
        glDeleteProgram(m_programID) ;
        m_programID = GL_INVALID_VALUE ;
    }
}
