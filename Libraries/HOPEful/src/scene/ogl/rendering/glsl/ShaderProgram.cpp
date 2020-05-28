#include <scene/ogl/rendering/glsl/ShaderProgram.hpp>
#include <utils/LogSystem.hpp>

using namespace Hope::GL ;

void ShaderProgram::build() {
    std::vector<GLuint> attachedShaders ;

    if (m_vertex.hasSource()) {
        m_vertex.compile() ;
        glAttachShader(m_programID, m_vertex) ;
        attachedShaders.push_back(m_vertex) ;
    }

    if (m_fragment.hasSource()) {
        m_fragment.compile() ;
        glAttachShader(m_programID, m_fragment) ;
        attachedShaders.push_back(m_fragment) ;
    }

    if (m_geometry.hasSource()) {
        m_geometry.compile() ;
        glAttachShader(m_programID, m_geometry) ;
        attachedShaders.push_back(m_geometry) ;
    }

    if (m_tessControl.hasSource()) {
        m_tessControl.compile() ;
        glAttachShader(m_programID, m_tessControl) ;
        attachedShaders.push_back(m_tessControl) ;
    }

    if (m_tessEval.hasSource()) {
        m_tessEval.compile() ;
        glAttachShader(m_programID, m_tessEval) ;
        attachedShaders.push_back(m_tessEval) ;
    }

    link() ;
}

bool ShaderProgram::isSuccessful(GLenum reason) {
    GLint isSuccess = 0 ;
    glGetProgramiv(m_programID, reason, &isSuccess) ;

    if (isSuccess == GL_FALSE) {
        GLint logSize = 0 ;
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &logSize) ;

        if (logSize > 0) {
            std::string errorLog ;
            errorLog.resize(logSize) ;
            glGetProgramInfoLog(m_programID, logSize, &logSize, &errorLog[0]) ;

            Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Error ;
            Doom::LogSystem::WriteLine(level, errorLog) ;
        }

        // Delete the shader as it failed.
        glDeleteProgram(m_programID) ;
        m_programID = GL_INVALID_VALUE ;
    }

    return (isSuccess == GL_TRUE) ;
}
