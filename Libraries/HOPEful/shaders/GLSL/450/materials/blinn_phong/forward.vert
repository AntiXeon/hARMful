// Blinn-Phong material shader.

layout(location = 0) in vec3 position ;
layout(location = 1) in vec2 texCoord ;
layout(location = 2) in vec3 normal ;

layout(location = 0) out vec3 outVertexWorldPosition ;
layout(location = 1) out vec3 outNormal ;
layout(location = 2) out vec2 outTexCoord ;
layout(location = 3) out vec3 outViewDirection ;

void main() {
    vec4 position4D = vec4(position, 1.f) ;

    gl_Position = mvpMatrix * position4D ;

    vec4 vertexPosition4D = modelViewMatrix * position4D ;
    outVertexWorldPosition = vec3(vertexPosition4D) / vertexPosition4D.w ;
    outNormal = normalize(vec3(normalMatrix * vec4(normal, 0.f))) ;
    outTexCoord = texCoord ;
    outViewDirection = normalize(-outVertexWorldPosition) ;
}
