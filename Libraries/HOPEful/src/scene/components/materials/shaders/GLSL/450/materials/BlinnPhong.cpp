// WARNING: This file is automatically generated. Any manual modification will be removed.
#include <scene/components/materials/shaders/GLSL/450/materials/BlinnPhong.hpp>

std::string BlinnPhongDeferredVertexCode =
"\
// Blinn-Phong material shader.\n\
\n\
layout(location = 0) in vec3 position ;\n\
layout(location = 2) in vec3 normal ;\n\
\n\
layout(location = 0) out vec3 outVertexWorldPosition ;\n\
layout(location = 1) out vec3 outNormal ;\n\
\n\
void main() {\n\
    vec4 position4D = vec4(position, 1.f) ;\n\
    gl_Position = mvpMatrix * position4D ;\n\
\n\
    outVertexWorldPosition = (modelMatrix * position4D).xyz ;\n\
    outNormal = (modelMatrix * vec4(normal, 0.f)).xyz ;\n\
}\n\
" ;

std::string BlinnPhongDeferredFragmentCode =
"\
// Blinn-Phong material shader.\n\
\n\
uniform vec3 ambient ;\n\
uniform vec3 diffuse ;\n\
uniform vec3 specular ;\n\
uniform float shininess ;\n\
\n\
layout(location = 0) in vec3 inVertexWorldPosition ;\n\
layout(location = 1) in vec3 inNormal ;\n\
\n\
layout(location = 0) out vec4 gAlbedo ;\n\
layout(location = 1) out vec4 gNormal ;\n\
layout(location = 2) out vec4 gSpecular ;\n\
layout(location = 3) out vec4 gPosition ;\n\
\n\
void main() {\n\
    gAlbedo = vec4(diffuse, 1.f) ;\n\
    gNormal = vec4(normalize(inNormal), 1.f) ;\n\
    gSpecular = vec4(specular, shininess) ;\n\
    gPosition = vec4(inVertexWorldPosition, 1.f) ;\n\
}\n\
" ;

std::string BlinnPhongForwardVertexCode =
"\
// Blinn-Phong material shader.\n\
\n\
layout(location = 0) in vec3 position ;\n\
layout(location = 1) in vec2 texCoord ;\n\
layout(location = 2) in vec3 normal ;\n\
\n\
layout(location = 0) out vec3 outVertexWorldPosition ;\n\
layout(location = 1) out vec3 outNormal ;\n\
layout(location = 2) out vec2 outTexCoord ;\n\
layout(location = 3) out vec3 outViewDirection ;\n\
\n\
void main() {\n\
    vec4 position4D = vec4(position, 1.f) ;\n\
\n\
    gl_Position = mvpMatrix * position4D ;\n\
\n\
    vec4 vertexPosition4D = modelViewMatrix * position4D ;\n\
    outVertexWorldPosition = vec3(vertexPosition4D) / vertexPosition4D.w ;\n\
    outNormal = normalize(vec3(normalMatrix * vec4(normal, 0.f))) ;\n\
    outTexCoord = texCoord ;\n\
    outViewDirection = normalize(-outVertexWorldPosition) ;\n\
}\n\
" ;

std::string BlinnPhongForwardFragmentCode =
"\
// Blinn-Phong material shader.\n\
\n\
uniform vec3 ambient ;\n\
uniform vec3 diffuse ;\n\
uniform vec3 specular ;\n\
uniform float shininess ;\n\
\n\
const float ScreenGamma = 2.2f ;\n\
\n\
layout(location = 0) in vec3 inVertexWorldPosition ;\n\
layout(location = 1) in vec3 inNormal ;\n\
layout(location = 2) in vec2 inTexCoord ;\n\
layout(location = 3) in vec3 inViewDirection ;\n\
\n\
out vec4 outColor ;\n\
\n\
void main() {\n\
    FragmentData currentFragment ;\n\
    currentFragment.worldPosition = inVertexWorldPosition ;\n\
    currentFragment.diffuseValue = diffuse ;\n\
    currentFragment.specularValue = specular ;\n\
    currentFragment.normalValue = inNormal ;\n\
    currentFragment.shininess = shininess ;\n\
\n\
    vec3 colorLinear = ambient + ComputeLightsContribution(inViewDirection, currentFragment) ;\n\
    vec3 colorGammaCorrected = pow(colorLinear, vec3(1.f / ScreenGamma)) ;\n\
    outColor = vec4(colorGammaCorrected, 1.f) ;\n\
}\n\
" ;

