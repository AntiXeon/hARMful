#ifndef __HOPE__GL_SHADER__
#define __HOPE__GL_SHADER__

#include <GL/glew.h>
#include <string>

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
             * To know if the shader has a source code.
             */
            bool m_hasCode = false ;

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
             * Set the source file of the shader.
             * Launch the compilation of the shader.
             */
            void setSourceFile(const std::string& filepath) ;

            /**
             * Directly set the source code of the shader.
             * Launch the compilation of the shader.
             */
            void setSourceCode(const std::string& code) ;

            /**
             * Check if the shader is valid.
             */
            bool isValid() const {
                return glIsShader(m_shaderID) ;
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
             * To know if the shader has a source code.
             */
            bool hasCode() const {
                return m_hasCode ;
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
    } ;
}

#endif
