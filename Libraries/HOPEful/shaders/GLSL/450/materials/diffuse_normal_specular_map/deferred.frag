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

layout(location = 0) out vec4 gAlbedo ;
layout(location = 1) out vec4 gNormal ;
layout(location = 2) out vec4 gSpecular ;
layout(location = 3) out vec4 gPosition ;

void main() {
    gAlbedo = vec4(texture(diffuse, inTexCoord).rgb, 1.f) ;
    gPosition = vec4(inVertexWorldPosition, 1.f) ;

    vec3 specularValue = vec3(texture(specular, inTexCoord).r) ;
    gSpecular = vec4(specularValue, shininess) ;

    vec3 normalVector = texture(normal, inTexCoord).rgb ;
    gNormal = vec4(AdjustNormalVector(inTBNMatrix, normalVector), 0.f) ;
}
