#version 450 core    // OpenGL 4.5

struct DirectionalLight {
    vec3 direction ;
    vec3 ambient ;
    vec3 diffuse ;
    vec3 specular ;
} ;

uniform DirectionalLight dirLight ;

uniform vec3 eyePosition ;

layout(location = 0) in vec2 inTexCoord ;
layout(location = 1) in vec3 inNormal ;
layout(location = 2) in vec3 inFragmentPosition ;

out vec4 color ;

vec4 DirectionalLightContribution(
    DirectionalLight light,
    vec3 normal,
    vec3 viewDirection
) {
    // Values to be replaced by uniforms.
    vec3 materialDiffuse = vec3(0.2f, 0.2f, 0.2f) ;
    vec3 materialSpecular = vec3(1.f, 1.f, 1.f) ;
    float materialShininess = 64.f ;


    vec3 lightDirection = normalize(-light.direction) ;
    float diffuseShading = max(dot(normal, lightDirection), 0.f) ;
    vec3 reflectDirection = reflect(-lightDirection, normal) ;
    float specularShading = pow(max(dot(viewDirection, reflectDirection), 0.f), materialShininess) ;

    vec3 ambientColor = light.ambient * materialDiffuse ;
    vec3 diffuseColor = light.diffuse * diffuseShading * materialDiffuse ;
    vec3 specularColor = light.specular * specularShading * materialSpecular ;
    return vec4(normalize(ambientColor + diffuseColor + specularColor), 1.f) ;
}

void main() {
    vec3 viewDirection = normalize(eyePosition - inFragmentPosition);

    color = DirectionalLightContribution(dirLight, inNormal, viewDirection) ;
}
