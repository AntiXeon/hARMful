const vec3 DefaultBaseReflectivity = vec3(0.04f) ;
const float Pi = 3.14159265359f ;

vec3 reflectivity(in vec3 albedo, in float metalness) {
	return mix(DefaultBaseReflectivity, albedo, metalness) ;
}

vec3 fresnelSchlick(
    in float cosTheta,
    in vec3 f0
) {
    return f0 + (1.f - f0) * pow(1.f - cosTheta, 5.f) ;
}

vec3 fresnelSchlickRoughness(
    in float cosTheta,
    in vec3 f0,
    in float roughness
) {
    return f0 + (max(vec3(1.f - roughness), f0) - f0) * pow(1.f - cosTheta, 5.f) ;
}

float ggxDistribution(
    in float nDotH,
    in float roughness
) {
    float a = roughness * roughness ;
    float a2 = a * a ;
    float nDotH2 = nDotH * nDotH ;

    float nom = a2;
    float denom = (nDotH2 * (a2 - 1.f) + 1.f) ;
    denom = Pi * denom * denom ;

    return nom / denom ;
}

float geometrySchlickGGX(
	in float nDotV,
	in float roughness
) {
    float r = (roughness + 1.f) ;
    float k = (r * r) / 8.f ;

    float nom = nDotV ;
    float denom = nDotV * (1.f - k) + k ;

    return nom / denom ;
}

float geometrySmith(
    in float nDotV,
    in float nDotL,
    in float roughness
) {
    float ggx2 = geometrySchlickGGX(nDotV, roughness) ;
    float ggx1 = geometrySchlickGGX(nDotL, roughness) ;

    return ggx1 * ggx2 ;
}

vec3 brdfCookTorrance(
	in vec3 viewDirection,
	in vec3 lightRadiance,
	in vec3 lightDirection,
	inout PBRFragmentData fragment
) {
	vec3 n = fragment.normal ;
	vec3 v = viewDirection ;
	vec3 l = lightDirection ;
	vec3 h = normalize(v + l) ;
	float nDotH = max(dot(n, h), 0.f) ;
	float lDotH = max(dot(l, h), 0.f) ;
	float nDotL = max(dot(n, l), 0.f) ;
	float nDotV = max(dot(n, v), 0.f) ;
    float hDotV = max(dot(h, v), 0.f) ;

	vec3 f = fresnelSchlick(hDotV, fragment.f0) ;
    float g = geometrySmith(nDotV, nDotL, fragment.roughness) ;
	float ndf = ggxDistribution(nDotH, fragment.roughness) ;

    vec3 nominator = ndf * f * g ;
    float denominator = 4.f * nDotV * nDotL + 0.001f ;
    vec3 specular = nominator / denominator ;

    vec3 kS = f ;
    vec3 kD = vec3(1.f) - kS ;
    kD *= 1.f - fragment.metalness ;
    return (kD * fragment.albedo / Pi + specular) * lightRadiance * nDotL ;
}
