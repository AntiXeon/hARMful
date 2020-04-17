// Physics-based rendering material shader.

layout(location =  0) uniform float albedoUseTexture ;
layout(location =  1) uniform vec3 albedoVertex ;
layout(binding =   2) uniform sampler2D albedoTexture ;

layout(location =  3) uniform float metalnessUseTexture ;
layout(location =  4) uniform float metalnessVertex ;
layout(binding =   5) uniform sampler2D metalnessTexture ;

layout(location =  6) uniform float emissiveUseTexture ;
layout(location =  7) uniform vec3 emissiveVertex ;
layout(binding =   8) uniform sampler2D emissiveTexture ;

layout(location =  9) uniform float roughnessUseTexture ;
layout(location = 10) uniform float roughnessVertex ;
layout(binding =  11) uniform sampler2D roughnessTexture ;

layout(location = 12) uniform float aoUseTexture ;
layout(location = 13) uniform float aoVertex ;
layout(binding =  14) uniform sampler2D aoTexture ;

layout(location = 15) uniform float normalUseTexture ;
layout(binding =  16) uniform sampler2D normalTexture ;

layout(location = 0) in vec2 inTexCoord ;
layout(location = 1) in vec3 inNormal ;
layout(location = 2) in mat3 inTBNMatrix ;

layout(location = 0) out vec4 gAlbedoMetalness ;	// Albedo (RGB) + metalness (A)
layout(location = 1) out vec4 gEmissiveRoughness ;	// Emissive (RGB) + roughness (A)
layout(location = 2) out vec4 gAO ;					// Material AO
layout(location = 3) out vec4 gNormal ;

/**
 * Select the color to use among vertex color and texture color.
 */
vec3 colorVSTexture(in float useTexture, in vec3 color, in vec3 texture) {
	vec3 textureColor = texture * useTexture ;
    vec3 vertexColor = color * (1.f - useTexture) ;
    return textureColor + vertexColor ;
}

/**
 * Select the value to use among vertex value and texture value.
 */
float valueVSTexture(in float useTexture, in float value, in float texture) {
	float textureValue = texture * useTexture ;
    float vertexValue = value * (1.f - useTexture) ;
    return textureValue + vertexValue ;
}

void main() {
	{
		// Albedo (RGB) + metalness (A)
		vec3 albedoColor = texture(albedoTexture, inTexCoord).rgb ;
		albedoColor = colorVSTexture(albedoUseTexture, albedoVertex, albedoColor) ;

		float metalnessValue = texture(metalnessTexture, inTexCoord).r ;
		metalnessValue = valueVSTexture(metalnessUseTexture, metalnessVertex, metalnessValue) ;

	    gAlbedoMetalness = vec4(albedoColor, metalnessValue) ;
	}

	{
		// Emissive (RGB) + roughness (A)
		vec3 emissiveColor = texture(emissiveTexture, inTexCoord).rgb ;
		emissiveColor = colorVSTexture(emissiveUseTexture, emissiveVertex, emissiveColor) ;

		float roughnessValue = texture(roughnessTexture, inTexCoord).r ;
		roughnessValue = valueVSTexture(roughnessUseTexture, roughnessVertex, roughnessValue) ;

		gEmissiveRoughness = vec4(emissiveColor, roughnessValue) ;
	}

	{
		// Material AO
		float aoValue = texture(aoTexture, inTexCoord).r ;
		aoValue = valueVSTexture(aoUseTexture, aoVertex, aoValue) ;

		gAO = vec4(aoValue, 0.f, 0.f, 0.f) ;
	}

	{
		// Normal
		vec3 normalVector = inNormal ;

		if (normalUseTexture > 0.5f) {
			normalVector = texture(normalTexture, inTexCoord).rgb ;
			normalVector = AdjustNormalVector(inTBNMatrix, normalVector) ;
		}

		gNormal = vec4(EncodeSpheremapNormals(normalVector), 0.f, 0.f) ;
	}
}
