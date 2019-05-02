// Blinn-Phong material shader using a diffuse map.

struct Material {
    layout(binding = 0) sampler2D diffuseMap ;
    vec3 specularColor ;
    float shininess ;
} ;

uniform Material material ;

layout(location = 0) in vec3 inVertexWorldPosition ;
layout(location = 1) in vec3 inNormal ;
layout(location = 2) in vec2 inTexCoord ;
layout(location = 3) in vec3 inViewDirection ;

out vec4 outColor ;

vec3 ComputeDirectionalLight(
    DirectionalLight light,
    vec3 viewDirection,
    vec3 normal
) {
    vec3 returnedLighting = vec3(0.f) ;

    vec4 lightWorldDirection = normalMatrix * vec4(light.direction,1) ;
    vec3 lightDirection = normalize(-vec3(lightWorldDirection)) ;
    float lambertian = max(dot(lightDirection, normal), 0.0) ;
    vec3 reflectDirection = reflect(-lightDirection, normal) ;

    vec3 halfwayDirection = normalize(lightDirection + viewDirection) ;
    float specularAngle = max(dot(reflectDirection, viewDirection), 0.f) ;
    specularAngle *= pow(specularAngle, material.shininess) ;
    vec3 specularColor = light.generateSpecular * light.color * specularAngle ;

    vec3 lightPowerColor = light.color * light.power ;
    returnedLighting = (texture(material.diffuseMap, inTexCoord).rgb * lambertian * lightPowerColor) ;
    returnedLighting += (material.specularColor * specularColor * lightPowerColor) ;

    return returnedLighting ;
}

vec3 ComputePointLight(
    PointLight light,
    vec3 viewDirection,
    vec3 normal
) {
    vec3 returnedLighting = vec3(0.f) ;

    vec3 lightWorldPosition = vec3(modelViewMatrix * vec4(light.position, 1)) ;
    vec3 lightDirection = normalize(lightWorldPosition - inVertexWorldPosition) ;
    float lambertian = max(dot(lightDirection, normal), 0.0) ;
    vec3 reflectDirection = reflect(-lightDirection, normal) ;

    vec3 halfwayDirection = normalize(lightDirection + viewDirection) ;
    float specularAngle = max(dot(reflectDirection, viewDirection), 0.f) ;
    specularAngle *= pow(specularAngle, material.shininess) ;
    vec3 specularColor = light.generateSpecular * light.color * specularAngle ;

    float lightDistance = length(inVertexWorldPosition - light.position) ;
    float sqrLightDistance = lightDistance * lightDistance ;
    float sqrFalloffDistance = light.falloffDistance * light.falloffDistance ;

    float lightLinearIntensity = light.falloffDistance / (light.falloffDistance + (light.linearAttenuation * lightDistance)) ;
    float lightQuadIntensity = sqrFalloffDistance / (sqrFalloffDistance + (light.quadraticAttenuation * sqrLightDistance)) ;
    float lightIntensity = light.power * lightLinearIntensity * lightQuadIntensity ;

    vec3 lightPowerColor = light.color * lightIntensity ;
    returnedLighting = (texture(material.diffuseMap, inTexCoord).rgb * lambertian * lightPowerColor) ;
    returnedLighting += (material.specularColor * specularColor * lightPowerColor) ;

    return returnedLighting ;
}

void main() {
    vec3 colorLinear = vec3(0.f, 0.f, 0.f) ;

    {
        // Contribution of directional lights.
        int validAmountOfDirLights = min(MAX_DIRECTIONAL_LIGHTS, amountDirectionalLights) ;
        for (int lightIndex = 0 ; lightIndex < validAmountOfDirLights ; lightIndex++) {
            colorLinear = colorLinear +
                ComputeDirectionalLight(
                    dirLights[lightIndex],
                    inViewDirection,
                    inNormal
                ) ;
        }
    }

    {
        // Contribution of point lights.
        int validAmountOfPointLights = min(MAX_POINT_LIGHTS, amountPointLights) ;
        for (int lightIndex = 0 ; lightIndex < validAmountOfPointLights ; lightIndex++) {
            colorLinear = colorLinear +
                ComputePointLight(
                    pointLights[lightIndex],
                    inViewDirection,
                    inNormal
                ) ;
        }
    }

    outColor = vec4(colorLinear, 1.f) ;
}
