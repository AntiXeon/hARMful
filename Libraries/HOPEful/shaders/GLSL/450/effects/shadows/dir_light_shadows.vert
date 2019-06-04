// Depth map for directional light shadows.

layout(location = 0) in vec3 position ;

uniform mat4 modelLightSpaceMatrix ;

void main() {
    gl_Position = modelLightSpaceMatrix * vec4(position, 1.f) ;
}
