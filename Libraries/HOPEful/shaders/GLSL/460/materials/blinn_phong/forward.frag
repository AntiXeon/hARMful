// Blinn-Phong material shader.

layout(location = 0) uniform vec3 ambient ;
layout(location = 1) uniform vec3 diffuse ;
layout(location = 2) uniform vec3 specular ;
layout(location = 3) uniform float shininess ;

const float ScreenGamma = 2.2f ;

layout(location = 0) in vec3 inVertexWorldPosition ;
layout(location = 1) in vec3 inNormal ;
layout(location = 2) in vec3 inViewDirection ;

out vec4 outColor ;

void main() {
    FragmentData currentFragment ;
    currentFragment.position = vec4(inVertexWorldPosition, 1.f) ;
    currentFragment.diffuseValue = diffuse ;
    currentFragment.specularValue = specular ;
    currentFragment.normalValue = inNormal ;
    currentFragment.shininess = shininess ;

    vec3 colorLinear = ambient + ComputeLightsContribution(inViewDirection, currentFragment) ;
    vec3 colorGammaCorrected = pow(colorLinear, vec3(1.f / ScreenGamma)) ;
    outColor = vec4(colorGammaCorrected, 1.f) ;
}
