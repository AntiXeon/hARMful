// Diffuse/normal material shader.
struct Material {
    layout(binding = 0) sampler2D diffuse ;
    layout(binding = 1) sampler2D normal ;
    vec3 ambient ;
    vec3 specular ;
    float shininess ;
} ;

uniform Material material ;

layout(location = 0) in vec2 inTexCoord ;
layout(location = 1) in mat3 inTBNMatrix ;

out vec4 outColor ;

void main() {
    vec3 normalVector = texture(material.normal, inTexCoord).rgb ;
    normalVector = AdjustNormalVector(inTBNMatrix, normalVector) ;

    outColor = vec4(normalVector, 1.f) ;
}
