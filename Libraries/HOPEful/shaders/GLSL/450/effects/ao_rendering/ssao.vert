// Screen-space ambient occlusion.

layout(location = 0) in vec3 position ;
layout(location = 1) in vec2 texCoords ;

layout(location = 0) out vec2 outTexCoords ;

void main() {
    outTexCoords = texCoords ;
    gl_Position = vec4(position, 1.f) ;
}
