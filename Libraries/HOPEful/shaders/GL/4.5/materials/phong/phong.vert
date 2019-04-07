#version 450    // OpenGL 4.5

layout(location = 0) in vec4 vertexCoord ;

uniform mat4 mvpMatrix ;

void main() {
    gl_Position = vertexCoord ;
}
