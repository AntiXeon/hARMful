#ifndef __OBJ_PARSER__
#define __OBJ_PARSER__

#include <gl.h>
#include <string>
#include <vector>

void readOBJ(const std::string& path,
             std::vector<GLfloat>& vertice,
             std::vector<GLuint>& verticeArray) ;

#endif
