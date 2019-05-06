/*** Data ***/
struct DirectionalLight {
    // Direction of the light.
    vec3 direction ;

    // Color of the light.
    vec3 color ;

    // Power of the light.
    float power ;

    // Does the light produce a specular?
    float generateSpecular ;
} ;

struct PointLight {
    // Position of the light in the 3D space.
    vec3 position ;

    // Color of the light.
    vec3 color ;

    // Distance of the light effect.
    float falloffDistance ;

    // Linear attenuation of the light.
    float linearAttenuation ;

    // Quadratic attenuation of the light.
    float quadraticAttenuation ;

    // Power of the light.
    float power ;

    // Does the light produce a specular?
    float generateSpecular ;
} ;

layout (std140, binding = LIGHTS_DATA_UBO_BINDING_INDEX) uniform LightsData
{
    DirectionalLight dirLights[MAX_DIRECTIONAL_LIGHTS] ;
    PointLight pointLights[MAX_POINT_LIGHTS] ;
    int amountDirectionalLights ;
    int amountPointLights ;
} ;


struct FragmentData {
    // Position of the fragment in the world.
    vec3 worldPosition ;

    // Diffuse color value.
    vec3 diffuseValue ;

    // Normal value.
    vec3 normalValue ;

    // Specular color value.
    vec3 specularValue ;

    // Shininess value.
    float shininess ;
} ;

/*** Functions ***/
/**
 * Compute the directional light contribution in a fragment shader.
 * @param   light           Data of the directional light.
 * @param   viewDirection   Direction of the view.
 * @param   fragment        Data on the processed fragment.
 * @return  Light contribution color.
 */
vec3 ComputeDirectionalLight(
    DirectionalLight light,
    vec3 viewDirection,
    FragmentData fragment
) {
    vec3 lightDirection = -light.direction ;
    lightDirection = normalize((viewMatrix * vec4(lightDirection, 0.f))).xyz ;
    float lambertian = max(dot(lightDirection, fragment.normalValue), 0.0) ;
    vec3 reflectDirection = reflect(-lightDirection, fragment.normalValue) ;

    vec3 halfwayDirection = normalize(lightDirection + viewDirection) ;
    float specularAngle = max(dot(reflectDirection, viewDirection), 0.f) ;
    specularAngle *= pow(specularAngle, fragment.shininess) ;
    vec3 specularColor = light.generateSpecular * light.color * specularAngle ;

    vec3 lightPowerColor = light.color * light.power ;
    vec3 returnedLighting = fragment.diffuseValue * lambertian * lightPowerColor ;
    returnedLighting += fragment.specularValue * specularColor * lightPowerColor ;

    return returnedLighting ;
}

/**
 * Compute the point light contribution in a fragment shader.
 * @param   light           Data of the point light.
 * @param   viewDirection   Direction of the view.
 * @param   fragment        Data on the processed fragment.
 * @return  Light contribution color.
 */
vec3 ComputePointLight(
    PointLight light,
    vec3 viewDirection,
    FragmentData fragment
) {
    vec3 lightDirection = normalize(light.position - fragment.worldPosition) ;
    float lambertian = max(dot(lightDirection, fragment.normalValue), 0.0) ;
    vec3 reflectDirection = reflect(-lightDirection, fragment.normalValue) ;

    vec3 halfwayDirection = normalize(lightDirection + viewDirection) ;
    float specularAngle = max(dot(reflectDirection, viewDirection), 0.f) ;
    specularAngle *= pow(specularAngle, fragment.shininess) ;
    vec3 specularColor = light.generateSpecular * light.color * specularAngle ;

    float lightDistance = length(fragment.worldPosition - light.position) ;
    float sqrLightDistance = lightDistance * lightDistance ;
    float sqrFalloffDistance = light.falloffDistance * light.falloffDistance ;

    float lightLinearIntensity = light.falloffDistance / (light.falloffDistance + (light.linearAttenuation * lightDistance)) ;
    float lightQuadIntensity = sqrFalloffDistance / (sqrFalloffDistance + (light.quadraticAttenuation * sqrLightDistance)) ;
    float lightIntensity = light.power * lightLinearIntensity * lightQuadIntensity ;

    vec3 lightPowerColor = light.color * lightIntensity ;
    vec3 returnedLighting = fragment.diffuseValue * lambertian * lightPowerColor ;
    returnedLighting += fragment.specularValue * specularColor * lightPowerColor ;

    return returnedLighting ;
}

/**
 * Compute the lights contribution in a fragment shader.
 * @param   viewDirection   Direction of the view.
 * @param   fragment        Data on the processed fragment.
 * @return  Color of the whole scene lights contribution.
 */
vec3 ComputeLightsContribution(
    vec3 viewDirection,
    FragmentData fragment
) {
    // Contribution of the directional light.
    vec3 colorLinear = ComputeDirectionalLight(
        dirLights[0],
        viewDirection,
        fragment
    ) ;

    // Contribution of point lights.
    int validAmountOfPointLights = min(MAX_POINT_LIGHTS, amountPointLights) ;
    for (int lightIndex = 0 ; lightIndex < validAmountOfPointLights ; lightIndex++) {
        colorLinear = colorLinear +
            ComputePointLight(
                pointLights[lightIndex],
                viewDirection,
                fragment
            ) ;
    }

    return colorLinear ;
}
