#ifndef __HOPE__GL_SHADER_PROGRAM__
#define __HOPE__GL_SHADER_PROGRAM__

#include <scene/ogl/rendering/glsl/shaders/VertexShader.hpp>
#include <scene/ogl/rendering/glsl/shaders/FragmentShader.hpp>
#include <scene/ogl/rendering/glsl/shaders/GeometryShader.hpp>
#include <scene/ogl/rendering/glsl/shaders/TesselationControlShader.hpp>
#include <scene/ogl/rendering/glsl/shaders/TesselationEvaluationShader.hpp>
#include <GL/glew.h>

namespace Hope::GL {
    /**
     * A shader program combines several types of shaders (vertex, fragment,
     * geometry, ...) to create a pipeline that is used to render objects,
     * materials, post-production effects, etc.
     * Only one shader of each type can be put in the pipeline but it is not
     * necessary to put all the types of shaders together. For example, a
     * material shader can be only composed of a vertex shader and a fragment
     * shader.
     */
    class ShaderProgram final {
        private:
            /**
             * ID of the program.
             */
            GLuint m_programID ;

            /**
             * Vertex shader that composes the current program.
             */
            VertexShader m_vertex ;

            /**
             * Fragment shader that composes the current program.
             */
            FragmentShader m_fragment ;

            /**
             * Geometry shader that composes the current program.
             */
            GeometryShader m_geometry ;

            /**
             * Tesselation control shader that composes the current program.
             */
            TesselationControlShader m_tessControl ;

            /**
             * Tesselation evaluation shader that composes the current program.
             */
            TesselationEvaluationShader m_tessEval ;

        public:
            /**
             * Create a shader program.
             */
            ShaderProgram() {
                m_programID = glCreateProgram() ;
            }

            /**
             * Destroy a shader program.
             */
            ~ShaderProgram() {
                glDeleteProgram(m_programID) ;
            }

            /**
             * Link the program.
             */
            void link() {
                glLinkProgram(m_programID) ;
                log() ;
            }

            /**
             * Use the program.
             */
            void use() {
                glUseProgram(m_programID) ;
            }

            /**
             * Set the vertex shader file that contains the source code.
             */
            void setVertexShaderFile(const std::string& filepath) {
                m_vertex.setSourceFile(filepath) ;
                glAttachShader(m_programID, m_vertex) ;
            }

            /**
             * Set the vertex shader source code.
             */
            void setVertexShaderCode(const std::string& code) {
                m_vertex.setSourceCode(code) ;
                glAttachShader(m_programID, m_vertex) ;
            }

            /**
             * Set the fragment shader file that contains the source code.
             */
            void setFragmentShaderFile(const std::string& filepath) {
                m_fragment.setSourceFile(filepath) ;
                glAttachShader(m_programID, m_fragment) ;
            }

            /**
             * Set the fragment shader source code.
             */
            void setFragmentShaderCode(const std::string& code) {
                m_fragment.setSourceCode(code) ;
                glAttachShader(m_programID, m_fragment) ;
            }

            /**
             * Set the geometry shader file that contains the source code.
             */
            void setGeometryShaderFile(const std::string& filepath) {
                m_geometry.setSourceFile(filepath) ;
                glAttachShader(m_programID, m_geometry) ;
            }

            /**
             * Set the geometry shader source code.
             */
            void setGeometryShaderCode(const std::string& code) {
                m_geometry.setSourceCode(code) ;
                glAttachShader(m_programID, m_geometry) ;
            }

            /**
             * Set the tesselation control shader file that contains the source
             * code.
             */
            void setTesselationControlShaderFile(const std::string& filepath) {
                m_tessControl.setSourceFile(filepath) ;
                glAttachShader(m_programID, m_tessControl) ;
            }

            /**
             * Set the tesselation control shader source code.
             */
            void setTesselationControlShaderCode(const std::string& code) {
                m_tessControl.setSourceCode(code) ;
                glAttachShader(m_programID, m_tessControl) ;
            }

            /**
             * Set the tesselation evaluation shader file that contains the source
             * code.
             */
            void setTesselationEvaluationShaderFile(const std::string& filepath) {
                m_tessEval.setSourceFile(filepath) ;
                glAttachShader(m_programID, m_tessEval) ;
            }

            /**
             * Set the tesselation evaluation shader source code.
             */
            void setTesselationEvaluationShaderCode(const std::string& code) {
                m_tessEval.setSourceCode(code) ;
                glAttachShader(m_programID, m_tessEval) ;
            }

        private:
            /**
             * Log any error in the shader program set up.
             */
            void log() ;
    } ;
}

#endif
