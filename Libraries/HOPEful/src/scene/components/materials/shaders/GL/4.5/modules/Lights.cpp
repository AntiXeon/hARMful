#include <scene/components/materials/shaders/GL/4.5/modules/Lights.hpp>

std::string LightsFragmentCode =
"\
struct DirectionalLight {\n\
    vec3 direction ;\n\
    vec3 ambient ;\n\
    vec3 diffuse ;\n\
    vec3 specular ;\n\
} ;\n\
\n\
uniform DirectionalLight dirLight ;\n\
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
" ;

