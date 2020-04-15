// Material for displaying the result of deferred rendering. Applied on a simple
// quad on the whole viewport area.

layout(binding = 0) uniform sampler2D albedo ;

layout(location = 0) in vec2 inTexCoords ;

out vec4 outColor ;

void main() {
    outColor = vec4(texture(albedo, inTexCoords).rgb, 1.f) ;
}
