#version 140    // OpenGL 3.1

uniform mat4 mvpMatrix ;

void main() {
    gl_Position = mvpMatrix * gl_Vertex ;
}
