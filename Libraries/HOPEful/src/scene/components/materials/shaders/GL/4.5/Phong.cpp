#include <scene/components/materials/shaders/GL/4.5/Phong.hpp>

std::string PhongVertexCode =
"\
#version 450    // OpenGL 4.5\
\
layout(location = 0) in vec4 vertexCoord ;\
\
uniform mat4 mvpMatrix ;\
\
void main() {\
    gl_Position = mvpMatrix * vertexCoord ;\
}\
" ;

std::string PhongFragmentCode =
"\
#version 450    // OpenGL 4.5\
\
uniform vec4 ambientColor ;\
uniform vec4 diffuseColor ;\
uniform vec4 specularColor ;\
uniform float shininess ;\
\
layout (location = 0) out vec4 FragColor ;\
\
void main() {\
    FragColor = ambientColor ;\
}\
" ;

