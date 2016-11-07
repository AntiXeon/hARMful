#include <assert.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>

#include <glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "matrix.h"
#include "parser.h"
#include "shaders.h"

using namespace std ;


#define SCREEN_WIDTH			800.f
#define SCREEN_HEIGHT			480.f
#define SCREEN_RATIO 			SCREEN_WIDTH / SCREEN_HEIGHT

// Matrix used to correctly see the scene
Matrix4 worldViewProjectionMatrix ;
// Vertex Array Object index
GLuint vaoIndex = 0 ;

#define CUBE_BUFFER_SIZE		2
GLuint SuzanneBuffers[CUBE_BUFFER_SIZE] ;
GLfloat* SuzanneArray = NULL ;
GLuint SuzanneArraySize = 0 ;
GLuint* SuzanneIndices = NULL ;
GLuint SuzanneIndicesSize = 0 ;


// Create the VBO where to store the geometry of the 3D model
void createVBO() {
	// Generate the buffers
	glGenBuffers(CUBE_BUFFER_SIZE, SuzanneBuffers) ;

	// Buffer containing the vertice description
	glBindBuffer(GL_ARRAY_BUFFER, SuzanneBuffers[0]) ;
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * SuzanneArraySize, SuzanneArray, GL_STATIC_DRAW) ;

	// Buffer containg the indices of the vertices positions and normals
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SuzanneBuffers[1]) ;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * SuzanneIndicesSize, SuzanneIndices, GL_STATIC_DRAW) ;
}


// Create a Vertex Array Object
void createVAO() {
	// Create the VAO
	glGenVertexArrays(1, &vaoIndex) ;
	assert(vaoIndex > 0) ;
	// Bind it
	glBindVertexArray(vaoIndex) ;

	// Bind VBOs to VAOs
	glEnableVertexAttribArray(getVertexPositionAttrib()) ;
	glEnableVertexAttribArray(getVertexColorAttrib()) ;

	// Use the array containg the geometry data
	glBindBuffer(GL_ARRAY_BUFFER, SuzanneBuffers[0]) ;

	// Send data
	glVertexAttribPointer(getVertexColorAttrib(), 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (float *) NULL + (0)) ;
	glVertexAttribPointer(getVertexPositionAttrib(), 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (float*) NULL + (3)) ;

	// Array containg the indices of the vertice
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SuzanneBuffers[1]) ;

	// Unbind the VAO
	glBindVertexArray(0) ;
}


// Set up the camera
void cameraSetup() {
	// Create the transformation matrices
	Matrix4 projectionMatrix ;
	projectionMatrix.SetProjectionMatrix(60.f, SCREEN_RATIO, 1.f, 500.f) ;

	Matrix4 worldMatrix ;
	worldMatrix.SetTransformationMatrix(0.f, -0.1f, -2.f) ;
	worldViewProjectionMatrix = projectionMatrix * worldMatrix ;

	glClearColor(0.2f, 0.2f, 0.2f, 1.f) ;
}

// Destroy the Vertex Array Object
void destroyVAO() {
	glDeleteVertexArrays(1, &vaoIndex) ;
}


// Main display function.
void render(SDL_Window* display) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT) ;


	// Use the shader program in the pipeline
	useShaders() ;
	glUniformMatrix4fv(getUniformID(), 1, GL_FALSE, worldViewProjectionMatrix.GetMatrixForOpenGL()) ;

	// Bind the VAO to use
	glBindVertexArray(vaoIndex) ;
	// Render the geometry according to the vertice and indexes descriptions
	glDrawElements(GL_TRIANGLES, SuzanneIndicesSize, GL_UNSIGNED_INT, 0) ;
	glBindVertexArray(0) ;
	unuseShaders() ;

	SDL_GL_SwapWindow(display) ;
}

// Load the Suzanne mesh.
void loadSuzanne() {
	string path = "models/Farmhouse OBJ.obj" ;
	vector<GLfloat> data ;
	vector<GLuint> verticeIndices ;

	readOBJ(path, data, verticeIndices) ;
	cout << "File loaded: " << path << endl ;

	// Copy vertice position
	SuzanneArraySize = data.size() ;
	SuzanneArray = new GLfloat[SuzanneArraySize] ;
	for (int i = 0 ; i < SuzanneArraySize ; i++) {
		SuzanneArray[i] = data[i] ;
	}

	// Copy vertex indices
	SuzanneIndicesSize = verticeIndices.size() ;
	SuzanneIndices = new GLuint[SuzanneIndicesSize] ;
	for (int i = 0 ; i < SuzanneIndicesSize ; i++)
		SuzanneIndices[i] = verticeIndices[i] ;
}



SDL_Window* initSDL() {
	SDL_Init(SDL_INIT_VIDEO) ;
	SDL_Window* displayWindow ;
	displayWindow = SDL_CreateWindow("OpenGL with SDL2", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL) ;
	SDL_GL_CreateContext(displayWindow) ;

	return displayWindow ;
}

void initGL() {
	glewInit() ;

	glEnable(GL_DEPTH_TEST) ;
	// ... More enabled/disabled stuff here ...
}


int main(int argc, char** argv) {
	SDL_Window* SDLWindow = initSDL() ;
	initGL() ;
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT) ;

	cameraSetup() ;
	createShaders() ;
	loadSuzanne() ;
	createVBO() ;
	createVAO() ;


	bool run = true ;
	while (run) {
		render(SDLWindow) ;
		sleep(1) ;
	}

	return 0 ;
}
