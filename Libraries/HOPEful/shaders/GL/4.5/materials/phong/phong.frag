uniform vec3 eyePosition ;
uniform int amountDirectionalLights ;

layout(location = 0) in vec2 inTexCoord ;
layout(location = 1) in vec3 inNormal ;
layout(location = 2) in vec3 inFragmentPosition ;

out vec4 color ;

void main() {
    int validAmountDirLights = min(amountDirectionalLights, MAX_DIRECTIONAL_LIGHTS) ;
    vec3 viewDirection = normalize(eyePosition - inFragmentPosition) ;

    vec4 colorAcc = vec4(0) ;
    for (int dirLightIndex = 0 ; dirLightIndex < validAmountDirLights ; dirLightIndex++) {
        colorAcc += DirectionalLightContribution(
            dirLights[dirLightIndex],
            inNormal,
            viewDirection
        ) ;
    }

    color = normalize(colorAcc) ;
}
