// Diffuse material shader using a diffuse map.

struct Material {
    vec3 ambient ;
    layout(binding = 0) sampler2D diffuse ;
    vec3 specular ;
    float shininess ;
} ;

uniform Material material ;

layout(location = 0) in vec3 inVertexWorldPosition ;
layout(location = 1) in vec3 inNormal ;
layout(location = 2) in vec2 inTexCoord ;
layout(location = 3) in vec3 inViewDirection ;

out vec4 outColor ;

void main() {
    FragmentData currentFragment ;
    currentFragment.worldPosition = inVertexWorldPosition ;
    currentFragment.diffuseValue = texture(material.diffuse, inTexCoord).rgb ;
    currentFragment.specularValue = material.specular ;
    currentFragment.normalValue = inNormal ;

    vec3 colorLinear = material.ambient ;
    colorLinear += ComputeLightsContribution(
        inViewDirection,
        currentFragment
    ) ;

    outColor = vec4(colorLinear, 1.f) ;
}
