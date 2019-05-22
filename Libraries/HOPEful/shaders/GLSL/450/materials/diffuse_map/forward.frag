// Diffuse map material shader.

uniform vec3 ambient ;
layout(binding = 0) uniform sampler2D diffuse ;
uniform vec3 specular ;
uniform float shininess ;

layout(location = 0) in vec3 inVertexWorldPosition ;
layout(location = 1) in vec3 inNormal ;
layout(location = 2) in vec2 inTexCoord ;
layout(location = 3) in vec3 inViewDirection ;

out vec4 outColor ;

void main() {
    FragmentData currentFragment ;
    currentFragment.worldPosition = inVertexWorldPosition ;
    currentFragment.diffuseValue = texture(diffuse, inTexCoord).rgb ;
    currentFragment.specularValue = specular ;
    currentFragment.normalValue = inNormal ;

    vec3 colorLinear = ambient ;
    colorLinear += ComputeLightsContribution(
        inViewDirection,
        currentFragment
    ) ;

    outColor = vec4(colorLinear, 1.f) ;
}
