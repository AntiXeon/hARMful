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
	float x = texCoords.x * 2.f - 1.f ;
	float y = texCoords.y * 2.f - 1.f ;
	float z = depth * 2.f - 1.f ;

	vec4 positionProjection = vec4(x, y, z, 1.f) ;
	vec4 positionView = inverseProjectionMatrix * positionProjection ;
	positionView /= positionView.w ;
	return positionView ;
}
