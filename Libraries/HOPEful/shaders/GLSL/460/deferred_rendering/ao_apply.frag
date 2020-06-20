// Material for applying computed ambient occlusion pass on the shaded
// rendering.

layout(binding = 0) uniform sampler2D rendering ;
layout(binding = 1) uniform sampler2D ambientOcclusion ;

layout(location = 0) in vec2 inTexCoords ;

out vec4 outColor ;

void main() {
    vec3 shadedPixel = texture(rendering, inTexCoords).rgb ;
    float aoPixel = texture(ambientOcclusion, inTexCoords).r ;
    outColor = vec4(shadedPixel * aoPixel, 1.f) ;
}
