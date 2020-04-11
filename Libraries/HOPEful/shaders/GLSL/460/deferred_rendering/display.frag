// Material for displaying the result of deferred rendering. Applied on a simple
// quad on the whole viewport area.

layout(binding = 0) uniform sampler2D albedo ;

layout(location = 0) in vec2 inTexCoords ;

out vec4 outColor ;

void main() {
	const float Gamma = 2.2f ;
	vec3 correctedColor = pow(texture(albedo, inTexCoords).rgb, vec3(1.f / Gamma)) ;
    outColor = vec4(correctedColor, 1.f) ;
}
