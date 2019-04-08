#include <scene/components/materials/shaders/GL/4.5/Phong.hpp>

std::string PhongVertexCode =
"\
#version 450 core    // OpenGL 4.5\n\
\n\
layout (location = 0) in vec3 position ;\n\
\n\
uniform mat4 mvpMatrix ;\n\
\n\
void main() {\n\
    gl_Position = mvpMatrix * vec4(position, 1.f) ;\n\
}\n\
" ;

std::string PhongFragmentCode =
"\
#version 450 core    // OpenGL 4.5\n\
\n\
out vec4 color ;\n\
\n\
void main() {\n\
    color = vec4(0.f, 1.f, 0.f, 1.f) ;\n\
}\n\
" ;

