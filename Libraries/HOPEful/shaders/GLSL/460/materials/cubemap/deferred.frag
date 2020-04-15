// Cubemap material shader.

layout(binding = 0) uniform samplerCube cubemap ;

layout(location = 0) in vec3 inTexCoord ;

layout(location = 0) out vec4 gAlbedoMetalness ;	// Albedo (RGB) + metalness (A)
layout(location = 1) out vec4 gEmissiveRoughness ;	// Emissive (RGB) + roughness (A)
layout(location = 2) out vec4 gAO ;					// Material AO
layout(location = 3) out vec4 gNormal ;

void main() {
	const float Metalness = 0.f ;
	const float Roughness = 0.f ;
	const float AO = 1.f ;
    const vec4 NoColor = vec4(0.f, 0.f, 0.f, 1.f) ;

    gAlbedoMetalness = vec4(texture(cubemap, inTexCoord).rgb, Metalness) ;
	gEmissiveRoughness = vec4(texture(cubemap, inTexCoord).rgb, Roughness) ;
	gAO = vec4(AO, vec3(0.f)) ;
    gNormal = vec4(NoColor.xy, 0.f, 0.f) ;
}
