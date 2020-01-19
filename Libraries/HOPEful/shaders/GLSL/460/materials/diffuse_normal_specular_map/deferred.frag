// Diffuse+normal+specular maps material shader.

layout(binding = 0) uniform sampler2D diffuse ;
layout(binding = 1) uniform sampler2D normal ;
layout(binding = 2) uniform sampler2D specular ;
layout(location = 0) uniform vec3 ambient ;
layout(location = 3) uniform float shininess ;

layout(location = 0) in mat3 inTBNMatrix ;
layout(location = 3) in vec2 inTexCoord ;

layout(location = 0) out vec4 gAlbedo ;
layout(location = 1) out vec4 gSpecular ;
layout(location = 2) out vec4 gNormal ;

void main() {
    gAlbedo = vec4(texture(diffuse, inTexCoord).rgb, 1.f) ;

    vec3 specularValue = vec3(texture(specular, inTexCoord).r) ;
    gSpecular = vec4(specularValue, shininess) ;

    vec3 normalVector = texture(normal, inTexCoord).rgb ;
    normalVector = AdjustNormalVector(inTBNMatrix, normalVector) ;
    gNormal = vec4(EncodeSpheremapNormals(normalVector), 0.f, 0.f) ;
}
