// Diffuse+normal maps material shader.

layout(binding = 0) uniform sampler2D diffuse ;
layout(binding = 1) uniform sampler2D normal ;
layout(location = 0) uniform vec3 ambient ;
layout(location = 2) uniform vec3 specular ;
layout(location = 3) uniform float shininess ;

layout(location = 0) in vec3 inVertexWorldPosition ;
layout(location = 1) in vec3 inNormal ;
layout(location = 2) in mat3 inTBNMatrix ;
layout(location = 5) in vec2 inTexCoord ;
layout(location = 6) in vec3 inViewDirection ;

out vec4 outColor ;

void main() {
    FragmentData currentFragment ;
    currentFragment.position = vec4(inVertexWorldPosition, 1.f) ;
    currentFragment.diffuseValue = texture(diffuse, inTexCoord).rgb ;
    currentFragment.specularValue = specular ;
    vec3 normalVector = texture(normal, inTexCoord).rgb ;
    currentFragment.normalValue = AdjustNormalVector(inTBNMatrix, normalVector) ;

    vec3 colorLinear = ambient ;
    colorLinear += ComputeLightsContribution(
        inViewDirection,
        currentFragment
    ) ;

    outColor = vec4(colorLinear, 1.f) ;
}
