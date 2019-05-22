// Diffuse+normal+specular maps material shader.

layout(binding = 0) uniform sampler2D diffuse ;
layout(binding = 1) uniform sampler2D normal ;
layout(binding = 2) uniform sampler2D specular ;
uniform vec3 ambient ;
uniform float shininess ;

layout(location = 0) in vec3 inVertexWorldPosition ;
layout(location = 1) in vec3 inNormal ;
layout(location = 2) in mat3 inTBNMatrix ;
layout(location = 5) in vec2 inTexCoord ;
layout(location = 6) in vec3 inViewDirection ;

out vec4 outColor ;

void main() {
    FragmentData currentFragment ;
    currentFragment.worldPosition = inVertexWorldPosition ;
    currentFragment.diffuseValue = texture(diffuse, inTexCoord).rgb ;
    currentFragment.specularValue = vec3(texture(specular, inTexCoord).r) ;
    vec3 normalVector = texture(normal, inTexCoord).rgb ;
    currentFragment.normalValue = AdjustNormalVector(inTBNMatrix, normalVector) ;

    vec3 colorLinear = ambient ;
    colorLinear += ComputeLightsContribution(
        inViewDirection,
        currentFragment
    ) ;

    outColor = vec4(colorLinear, 1.f) ;
}
