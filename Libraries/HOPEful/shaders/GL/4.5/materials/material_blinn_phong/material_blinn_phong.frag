// Blinn-Phong material shader.

struct Material {
    vec3 ambient ;
    vec3 diffuse ;
    vec3 specular ;
    float shininess ;
} ;

uniform Material material ;

const float ScreenGamma = 2.2f ;

layout(location = 0) in vec3 inVertexWorldPosition ;
layout(location = 1) in vec3 inNormal ;
layout(location = 2) in vec2 inTexCoord ;
layout(location = 3) in vec3 inViewDirection ;

out vec4 outColor ;

void main() {
    FragmentData currentFragment ;
    currentFragment.worldPosition = inVertexWorldPosition ;
    currentFragment.diffuseValue = material.diffuse ;
    currentFragment.specularValue = material.specular ;
    currentFragment.normalValue = inNormal ;

    vec3 colorLinear = material.ambient + ComputeLightsContribution(inViewDirection, currentFragment) ;
    vec3 colorGammaCorrected = pow(colorLinear, vec3(1.f / ScreenGamma)) ;
    outColor = vec4(colorGammaCorrected, 1.f) ;
}
