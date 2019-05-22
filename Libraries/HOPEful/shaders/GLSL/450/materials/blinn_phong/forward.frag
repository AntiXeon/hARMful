// Blinn-Phong material shader.

uniform vec3 ambient ;
uniform vec3 diffuse ;
uniform vec3 specular ;
uniform float shininess ;

const float ScreenGamma = 2.2f ;

layout(location = 0) in vec3 inVertexWorldPosition ;
layout(location = 1) in vec3 inNormal ;
layout(location = 2) in vec2 inTexCoord ;
layout(location = 3) in vec3 inViewDirection ;

out vec4 outColor ;

void main() {
    FragmentData currentFragment ;
    currentFragment.worldPosition = inVertexWorldPosition ;
    currentFragment.diffuseValue = diffuse ;
    currentFragment.specularValue = specular ;
    currentFragment.normalValue = inNormal ;
    currentFragment.shininess = shininess ;

    vec3 colorLinear = ambient + ComputeLightsContribution(inViewDirection, currentFragment) ;
    vec3 colorGammaCorrected = pow(colorLinear, vec3(1.f / ScreenGamma)) ;
    outColor = vec4(colorGammaCorrected, 1.f) ;
}
