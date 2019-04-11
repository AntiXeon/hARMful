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
uniform mat4 modelMatrix ;\n\
\n\
layout(location = 0) out vec2 outTexCoord ;\n\
layout(location = 1) out vec3 outNormal ;\n\
layout(location = 2) out vec3 outFragmentPosition ;\n\
\n\
void main() {\n\
    vec4 position4D = vec4(position, 1.f) ;\n\
\n\
    outTexCoord = texCoord ;\n\
    outNormal = normalize(mat3(transpose(inverse(modelMatrix))) * normal) ;\n\
    outFragmentPosition = vec3(modelMatrix * position4D) ;\n\
\n\
    gl_Position = mvpMatrix * position4D ;\n\
}\n\
" ;

std::string PhongFragmentCode =
"\
uniform vec3 eyePosition ;\n\
\n\
layout(location = 0) in vec2 inTexCoord ;\n\
layout(location = 1) in vec3 inNormal ;\n\
layout(location = 2) in vec3 inFragmentPosition ;\n\
\n\
out vec4 color ;\n\
\n\
void main() {\n\
    vec3 viewDirection = normalize(eyePosition - inFragmentPosition);\n\
    color = DirectionalLightContribution(dirLight, inNormal, viewDirection) ;\n\
}\n\
" ;

