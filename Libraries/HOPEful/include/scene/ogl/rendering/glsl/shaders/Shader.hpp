#ifndef __HOPE__GL_SHADER__
#define __HOPE__GL_SHADER__

#include <GL/glew.h>
#include <string>
#include <vector>

namespace Hope::GL {
    /**
     * Represent a shader, that can be combined with other shaders into a shader
     * program.
     */
    class Shader {
        private:
            /**
             * The type of the shader.
             */
            GLenum m_shaderType ;

            /**
             * ID of the shader provided by the OpenGL API.
             */
            GLuint m_shaderID = GL_INVALID_VALUE ;

            /**
             * Source codes.
             */
            std::vector<std::string> m_sources ;

        public:
            /**
             * Create a new Shader.
             */
            Shader(const GLenum shaderType) ;

            /**
             * Destroy a shader.
             */
            virtual ~Shader() ;

            /**
             * Add a source file of the shader.
             */
            void addSourceFile(const std::string& filepath) ;

            /**
             * Directly add the source code of the shader.
             */
            void addSourceCode(const std::string& code) {
                m_sources.push_back(code) ;
            }

            /**
             * Compile the source codes of the shader.
             * @return  true on success; false on failure.
             */
            bool compile() ;

            /**
             * Check if the shader is valid.
             */
            bool isValid() const {
                return glIsShader(m_shaderID) ;
            }

            /**
             * Return true if at least one source is set, false otherwise.
             */
            bool hasSource() const {
                return m_sources.size() > 0 ;
            }

            /**
             * Get the type of the shader.
             */
            GLenum type() const {
                return m_shaderType ;
            }

            /**
             * Get the ID of the shader provided by the OpenGL API.
             */
            GLuint id() const {
                return m_shaderID ;
            }

            /**
             * Convert the shader directly to its ID for using it more easily in
             * the OpenGL API.
             */
            operator GLuint() const {
                return m_shaderID ;
            }


            // Copy/move operations.
            Shader() = delete ;
            Shader(const Shader& copied) = delete ;
            Shader(Shader&& moved) = delete ;
            Shader& operator=(const Shader& copied) = delete ;
            Shader& operator=(Shader&& moved) = delete ;

        private:
            /**
             * Print compilation errors.
             */
            void printCompilationError() ;

            /**
             * Callback used to convert the vector<string> to a char** for the
             * OpenGL API.
             */
            static const char* SourceToCStr(const std::string& source) {
                return source.c_str() ;
            }
    } ;
}

#endif
