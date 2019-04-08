#version 450 core    // OpenGL 4.5

layout (location = 0) in vec3 position ;

void main() {
    gl_Position = vec4(position, 1.f) ;
}
