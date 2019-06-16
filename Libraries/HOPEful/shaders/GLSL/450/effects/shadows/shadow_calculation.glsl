layout(location = UNIFORM_SHADOW_USE_LOCATION) uniform int useShadow ;
layout(location = UNIFORM_SHADOW_AMOUNT_CASCADE_LOCATION) uniform int amountCascades ;
layout(location = UNIFORM_SHADOW_CASCADED_SPLITS_LOCATION) uniform float cascadedSplits[MAX_AMOUNT_SHADOW_CASCADES] ;
layout(location = UNIFORM_SHADOW_CASCADE_MATRICES_LOCATION) uniform mat4 lightViewProjectionMatrices[MAX_AMOUNT_SHADOW_CASCADES] ;
layout(binding = SHADOW_DEPTH_MAP_BINDING_UNIT) uniform sampler2DArray cascadedDepthTexture ;

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
    vec3 lightDirection,
    vec4 position,
    vec3 normal,
    float depth
) {
    float shadow = 0.f ;

    if (useShadow == 0) {
        return shadow ;
    }

    const float bias = max(0.001f * (1.f - dot(normal, lightDirection)), 0.0001f) ;
    float distanceCamera = length(abs(position.xyz - eyePosition)) / farPlaneDistance ;

    int selectedCascade = 0 ;
    for (int cascadeIndex = amountCascades - 1 ; cascadeIndex >= 0 ; cascadeIndex--) {
        if (distanceCamera < cascadedSplits[cascadeIndex]) {
            selectedCascade = cascadeIndex ;
            break ;
        }
    }

    vec3 projectionCoordinates ;
    vec4 worldPosition = inverseViewMatrix * position ;
    vec4 lightSpacePosition = lightViewProjectionMatrices[selectedCascade] * worldPosition ;
    projectionCoordinates = lightSpacePosition.xyz * 0.5f + 0.5f ;
    float shadowMapDepth = texture(cascadedDepthTexture, vec3(projectionCoordinates.xy, selectedCascade)).r ;


    float currentDepth = projectionCoordinates.z - bias ;

    if(currentDepth > 1.f) {
        return 1.f ;
    }
    else {
        return float(currentDepth < shadowMapDepth) ;
    }
}
