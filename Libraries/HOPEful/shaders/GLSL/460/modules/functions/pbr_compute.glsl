const vec3 DefaultBaseReflectivity = vec3(0.04f) ;
const float Pi = 3.14159265359f ;

/**
 * Get the reflectivity of the current fragment.
 */
vec3 reflectivity(PBRFragmentData fragment) {
	return mix(DefaultBaseReflectivity, fragment.albedo, fragment.metalness) ;
}

/**
 * Fresnel-Schlick approximation.
 */
vec3 fresnelSchlick(float cosTheta, vec3 f0) {
    return f0 + (1.f - f0) * pow(1.f - cosTheta, 5.f) ;
}

float distributionGGX(
	float nDotH,
	float roughness
) {
	float alpha = roughness * roughness ;
	float alphaSquared = alpha * alpha ;
	float nDotHSquared = nDotH * nDotH ;

	float fracDenominator = ((nDotHSquared * (alphaSquared - 1.f)) + 1.f) ;
	fracDenominator = Pi * (fracDenominator * fracDenominator) ;

	return alphaSquared / fracDenominator ;
}

float geometrySchlickGGX(
	float nDotV,
	float roughness
) {
	float r = roughness + 1.f ;
	float k = (r * r) / 8.f ;

	float fracDenominator = nDotV * (1.f - k) + k ;
	return nDotV / fracDenominator ;
}

float geometrySmith(
	float nDotV,
	float nDotL,
	float roughness
) {
	float ggx1 = geometrySchlickGGX(nDotL, roughness) ;
	float ggx2 = geometrySchlickGGX(nDotV, roughness) ;

	return ggx1 * ggx2 ;
}

vec3 brdfCookTorrance(
	vec3 viewDirection,
	vec3 lightRadiance,
	vec3 lightDirection,
	PBRFragmentData fragment
) {
	vec3 v = viewDirection ;
	vec3 n = fragment.normal ;
	vec3 l = lightDirection ;
	vec3 h = normalize(v + l) ;
	vec3 f0 = reflectivity(fragment) ;

	float nDotH = max(0.f, dot(n, h)) ;
	float nDotV = max(0.f, dot(n, v)) ;
	float nDotL = max(0.f, dot(n, l)) ;

	float ndf = distributionGGX(nDotH, fragment.roughness) ;
	float g = geometrySmith(nDotV, nDotL, fragment.roughness) ;

	float hDotV = clamp(dot(h, v), 0.f, 1.f) ;
	vec3 f = fresnelSchlick(hDotV, f0) ;

	float nDotf = max(0.f, dot(n, f)) ;

	vec3 kS = f ;
	vec3 kD = vec3(1.f) - kS ;
	kD *= 1.f - fragment.metalness ;

	const float MinDenominator = 0.001f ;
	float fracDenominator = max(MinDenominator, 4.f * nDotV * nDotL) ;
	vec3 fracNumerator = ndf * g * f ;
	vec3 specular = fracNumerator / fracDenominator ;

	vec3 lightL0 = (kD * fragment.albedo / Pi + specular) * lightRadiance * nDotL ;
	return lightL0 ;
}
