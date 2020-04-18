layout (std140, binding = LIGHTS_DATA_UBO_BINDING_INDEX) uniform LightsData
{
    DirectionalLight dirLights[MAX_DIRECTIONAL_LIGHTS] ;
    PointLight pointLights[MAX_POINT_LIGHTS] ;
    int amountDirectionalLights ;
    int amountPointLights ;
} ;

/*** Functions ***/
/**
 * Compute the directional light reflectance on a PBR fragment shader.
 * @param   light           Data of the directional light.
 * @param   viewDirection   Direction of the view.
 * @param   fragment        Data on the processed fragment.
 * @return  Light contribution color.
 */
vec3 ComputeDirectionalLightReflectance(
    DirectionalLight light,
    vec3 viewDirection,
    PBRFragmentData fragment
) {
	vec3 lightRadiance = light.color * light.power ;

	vec3 lightDirection = -light.direction ;
    lightDirection = normalize((viewMatrix * vec4(lightDirection, 0.f))).xyz ;

	float litFragment = ShadowCompute(
        lightDirection,
        fragment.viewPosition,
        fragment.normal,
        fragment.depth
    ) ;

	vec3 brdf = brdfCookTorrance(
		viewDirection,
		lightRadiance,
		lightDirection,
		fragment
	) ;

	return brdf * litFragment ;
}

/**
 * Compute the point light reflectance on a PBR fragment shader.
 * @param   light           Data of the point light.
 * @param   viewDirection   Direction of the view.
 * @param   fragment        Data on the processed fragment.
 * @return  Light contribution color.
 */
vec3 ComputePointLightReflectance(
    PointLight light,
    vec3 viewDirection,
    PBRFragmentData fragment
) {
	vec3 diffLighFragment = light.position - fragment.viewPosition.xyz ;

	float distance = length(diffLighFragment) ;
	float attenuation = 1.f / (distance * distance) ;
	vec3 lightRadiance = light.power * light.color * attenuation ;

	vec3 lightDirection = normalize(diffLighFragment) ;

	return brdfCookTorrance(
		viewDirection,
		lightRadiance,
		lightDirection,
		fragment
	) ;
}

/**
* Compute the reflectance of all the lights on a PBR fragment shader.
 * @param   viewDirection   Direction of the view.
 * @param   fragment        Data on the processed fragment.
 * @return  Color of the whole scene lights contribution.
 */
vec3 ComputeLightsReflectance(
    vec3 viewDirection,
    PBRFragmentData fragment
) {
	// Reflectance equation.
	vec3 totalL0 = vec3(0.f) ;

    // Contribution of the directional light.
    totalL0 += ComputeDirectionalLightReflectance(
        dirLights[0],
        viewDirection,
        fragment
    ) ;

    // Contribution of point lights.
    int validAmountOfPointLights = min(MAX_POINT_LIGHTS, amountPointLights) ;
    for (int lightIndex = 0 ; lightIndex < validAmountOfPointLights ; lightIndex++) {
        totalL0 += ComputePointLightReflectance(
            pointLights[lightIndex],
            viewDirection,
            fragment
        ) ;
    }

	totalL0 /= (amountDirectionalLights + amountPointLights) ;

    return (totalL0 * fragment.ao) + fragment.emissive ;
}
