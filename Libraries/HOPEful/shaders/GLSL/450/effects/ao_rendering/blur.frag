// Screen-space ambient occlusion blur and copy.

layout(binding = 0) uniform sampler2D ao ;

layout(location = 0) in vec2 inTexCoords ;

out vec4 fragColor ;

void main() {
    fragColor = texture(ao, inTexCoords) ;
}
