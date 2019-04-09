#version 450 core    // OpenGL 4.5

layout(location = 0) in vec2 outTexCoord ;
layout(location = 1) in vec3 outNormal ;

out vec4 color ;

void main() {
    color = vec4(0.f, 1.f, 0.f, 1.f) * vec4(-outNormal, 1.f) ;
}
