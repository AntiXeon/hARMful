// Diffuse map material shader.

uniform vec3 ambient ;
layout(binding = 0) uniform sampler2D diffuse ;
uniform vec3 specular ;
uniform float shininess ;

layout(location = 0) in vec2 inTexCoord ;
layout(location = 1) in vec3 inNormal ;

layout(location = 0) out vec4 gAlbedo ;
layout(location = 1) out vec4 gNormal ;
layout(location = 2) out vec4 gSpecular ;

void main() {
    gAlbedo = vec4(texture(diffuse, inTexCoord).rgb, 1.f) ;
    gNormal = vec4(normalize(inNormal) * 0.5f + 0.5f, 0.f) ;
    gSpecular = vec4(specular, shininess) ;
}
