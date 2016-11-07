#include <assert.h>
#include <iostream>
#include <string>
#include "utils.h"
#include "shaders.h"

using namespace std ;

// Shader related IDs
static GLuint vertexID = 0, fragmentID = 0, programID = 0, uniformID = 0 ;
static GLuint vertexPositionAttrib = 0, vertexNormalAttrib = 0, vertexColorAttrib = 0 ;
static const GLchar *vertexShaderSource, *fragmentShaderSource ;


// Create shaders
void createShaders() {
	// Create the shaders
	vertexID = glCreateShader(GL_VERTEX_SHADER) ;
	assert(vertexID > 0) ;
	fragmentID = glCreateShader(GL_FRAGMENT_SHADER) ;
	assert(fragmentID > 0) ;

	// Read source code from both vertex and fragment shaders
	string vertexSrc, fragmentSrc ;
	readShaderSource("shaders/shader.vert", vertexSrc) ;
	readShaderSource("shaders/shader.frag", fragmentSrc) ;
	vertexShaderSource = vertexSrc.c_str() ;
	fragmentShaderSource = fragmentSrc.c_str() ;

	// Send the source code of the shaders to the GPU
	glShaderSource(vertexID, 1, &vertexShaderSource, NULL) ;
	glShaderSource(fragmentID, 1, &fragmentShaderSource, NULL) ;

	// Compile the source codes
	glCompileShader(vertexID) ;
	glCompileShader(fragmentID) ;

	GLint error ;
	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &error) ;
	if (error != GL_TRUE)
		cerr << "Error on compilation of vertex shader" << endl ;

	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &error) ;
	if (error != GL_TRUE)
		cerr << "Error on compilation of fragment shader!" << endl ;

	// Create the shader program into the pipeline
	programID = glCreateProgram () ;
	// Attach the shaders to the program
	glAttachShader(programID, vertexID) ;
	glAttachShader(programID, fragmentID) ;
	// Link the program
	glLinkProgram(programID) ;

	vertexPositionAttrib = glGetAttribLocation(programID, "VertexPosition") ;
	vertexColorAttrib = glGetAttribLocation(programID, "VertexColor") ;
	uniformID = glGetUniformLocation(programID, "ModelViewProjectionMatrix") ;
}

// Attach a variable from the shader
void bindAttribLocation(GLuint index, const GLchar* name) {
	glBindAttribLocation(programID, index, name) ;
}

// Use shaders
void useShaders() {
	glUseProgram(programID) ;
}

// Do not use shaders anymore
void unuseShaders() {
	glUseProgram(0) ;
}

// Destroy the shaders
void destroyShaders() {
	// Destroy shaders
	glDeleteShader(vertexID) ;
	glDeleteShader(fragmentID) ;

	// Destroy program
	glDeleteProgram(programID) ;
}



GLuint getVertexPositionAttrib() {
	return vertexPositionAttrib ;
}

GLuint getVertexColorAttrib() {
	return vertexColorAttrib ;
}

GLuint getUniformID() {
	return uniformID ;
}
