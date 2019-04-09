#version 450 core    // OpenGL 4.5

layout(location = 0) in vec3 position ;
layout(location = 1) in vec2 texCoord ;
layout(location = 2) in vec3 normal ;

uniform mat4 mvpMatrix ;

layout(location = 0) out vec2 outTexCoord ;
layout(location = 1) out vec3 outNormal ;

void main() {
    gl_Position = mvpMatrix * vec4(position, 1.f) ;

    outTexCoord = texCoord ;
    outNormal = normal ;
}
