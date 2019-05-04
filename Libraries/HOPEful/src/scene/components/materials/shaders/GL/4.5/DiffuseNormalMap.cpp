// WARNING: This file is automatically generated. Any manual modification will be removed.
#include <scene/components/materials/shaders/GL/4.5/DiffuseNormalMap.hpp>

std::string DiffuseNormalMapVertexCode =
"\
layout(location = 0) in vec3 position ;\n\
layout(location = 1) in vec2 texCoord ;\n\
layout(location = 2) in vec3 normal ;\n\
layout(location = 3) in vec3 tangent ;\n\
layout(location = 4) in vec3 bitangent ;\n\
\n\
layout(location = 0) out vec3 outVertexWorldPosition ;\n\
layout(location = 1) out vec3 outNormal ;\n\
layout(location = 2) out mat3 outTBNMatrix ;\n\
layout(location = 5) out vec2 outTexCoord ;\n\
layout(location = 6) out vec3 outViewDirection ;\n\
\n\
void correctTBNMatrix() {\n\
    vec3 correctedTangent = normalize(vec3(normalMatrix * vec4(tangent, 0.f))) ;\n\
    vec3 correctedBitangent = normalize(vec3(normalMatrix * vec4(bitangent, 0.f))) ;\n\
    vec3 correctedNormal = normalize(vec3(normalMatrix * vec4(normal, 0.f))) ;\n\
    outTBNMatrix = mat3(correctedTangent, correctedBitangent, correctedNormal) ;\n\
}\n\
\n\
void main() {\n\
    correctTBNMatrix() ;\n\
\n\
    vec4 position4D = vec4(position, 1.f) ;\n\
\n\
    gl_Position = mvpMatrix * position4D ;\n\
\n\
    vec4 vertexPosition4D = modelViewMatrix * vec4(position, 1.f) ;\n\
    outVertexWorldPosition = vec3(vertexPosition4D) / vertexPosition4D.w ;\n\
    outNormal = normalize(vec3(normalMatrix * vec4(normal, 0.f))) ;\n\
    outTexCoord = texCoord ;\n\
    outViewDirection = normalize(-outVertexWorldPosition) ;\n\
}\n\
" ;

std::string DiffuseNormalMapFragmentCode =
"\
// Blinn-Phong material shader using diffuse and normal maps.\n\
\n\
struct Material {\n\
    layout(binding = 0) sampler2D diffuse ;\n\
    layout(binding = 1) sampler2D normal ;\n\
    vec3 ambient ;\n\
    vec3 specular ;\n\
    float shininess ;\n\
} ;\n\
\n\
uniform Material material ;\n\
\n\
layout(location = 0) in vec3 inVertexWorldPosition ;\n\
layout(location = 1) in vec3 inNormal ;\n\
layout(location = 2) in mat3 inTBNMatrix ;\n\
layout(location = 5) in vec2 inTexCoord ;\n\
layout(location = 6) in vec3 inViewDirection ;\n\
\n\
out vec4 outColor ;\n\
\n\
vec3 ComputeDirectionalLight(\n\
    DirectionalLight light,\n\
    vec3 viewDirection,\n\
    vec3 normal\n\
) {\n\
    vec3 returnedLighting = vec3(0.f) ;\n\
\n\
    vec3 lightDirection = -light.direction ;\n\
    lightDirection = normalize((viewMatrix * vec4(lightDirection, 0.f))).xyz ;\n\
    float lambertian = max(dot(lightDirection, normal), 0.0) ;\n\
    vec3 reflectDirection = reflect(-lightDirection, normal) ;\n\
\n\
    vec3 halfwayDirection = normalize(lightDirection + viewDirection) ;\n\
    float specularAngle = max(dot(reflectDirection, viewDirection), 0.f) ;\n\
    specularAngle *= pow(specularAngle, material.shininess) ;\n\
    vec3 specularColor = light.generateSpecular * light.color * specularAngle ;\n\
\n\
    vec3 lightPowerColor = light.color * light.power ;\n\
    returnedLighting = (texture(material.diffuse, inTexCoord).rgb * lambertian * lightPowerColor) ;\n\
    returnedLighting += (material.specular * specularColor * lightPowerColor) ;\n\
\n\
    return returnedLighting ;\n\
}\n\
\n\
vec3 ComputePointLight(\n\
    PointLight light,\n\
    vec3 viewDirection,\n\
    vec3 normal\n\
) {\n\
    vec3 returnedLighting = vec3(0.f) ;\n\
\n\
    vec3 lightDirection = normalize(light.position - inVertexWorldPosition) ;\n\
    float lambertian = max(dot(lightDirection, normal), 0.0) ;\n\
    vec3 reflectDirection = reflect(-lightDirection, normal) ;\n\
\n\
    vec3 halfwayDirection = normalize(lightDirection + viewDirection) ;\n\
    float specularAngle = max(dot(reflectDirection, viewDirection), 0.f) ;\n\
    specularAngle *= pow(specularAngle, material.shininess) ;\n\
    vec3 specularColor = light.generateSpecular * light.color * specularAngle ;\n\
\n\
    float lightDistance = length(inVertexWorldPosition - light.position) ;\n\
    float sqrLightDistance = lightDistance * lightDistance ;\n\
    float sqrFalloffDistance = light.falloffDistance * light.falloffDistance ;\n\
\n\
    float lightLinearIntensity = light.falloffDistance / (light.falloffDistance + (light.linearAttenuation * lightDistance)) ;\n\
    float lightQuadIntensity = sqrFalloffDistance / (sqrFalloffDistance + (light.quadraticAttenuation * sqrLightDistance)) ;\n\
    float lightIntensity = light.power * lightLinearIntensity * lightQuadIntensity ;\n\
\n\
    vec3 lightPowerColor = light.color * lightIntensity ;\n\
    returnedLighting = (texture(material.diffuse, inTexCoord).rgb * lambertian * lightPowerColor) ;\n\
    returnedLighting += (material.specular * specularColor * lightPowerColor) ;\n\
\n\
    return returnedLighting ;\n\
}\n\
\n\
void main() {\n\
    vec3 colorLinear = material.ambient ;\n\
\n\
    vec3 normalMapVector = texture(material.normal, inTexCoord).rgb ;\n\
    normalMapVector = normalize((normalMapVector * 2.f) - 1.f) ;\n\
    normalMapVector = normalize(inTBNMatrix * normalMapVector) ;\n\
\n\
    {\n\
        // Contribution of directional lights.\n\
        int validAmountOfDirLights = min(MAX_DIRECTIONAL_LIGHTS, amountDirectionalLights) ;\n\
        for (int lightIndex = 0 ; lightIndex < validAmountOfDirLights ; lightIndex++) {\n\
            colorLinear = colorLinear +\n\
                ComputeDirectionalLight(\n\
                    dirLights[lightIndex],\n\
                    inViewDirection,\n\
                    normalMapVector\n\
                ) ;\n\
        }\n\
    }\n\
\n\
    {\n\
        // Contribution of point lights.\n\
        int validAmountOfPointLights = min(MAX_POINT_LIGHTS, amountPointLights) ;\n\
        for (int lightIndex = 0 ; lightIndex < validAmountOfPointLights ; lightIndex++) {\n\
            colorLinear = colorLinear +\n\
                ComputePointLight(\n\
                    pointLights[lightIndex],\n\
                    inViewDirection,\n\
                    normalMapVector\n\
                ) ;\n\
        }\n\
    }\n\
\n\
    outColor = vec4(colorLinear, 1.f) ;\n\
}\n\
" ;

