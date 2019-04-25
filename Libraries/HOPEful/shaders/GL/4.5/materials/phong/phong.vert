layout(location = 0) in vec3 position ;
layout(location = 1) in vec2 texCoord ;
layout(location = 2) in vec3 normal ;

layout(location = 0) out vec3 outVertexPosition ;
layout(location = 1) out vec3 outNormal ;
layout(location = 2) out vec2 outTexCoord ;

void main() {
    vec4 position4D = vec4(position, 1.f) ;

    gl_Position = mvpMatrix * position4D ;

    vec4 vertexPosition4D = modelViewMatrix * vec4(position, 1.f) ;
    outVertexPosition = vec3(vertexPosition4D) / vertexPosition4D.w ;
    outNormal = vec3(normalMatrix * vec4(normal, 0.f)) ;
    outTexCoord = texCoord ;
}
