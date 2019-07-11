// Screen-space ambient occlusion blur and copy.

layout(binding = 0) uniform sampler2D ao ;

layout(location = 0) in vec2 inTexCoords ;

layout(location = 0) out vec4 gAlbedoAO ;

void main() {
    gAlbedoAO = texture(ao, inTexCoords).rgba ;
}
