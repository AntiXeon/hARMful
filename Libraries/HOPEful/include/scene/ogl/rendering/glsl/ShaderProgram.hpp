#ifndef __HOPE__GL_SHADER_PROGRAM__
#define __HOPE__GL_SHADER_PROGRAM__

#include <utils/Platform.hpp>

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
            exported ShaderProgram() : m_programID(glCreateProgram()) {}

            /**
             * Destroy a shader program.
             */
            exported ~ShaderProgram() {
                glDeleteProgram(m_programID) ;
            }

            /**
             * Build the shader program.
             */
            exported void build() ;

            /**
             * Link the program.
             */
            exported bool link() {
                glLinkProgram(m_programID) ;
                return isSuccessful(GL_LINK_STATUS) ;
            }

            /**
             * Use the program.
             */
            exported void use() {
                glUseProgram(m_programID) ;
            }

            /**
             * Unuse the program.
             */
            exported void unuse() {
                glUseProgram(0) ;
            }

            /**
             * Get the ID of the shader program, attributed by the OpenGL API.
             */
            exported GLuint id() const {
                return m_programID ;
            }

            /**
             * Add the vertex shader file that contains the source code.
             */
            exported void addVertexShaderFile(const std::string& filepath) {
                m_vertex.addSourceFile(filepath) ;
            }

            /**
             * Add the vertex shader source code.
             */
            exported void addVertexShaderCode(const std::string& code) {
                m_vertex.addSourceCode(code) ;
            }

            /**
             * Add the fragment shader file that contains the source code.
             */
            exported void addFragmentShaderFile(const std::string& filepath) {
                m_fragment.addSourceFile(filepath) ;
            }

            /**
             * Add the fragment shader source code.
             */
            exported void addFragmentShaderCode(const std::string& code) {
                m_fragment.addSourceCode(code) ;
            }

            /**
             * Add the geometry shader file that contains the source code.
             */
            exported void addGeometryShaderFile(const std::string& filepath) {
                m_geometry.addSourceFile(filepath) ;
            }

            /**
             * Add the geometry shader source code.
             */
            exported void addGeometryShaderCode(const std::string& code) {
                m_geometry.addSourceCode(code) ;
            }

            /**
             * Add the tesselation control shader file that contains the source
             * code.
             */
            exported void addTesselationControlShaderFile(const std::string& filepath) {
                m_tessControl.addSourceFile(filepath) ;
            }

            /**
             * Set the tesselation control shader source code.
             */
            exported void addTesselationControlShaderCode(const std::string& code) {
                m_tessControl.addSourceCode(code) ;
            }

            /**
             * Add the tesselation evaluation shader file that contains the source
             * code.
             */
            exported void addTesselationEvaluationShaderFile(const std::string& filepath) {
                m_tessEval.addSourceFile(filepath) ;
            }

            /**
             * Add the tesselation evaluation shader source code.
             */
            exported void addTesselationEvaluationShaderCode(const std::string& code) {
                m_tessEval.addSourceCode(code) ;
            }

        private:
            /**
             * Log any error in the shader program set up.
             * @return  true on success; false on failure.
             */
            bool isSuccessful(GLenum reason) ;
    } ;
}

#endif
