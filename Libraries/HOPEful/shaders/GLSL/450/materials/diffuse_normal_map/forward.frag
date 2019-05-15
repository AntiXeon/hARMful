// Blinn-Phong material shader using diffuse and normal maps.

struct Material {
    layout(binding = 0) sampler2D diffuse ;
    layout(binding = 1) sampler2D normal ;
    vec3 ambient ;
    vec3 specular ;
    float shininess ;
} ;

uniform Material material ;

layout(location = 0) in vec3 inVertexWorldPosition ;
layout(location = 1) in vec3 inNormal ;
layout(location = 2) in mat3 inTBNMatrix ;
layout(location = 5) in vec2 inTexCoord ;
layout(location = 6) in vec3 inViewDirection ;

out vec4 outColor ;

void main() {
    FragmentData currentFragment ;
    currentFragment.worldPosition = inVertexWorldPosition ;
    currentFragment.diffuseValue = texture(material.diffuse, inTexCoord).rgb ;
    currentFragment.specularValue = material.specular ;
    vec3 normalVector = texture(material.normal, inTexCoord).rgb ;
    currentFragment.normalValue = AdjustNormalVector(inTBNMatrix, normalVector) ;

    vec3 colorLinear = material.ambient ;
    colorLinear += ComputeLightsContribution(
        inViewDirection,
        currentFragment
    ) ;

    outColor = vec4(colorLinear, 1.f) ;
}
