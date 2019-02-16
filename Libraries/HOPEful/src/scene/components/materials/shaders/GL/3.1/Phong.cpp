#include <scene/components/materials/shaders/GL/3.1/Phong.hpp>

std::string PhongVertexCode =
"                                           \
#version 140    // OpenGL 3.1               \
                                            \
uniform mat4 mvpMatrix ;                    \
                                            \
void main() {                               \
    gl_Position = mvpMatrix * gl_Vertex ;   \
}                                           \
" ;

std::string PhongFragmentCode =
"                                           \
#version 140    // OpenGL 3.1               \
                                            \
struct MaterialParameters                   \
{                                           \
   vec4 ambientColor ;                      \
   vec4 diffuseColor ;                      \
   vec4 specularColor ;                     \
   float shininess ;                        \
} ;                                         \
                                            \
uniform MaterialParameters material ;       \
                                            \
void main() {                               \
    FragColor = material.ambientColor ;     \
}                                           \
" ;
