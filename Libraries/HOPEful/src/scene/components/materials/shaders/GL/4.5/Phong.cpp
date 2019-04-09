#include <scene/components/materials/shaders/GL/4.5/Phong.hpp>

std::string PhongVertexCode =
"\
#version 450 core    // OpenGL 4.5\n\
\n\
layout(location = 0) in vec3 position ;\n\
layout(location = 1) in vec2 texCoord ;\n\
layout(location = 2) in vec3 normal ;\n\
\n\
uniform mat4 mvpMatrix ;\n\
\n\
layout(location = 0) out vec2 outTexCoord ;\n\
layout(location = 1) out vec3 outNormal ;\n\
\n\
void main() {\n\
    gl_Position = mvpMatrix * vec4(position, 1.f) ;\n\
\n\
    outTexCoord = texCoord ;\n\
    outNormal = normal ;\n\
}\n\
" ;

std::string PhongFragmentCode =
"\
#version 450 core    // OpenGL 4.5\n\
\n\
layout(location = 0) in vec2 outTexCoord ;\n\
layout(location = 1) in vec3 outNormal ;\n\
\n\
out vec4 color ;\n\
\n\
void main() {\n\
    color = vec4(0.f, 1.f, 0.f, 1.f) * vec4(-outNormal, 1.f) ;\n\
}\n\
" ;

