// Depth map for directional light shadows.

layout(location = 0) in vec3 position ;

void main() {
    gl_Position = mvpMatrix * vec4(position, 1.f) ;
}
