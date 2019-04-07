#include <scene/components/materials/shaders/GL/4.5/Phong.hpp>

std::string PhongVertexCode =
"\
#version 450    // OpenGL 4.5\n\
\n\
layout(location = 0) in vec4 vertexCoord ;\n\
\n\
uniform mat4 mvpMatrix ;\n\
\n\
void main() {\n\
    gl_Position = vertexCoord ;\n\
}\n\
" ;

std::string PhongFragmentCode =
"\
#version 450    // OpenGL 4.5\n\
\n\
uniform vec4 ambientColor ;\n\
uniform vec4 diffuseColor ;\n\
uniform vec4 specularColor ;\n\
uniform float shininess ;\n\
\n\
layout(location = 0) out vec4 fragColor ;\n\
\n\
void main() {\n\
    fragColor = vec4(1.f, 1.f, 1.f, 1.f) ;\n\
}\n\
" ;

