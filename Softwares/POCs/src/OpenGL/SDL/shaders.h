#ifndef __SCORN__SHADERS_TOOLS__
#define __SCORN__SHADERS_TOOLS__

#include <glew.h>
#include <gl.h>

void createShaders() ;

void bindAttribLocation(GLuint index, const GLchar* name) ;

void useShaders() ;

void unuseShaders() ;

void destroyShaders() ;



GLuint getVertexPositionAttrib() ;

GLuint getVertexColorAttrib() ;

GLuint getUniformID() ;

#endif
