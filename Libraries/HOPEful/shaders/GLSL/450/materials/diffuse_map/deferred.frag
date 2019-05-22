// Diffuse map material shader.

uniform vec3 ambient ;
layout(binding = 0) uniform sampler2D diffuse ;
uniform vec3 specular ;
uniform float shininess ;

layout(location = 0) in vec3 inVertexWorldPosition ;
layout(location = 1) in vec2 inTexCoord ;
layout(location = 2) in vec3 inNormal ;

layout(location = 0) out vec4 gAlbedo ;
layout(location = 1) out vec4 gNormal ;
layout(location = 2) out vec4 gSpecular ;
layout(location = 3) out vec4 gPosition ;

void main() {
    gAlbedo = vec4(texture(diffuse, inTexCoord).rgb, 1.f) ;
    gNormal = vec4(normalize(inNormal), 1.f) ;
    gSpecular = vec4(specular, shininess) ;
    gPosition = vec4(inVertexWorldPosition, 1.f) ;
}
