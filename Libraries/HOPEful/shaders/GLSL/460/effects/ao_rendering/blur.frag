// Screen-space ambient occlusion blur and copy.
layout(binding = 1) uniform sampler2D ao ;

layout(location = 0) in vec2 inTexCoords ;

out vec4 fragColor ;

void main() {
    vec2 texelSize = vec2(1.f) / viewportSize ;

    float blurSamples = 0.f ;
    float blurResult = 0.f ;

    for (int x = -2 ; x <= 2 ; ++x) {
        for (int y = -2 ; y <= 2 ; ++y) {
            vec2 offset = vec2(float(x), float(y)) * texelSize ;
            blurResult += texture(ao, inTexCoords + offset).r ;
            blurSamples += 1.f ;
        }
    }

    blurResult = blurResult / blurSamples ;
    fragColor = vec4(blurResult) ;
}
