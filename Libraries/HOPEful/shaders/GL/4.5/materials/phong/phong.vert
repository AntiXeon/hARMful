#version 450 core    // OpenGL 4.5

layout (location = 0) in vec3 position ;

uniform mat4 mvpMatrix ;

void main() {
    gl_Position = mvpMatrix * vec4(position, 1.f) ;
}
