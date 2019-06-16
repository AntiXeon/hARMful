/**
 * Adjust a normal vector with a Tangent-Bitangent-Normal matrix.
 */
vec3 AdjustNormalVector(mat3 tbnMatrix, vec3 normalValue) {
    vec3 adjustedNormalVector = normalize((normalValue * 2.f) - 1.f) ;
    adjustedNormalVector = normalize(tbnMatrix * adjustedNormalVector) ;
    return adjustedNormalVector ;
}

/**
 * Retrieve a view space position from texture coordinates and depth.
 */
vec4 ComputeViewSpacePosition(vec2 texCoords, float depth) {
    vec2 adjustedTexCoords = texCoords * 2.f - 1.f ;
	float x = adjustedTexCoords.x ;
	float y = adjustedTexCoords.y ;
	float z = depth * 2.f - 1.f ;

	vec4 positionProjection = vec4(x, y, z, 1.f) ;
	vec4 positionView = inverseProjectionMatrix * positionProjection ;
    positionView /= positionView.w ;
	return positionView ;
}

/**
 * Encode normals using the Lambert azimuthal equal-area projection.
 * See http://aras-p.info/texts/CompactNormalStorage.html
 */
vec2 EncodeSpheremapNormals(vec3 normal) {
    vec3 normalizedNormal = normalize(normal) ;
    float zEncoding = sqrt(normalizedNormal.z * 8.f + 8.f) ;
    return (normalizedNormal.xy / zEncoding) + 0.5f ;
}

/**
 * Decode normals using the Lambert azimuthal equal-area projection.
 * See http://aras-p.info/texts/CompactNormalStorage.html
 */
vec3 DecodeSpheremapNormals(vec2 sphereNormal) {
    vec2 adjustedSphereNormal = sphereNormal * 4.f - 2.f ;
    float dotResult = dot(adjustedSphereNormal, adjustedSphereNormal) ;
    float zInverseDecoding = sqrt(1.f - dotResult / 4.f) ;

    vec3 decodedNormal = vec3(0.f) ;
    decodedNormal.xy = adjustedSphereNormal * zInverseDecoding ;
    decodedNormal.z = 1.f - dotResult / 2.f ;
    return decodedNormal ;
}
