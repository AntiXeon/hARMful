// Diffuse/normal/specular material shader.
layout(location = 0) in vec3 position ;
layout(location = 1) in vec2 texCoord ;

layout(location = 0) out vec2 outTexCoord ;

void main() {
    gl_Position = mvpMatrix * vec4(position, 1.f) ;
    outTexCoord = texCoord ;
}
