#version 450    // OpenGL 4.5

uniform vec4 ambientColor ;
uniform vec4 diffuseColor ;
uniform vec4 specularColor ;
uniform float shininess ;

layout (location = 0) out vec4 FragColor ;

void main() {
    FragColor = ambientColor ;
}
