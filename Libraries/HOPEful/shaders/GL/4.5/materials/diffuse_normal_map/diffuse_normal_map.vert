layout(location = 0) in vec3 position ;
layout(location = 1) in vec2 texCoord ;
layout(location = 2) in vec3 normal ;
layout(location = 3) in vec3 tangent ;
layout(location = 4) in vec3 bitangent ;

layout(location = 0) out vec3 outVertexWorldPosition ;
layout(location = 1) out vec3 outNormal ;
layout(location = 2) out mat3 outTBNMatrix ;
layout(location = 5) out vec2 outTexCoord ;
layout(location = 6) out vec3 outViewDirection ;

void correctTBNMatrix() {
    vec3 correctedTangent = normalize(vec3(normalMatrix * vec4(tangent, 0.f))) ;
    vec3 correctedBitangent = normalize(vec3(normalMatrix * vec4(bitangent, 0.f))) ;
    vec3 correctedNormal = normalize(vec3(normalMatrix * vec4(normal, 0.f))) ;
    outTBNMatrix = mat3(correctedTangent, correctedBitangent, correctedNormal) ;
}

void main() {
    correctTBNMatrix() ;

    vec4 position4D = vec4(position, 1.f) ;

    gl_Position = mvpMatrix * position4D ;

    vec4 vertexPosition4D = modelViewMatrix * vec4(position, 1.f) ;
    outVertexWorldPosition = vec3(vertexPosition4D) / vertexPosition4D.w ;
    outNormal = normalize(vec3(normalMatrix * vec4(normal, 0.f))) ;
    outTexCoord = texCoord ;
    outViewDirection = normalize(-outVertexWorldPosition) ;
}
