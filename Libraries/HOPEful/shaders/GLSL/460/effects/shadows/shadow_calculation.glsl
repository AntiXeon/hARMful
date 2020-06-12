layout(location = UNIFORM_SHADOW_USE_LOCATION) uniform int useShadow ;
layout(location = UNIFORM_SHADOW_AMOUNT_CASCADE_LOCATION) uniform int amountCascades ;
layout(location = UNIFORM_SHADOW_CASCADED_SPLITS_LOCATION) uniform float cascadedSplits[MAX_AMOUNT_SHADOW_CASCADES] ;
layout(location = UNIFORM_SHADOW_CASCADE_MATRICES_LOCATION) uniform mat4 lightViewProjectionMatrices[MAX_AMOUNT_SHADOW_CASCADES] ;
layout(binding = SHADOW_DEPTH_MAP_BINDING_UNIT) uniform sampler2DArrayShadow cascadedDepthTexture ;

/**
 * Compute the distance of the given point from the camera location.
 * @param   Position to know the distance from the camera.
 * @return  Distance between the given position and the camera location.
 */
float distanceFromCamera(in vec4 position) {
    vec4 projectedPosition = projectionMatrix * position ;
    return projectedPosition.z / farPlaneDistance ;
}

/**
 * Compute the shadow for the current fragment.
 * @param   lightSpaceFragPosition  Position of the fragment in the light space
 *                                  coordinates system. It is used to compare
 *                                  the depth in the shadow depth and the one of
 *                                  the current fragment from the light point of
 *                                  view.
 * @return  1 if the fragment is lit (not shadowed); 0 if the fragment is in the
 *          shadow. It is in the shadow of the light if its depth is higher than
 *          the depth taken from the light depth map.
 */
float ShadowCompute(
    in vec3 lightDirection,
    in vec4 position,
    in vec3 normal,
    in float depth
) {
    float litFragment = 1.f ;

    if (useShadow == 0) {
        return litFragment ;
    }

    const float bias = max(0.01f * (1.f - dot(normal, lightDirection)), 0.001f) ;
    float distanceCamera = distanceFromCamera(position) ;

    // Select the right cascade index based on the distance of the fragment to
    // the camera.
    bool insideMap = false ;
    int selectedCascade = 0 ;
    for (int cascadeIndex = amountCascades - 1 ; cascadeIndex >= 0 ; cascadeIndex--) {
        if (distanceCamera < cascadedSplits[cascadeIndex]) {
            selectedCascade = cascadeIndex ;
            insideMap = true ;
            break ;
        }
    }

    if (insideMap) {
        vec4 projectionCoordinates ;
        vec4 worldPosition = inverseViewMatrix * position ;
        vec4 lightSpacePosition = lightViewProjectionMatrices[selectedCascade] * worldPosition ;
        projectionCoordinates.xyw = (lightSpacePosition.xyz / lightSpacePosition.w) * 0.5f + 0.5f ;
        projectionCoordinates.w = projectionCoordinates.w - bias ;
        projectionCoordinates.z = float(selectedCascade) ;

        litFragment = 0.f ;
        litFragment += textureOffset(cascadedDepthTexture, projectionCoordinates, ivec2(-1, -1)) ;
        litFragment += textureOffset(cascadedDepthTexture, projectionCoordinates, ivec2(-1,  1)) ;
        litFragment += textureOffset(cascadedDepthTexture, projectionCoordinates, ivec2( 0,  0)) ;
        litFragment += textureOffset(cascadedDepthTexture, projectionCoordinates, ivec2( 1, -1)) ;
        litFragment += textureOffset(cascadedDepthTexture, projectionCoordinates, ivec2( 1,  1)) ;
        return litFragment / 5.f ;
    }

    return 1.f ;
}
