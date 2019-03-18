#include <scene/components/materials/shaders/GL/3.1/Phong.hpp>

std::string PhongVertexCode =
"\
#version 140    // OpenGL 3.1\
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
#version 140    // OpenGL 3.1\
\
layout(location = 0) in vec4 ambientColor ;\
layout(location = 1) in vec4 diffuseColor ;\
layout(location = 2) in vec4 specularColor ;\
layout(location = 3) in float shininess ;\
\
layout (location = 0) out vec4 FragColor ;\
\
void main() {\
    FragColor = ambientColor ;\
}\
" ;

