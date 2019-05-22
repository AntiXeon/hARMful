// Material for deferred rendering. Applied on a simple quad on the whole
// viewport area.

layout(binding = 0) uniform sampler2D albedo ;
layout(binding = 1) uniform sampler2D normal ;
layout(binding = 2) uniform sampler2D specular ;
layout(binding = 3) uniform sampler2D position ;

layout(location = 0) in vec2 texCoords ;

out vec4 outColor ;

void main() {
    outColor = vec4(texture(albedo, texCoords).rgb, 1.f) ;
}
