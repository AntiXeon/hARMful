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
#version 450 core    // OpenGL 4.5\n\
\n\
struct DirectionalLight {\n\
    vec3 direction ;\n\
    vec3 ambient ;\n\
    vec3 diffuse ;\n\
    vec3 specular ;\n\
} ;\n\
\n\
uniform DirectionalLight dirLight ;\n\
\n\
uniform vec3 eyePosition ;\n\
\n\
layout(location = 0) in vec2 inTexCoord ;\n\
layout(location = 1) in vec3 inNormal ;\n\
layout(location = 2) in vec3 inFragmentPosition ;\n\
\n\
out vec4 color ;\n\
\n\
vec4 DirectionalLightContribution(\n\
    DirectionalLight light,\n\
    vec3 normal,\n\
    vec3 viewDirection\n\
) {\n\
    // Values to be replaced by uniforms.\n\
    vec3 materialDiffuse = vec3(0.2f, 0.2f, 0.2f) ;\n\
    vec3 materialSpecular = vec3(1.f, 1.f, 1.f) ;\n\
    float materialShininess = 64.f ;\n\
\n\
\n\
    vec3 lightDirection = normalize(-light.direction) ;\n\
    float diffuseShading = max(dot(normal, lightDirection), 0.f) ;\n\
    vec3 reflectDirection = reflect(-lightDirection, normal) ;\n\
    float specularShading = pow(max(dot(viewDirection, reflectDirection), 0.f), materialShininess) ;\n\
\n\
    vec3 ambientColor = light.ambient * materialDiffuse ;\n\
    vec3 diffuseColor = light.diffuse * diffuseShading * materialDiffuse ;\n\
    vec3 specularColor = light.specular * specularShading * materialSpecular ;\n\
    return vec4(normalize(ambientColor + diffuseColor + specularColor), 1.f) ;\n\
}\n\
\n\
void main() {\n\
    vec3 viewDirection = normalize(eyePosition - inFragmentPosition);\n\
\n\
    color = DirectionalLightContribution(dirLight, inNormal, viewDirection) ;\n\
}\n\
" ;

