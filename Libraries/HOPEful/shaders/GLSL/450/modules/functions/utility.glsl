vec3 AdjustNormalVector(mat3 tbnMatrix, vec3 normalValue) {
    vec3 adjustedNormalVector = normalize((normalValue * 2.f) - 1.f) ;
    adjustedNormalVector = normalize(tbnMatrix * adjustedNormalVector) ;
    return adjustedNormalVector ;
}
