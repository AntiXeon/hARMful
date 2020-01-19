// Diffuse map material shader.

layout(location = 0) in vec3 position ;
layout(location = 1) in vec2 texCoord ;
layout(location = 2) in vec3 normal ;

layout(location = 0) out vec2 outTexCoord ;
layout(location = 1) out vec3 outNormal ;

void main() {
    vec4 position4D = vec4(position, 1.f) ;
    gl_Position = mvpMatrix * position4D ;

    outTexCoord = texCoord ;
    outNormal = (normalMatrix * vec4(normal, 0.f)).xyz ;
}
