#version 140    // OpenGL 3.1

struct MaterialParameters
{
   vec4 ambientColor ;
   vec4 diffuseColor ;
   vec4 specularColor ;
   float shininess ;
} ;

uniform MaterialParameters material ;

layout (location = 0) out vec4 FragColor ;

void main() {
    FragColor = material.ambientColor ;
}
