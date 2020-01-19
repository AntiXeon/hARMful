// Diffuse map material shader.

layout(location = 0) uniform vec3 ambient ;
layout(binding = 0) uniform sampler2D diffuse ;
layout(location = 2) uniform vec3 specular ;
layout(location = 3) uniform float shininess ;

layout(location = 0) in vec3 inVertexWorldPosition ;
layout(location = 1) in vec3 inNormal ;
layout(location = 2) in vec2 inTexCoord ;
layout(location = 3) in vec3 inViewDirection ;

out vec4 outColor ;

void main() {
    FragmentData currentFragment ;
    currentFragment.position = inVertexWorldPosition ;
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
