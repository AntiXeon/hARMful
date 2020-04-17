const vec3 DefaultBaseReflectivity = vec3(0.04f) ;
const float Pi = 3.14159265359f ;

vec3 reflectivity(PBRFragmentData fragment) {
	return mix(DefaultBaseReflectivity, fragment.albedo, fragment.metalness) ;
}

vec3 fresnelSchlick(float cosTheta, vec3 f0) {
    return f0 + (1.f - f0) * pow(1.f - cosTheta, 5.f) ;
}

float ggxDistribution(float nDotH, float roughness) {
	float alpha = roughness * roughness ;
	float alphaSquared = alpha * alpha ;
	float nDotHSquared = nDotH * nDotH ;

	float fracDenom = nDotHSquared * (alphaSquared - 1.f) + 1.f ;
	fracDenom = Pi * fracDenom * fracDenom ;
	return alphaSquared / fracDenom ;
}

float geometrySchlickGGX(
	float nDotV,
	float roughness
) {
	float r = (roughness + 1.f) ;
	float k = (r * r) / 8.f ;

	float fracDenominator = nDotV * (1.f - k) + k ;
	return nDotV / fracDenominator ;
}

float geometrySmith(float dotProd, float roughness) {
	float k = (roughness + 1.f) * (roughness + 1.f) / 8.f ;
	float fracDenom = dotProd * (1.f - k) + k ;
	return 1.f / fracDenom ;
}

vec3 brdfCookTorrance(
	vec3 viewDirection,
	vec3 lightRadiance,
	vec3 lightDirection,
	PBRFragmentData fragment
) {
	vec3 f0 = reflectivity(fragment) ;

	vec3 n = fragment.normal ;
	vec3 v = viewDirection ;
	vec3 l = lightDirection ;
	vec3 h = normalize(v + l) ;
	float nDotH = max(dot( n, h ), 0.f) ;
	float lDotH = max(dot( l, h ), 0.f) ;
	float nDotL = max(dot( n, l ), 0.f) ;
	float nDotV = max(dot( n, v ), 0.f) ;

	float geomSmithNDotL = geometrySmith(nDotL, fragment.roughness) ;
	float geomSmithNDotV = geometrySmith(nDotV, fragment.roughness) ;

	vec3 f = fresnelSchlick(lDotH, f0) ;
	float g = geomSmithNDotL * geomSmithNDotV ;
	float ndf = ggxDistribution(nDotH, fragment.roughness) ;

	vec3 specBrdf = 0.25f * ndf * f * g ;
	return (fragment.albedo + Pi * specBrdf) * lightRadiance * nDotL ;
}
