// Diffuse+normal maps material shader.

layout(binding = 0) uniform sampler2D diffuse ;
layout(binding = 1) uniform sampler2D normal ;
uniform vec3 ambient ;
uniform vec3 specular ;
uniform float shininess ;

layout(location = 0) in mat3 inTBNMatrix ;
layout(location = 3) in vec2 inTexCoord ;

layout(location = 0) out vec4 gAlbedo ;
layout(location = 1) out vec4 gNormal ;
layout(location = 2) out vec4 gSpecular ;

void main() {
    gAlbedo = vec4(texture(diffuse, inTexCoord).rgb, 1.f) ;
    gSpecular = vec4(specular, shininess) ;

    vec3 normalVector = texture(normal, inTexCoord).rgb ;
    gNormal = vec4(AdjustNormalVector(inTBNMatrix, normalVector) * 0.5f + 0.5f, 0.f) ;
}
