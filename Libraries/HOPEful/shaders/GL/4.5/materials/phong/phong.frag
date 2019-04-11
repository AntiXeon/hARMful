uniform vec3 eyePosition ;

layout(location = 0) in vec2 inTexCoord ;
layout(location = 1) in vec3 inNormal ;
layout(location = 2) in vec3 inFragmentPosition ;

out vec4 color ;

void main() {
    vec3 viewDirection = normalize(eyePosition - inFragmentPosition);
    color = DirectionalLightContribution(dirLight, inNormal, viewDirection) ;
}
