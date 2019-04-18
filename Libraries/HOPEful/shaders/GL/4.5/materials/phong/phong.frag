// Phong material shader.

struct Material {
    vec3 ambientColor ;
    vec3 diffuseColor ;
    vec3 specularColor ;
    float shininess ;
} ;

uniform Material phong ;
uniform vec3 eyePosition ;
uniform int amountDirectionalLights ;

const float ScreenGamma = 2.2f ;

layout(location = 0) in vec3 inVertexPosition ;
layout(location = 1) in vec3 inNormal ;
layout(location = 2) in vec2 inTexCoord ;

out vec4 outColor ;

vec3 ComputeLight(
    vec3 lightDirection,
    vec3 lightColor,
    float lightPower,
    bool generateSpecular,
    vec3 viewDirection,
    vec3 normal
) {
    vec3 returnedLighting ;
    float lambertian = max(dot(lightDirection, normal), 0.f) ;
    float specular = float(generateSpecular == true) ;

    if (lambertian > 0.f) {
        vec3 reflectDirection = reflect(-lightDirection, normal) ;
        float specularAngle = max(dot(reflectDirection, viewDirection), 0.f) ;
        specular *= pow(specularAngle, phong.shininess / 4.) ;

        vec3 lightPowerColor = lightColor * lightPower ;
        returnedLighting = (phong.diffuseColor * lambertian * lightPowerColor) ;
        returnedLighting += (phong.specularColor * specular * lightPowerColor) ;
    }

    return returnedLighting ;
}

void main() {
    int validAmountOfDirLights = min(MAX_DIRECTIONAL_LIGHTS, amountDirectionalLights) ;

    vec3 normal = normalize(inNormal) ;
    vec3 viewDirection = normalize(-inVertexPosition) ;

    vec3 colorLinear = phong.ambientColor ;

    for (int lightIndex = 0 ; lightIndex < validAmountOfDirLights ; lightIndex++) {
        vec3 lightDirection = normalize(dirLights[lightIndex].direction) ;

        colorLinear += ComputeLight(
            lightDirection,
            dirLights[lightIndex].color,
            dirLights[lightIndex].power,
            dirLights[lightIndex].generateSpecular,
            viewDirection,
            normal
        ) ;
    }

    vec3 colorGammaCorrected = pow(colorLinear, vec3(1.f / ScreenGamma)) ;
    outColor = vec4(colorLinear, 1.f) ;
}
