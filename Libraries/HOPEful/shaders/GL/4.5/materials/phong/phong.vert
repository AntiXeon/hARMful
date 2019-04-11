#version 450 core    // OpenGL 4.5

layout(location = 0) in vec3 position ;
layout(location = 1) in vec2 texCoord ;
layout(location = 2) in vec3 normal ;

uniform mat4 mvpMatrix ;
uniform mat4 modelMatrix ;

layout(location = 0) out vec2 outTexCoord ;
layout(location = 1) out vec3 outNormal ;
layout(location = 2) out vec3 outFragmentPosition ;

void main() {
    vec4 position4D = vec4(position, 1.f) ;

    outTexCoord = texCoord ;
    outNormal = normalize(mat3(transpose(inverse(modelMatrix))) * normal) ;
    outFragmentPosition = vec3(modelMatrix * position4D) ;

    gl_Position = mvpMatrix * position4D ;
}
