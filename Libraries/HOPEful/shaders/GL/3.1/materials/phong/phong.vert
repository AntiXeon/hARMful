#version 140    // OpenGL 3.1

layout(location = 0) in vec4 vertexCoord ;

uniform mat4 mvpMatrix ;

void main() {
    gl_Position = mvpMatrix * vertexCoord ;
}
