// Screen-space ambient occlusion blur and copy.

layout(binding = 0) uniform sampler2D ao ;
layout(binding = 1) uniform sampler2D normal ;
layout(binding = 2) uniform sampler2D specular ;
layout(binding = 3) uniform sampler2D depth ;

layout(location = 0) in vec2 inTexCoords ;

layout(location = 0) out vec4 gAlbedoAO ;
layout(location = 1) out vec4 gNormal ;
layout(location = 3) out vec4 gSpecular ;

void main() {
    gAlbedoAO = texture(ao, inTexCoords).rgba ;
    gNormal = texture(normal, inTexCoords).rgba ;
    gSpecular = texture(specular, inTexCoords).rgba ;
    gl_FragDepth = texture(depth, inTexCoords).r ;
}
