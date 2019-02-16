#version 140    // OpenGL 3.1

struct MaterialParameters
{
   vec4 ambientColor ;
   vec4 diffuseColor ;
   vec4 specularColor ;
   float shininess ;
} ;

uniform MaterialParameters material ;

void main() {
    FragColor = material.ambientColor ;
}
