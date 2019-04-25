// Phong material shader.

struct Material {
    vec3 ambientColor ;
    vec3 diffuseColor ;
    vec3 specularColor ;
    float shininess ;
} ;

uniform Material phong ;

const float ScreenGamma = 2.2f ;

layout(location = 0) in vec3 inVertexPosition ;
layout(location = 1) in vec3 inNormal ;
layout(location = 2) in vec2 inTexCoord ;

out vec4 outColor ;

vec3 ComputeDirectionalLight(
    DirectionalLight light,
    vec3 viewDirection,
    vec3 normal
) {
    vec3 returnedLighting = vec3(0.f) ;

    vec3 lightDirection = normalize(light.direction) ;
    float lambertian = max(dot(-lightDirection, normal), 0.f) ;
    float specular = float(light.generateSpecular == true) ;

    if (lambertian > 0.f) {
        vec3 reflectDirection = reflect(lightDirection, normal) ;
        float specularAngle = max(dot(reflectDirection, viewDirection), 0.f) ;
        specular *= pow(specularAngle, phong.shininess / 4.) ;

        vec3 lightPowerColor = light.color * light.power ;
        returnedLighting = (phong.diffuseColor * lambertian * lightPowerColor) ;
        returnedLighting += (phong.specularColor * specular * lightPowerColor) ;
    }

    return returnedLighting ;
}

vec3 ComputePointLight(
    PointLight light,
    vec3 viewDirection,
    vec3 normal
) {
    vec3 returnedLighting = vec3(0.f) ;

    vec3 lightDirection = normalize(inVertexPosition - light.position) ;
    float lambertian = max(dot(-lightDirection, normal), 0.f) ;
    float specular = float(light.generateSpecular == true) ;

    if (lambertian > 0.f) {
        vec3 reflectDirection = reflect(lightDirection, normal) ;
        float specularAngle = max(dot(reflectDirection, viewDirection), 0.f) ;
        specular *= pow(specularAngle, phong.shininess / 4.) ;

        float lightDistance = length(inVertexPosition - light.position) ;
        float sqrLightDistance = lightDistance * lightDistance ;
        float sqrFalloffDistance = light.falloffDistance * light.falloffDistance ;

        float lightLinearIntensity = light.falloffDistance / (light.falloffDistance + (light.linearAttenuation * lightDistance)) ;
        float lightQuadIntensity = sqrFalloffDistance / (sqrFalloffDistance + (light.quadraticAttenuation * sqrLightDistance)) ;
        float lightIntensity = light.power * lightLinearIntensity * lightQuadIntensity ;

        vec3 lightPowerColor = light.color * lightIntensity ;
        returnedLighting = (phong.diffuseColor * lambertian * lightPowerColor) ;
        returnedLighting += (phong.specularColor * specular * lightPowerColor) ;
    }

    return returnedLighting ;
}

void main() {
    vec3 normal = normalize(inNormal) ;
    vec3 viewDirection = normalize(-inVertexPosition) ;

    vec3 colorLinear = phong.ambientColor ;

    {
        // Contribution of directional lights.
        int validAmountOfDirLights = min(MAX_DIRECTIONAL_LIGHTS, amountDirectionalLights) ;
        for (int lightIndex = 0 ; lightIndex < validAmountOfDirLights ; lightIndex++) {
            colorLinear = colorLinear +
                ComputeDirectionalLight(
                    dirLights[lightIndex],
                    viewDirection,
                    normal
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
                    viewDirection,
                    normal
                ) ;
        }
    }

    vec3 colorGammaCorrected = pow(colorLinear, vec3(1.f / ScreenGamma)) ;
    outColor = vec4(colorGammaCorrected, 1.f) ;
}
