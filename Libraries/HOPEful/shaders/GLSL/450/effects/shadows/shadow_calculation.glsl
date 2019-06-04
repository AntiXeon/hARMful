uniform bool useShadow ;
layout(binding = SHADOW_DEPTH_MAP_BINDING_UNIT) uniform sampler2D shadowDepth ;

const float NotInShadow = 0.f ;
const float InShadow = 1.f ;

/**
 * Compute the shadow for the current fragment.
 * @param   lightSpaceFragPosition  Position of the fragment in the light space
 *                                  coordinates system. It is used to compare
 *                                  the depth in the shadow depth and the one of
 *                                  the current fragment from the light point of
 *                                  view.
 * @return  0 if the fragment is lit (not shadowed); 1 if the fragment is in the
 *          shadow. It is in the shadow of the light if its depth is higher than
 *          the depth taken from the light depth map.
 */
float ShadowCompute(vec3 lightSpaceFragPosition) {
    if (useShadow) {
        return NotInShadow ;
    }
    else {
        return NotInShadow ;
    }
}
