// Diffuse/normal material shader.
layout(location = 0) in vec3 position ;
layout(location = 1) in vec2 texCoord ;
layout(location = 2) in vec3 normal ;
layout(location = 3) in vec3 tangent ;
layout(location = 4) in vec3 bitangent ;

layout(location = 0) out vec2 outTexCoord ;
layout(location = 1) out mat3 outTBNMatrix ;

void correctTBNMatrix() {
    vec3 correctedTangent = normalize(vec3(modelMatrix * vec4(tangent, 0.f))) ;
    vec3 correctedBitangent = normalize(vec3(modelMatrix * vec4(bitangent, 0.f))) ;
    vec3 correctedNormal = normalize(vec3(modelMatrix * vec4(normal, 0.f))) ;
    outTBNMatrix = mat3(correctedTangent, correctedBitangent, correctedNormal) ;
}

void main() {
    correctTBNMatrix() ;
    outTexCoord = texCoord ;
    gl_Position = mvpMatrix * vec4(position, 1.f) ;
}
