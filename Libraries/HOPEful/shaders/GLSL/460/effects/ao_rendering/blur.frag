// Screen-space ambient occlusion blur and copy.
layout(binding = 1) uniform sampler2D ao ;

layout(location = 0) in vec2 inTexCoords ;

out vec4 fragColor ;

void main() {
    vec2 texelSize = vec2(1.f) / viewportSize ;

    float blurResult = 0.f ;
    for (int x = -1 ; x <= 1 ; ++x) {
        for (int y = -1 ; y <= 1 ; ++y) {
            vec2 offset = vec2(float(x), float(y)) * texelSize ;
            blurResult += texture(ao, inTexCoords + offset).r ;
        }
    }

    blurResult = blurResult / 9.f ;
    fragColor = vec4(blurResult) ;
}
