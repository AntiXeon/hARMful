// Screen-space ambient occlusion blur and copy.

layout(binding = 0) uniform sampler2D ao ;

layout(location = 0) in vec2 inTexCoords ;

out vec4 fragColor ;

void main() {
    vec2 texelSize = 1.f / vec2(textureSize(ao, 0)) ;

    float blurResult = 0.f ;
    for (int x = -2 ; x < 2 ; ++x) {
        for (int y = -2 ; y < 2 ; ++y) {
            vec2 offset = vec2(float(x), float(y)) * texelSize ;
            blurResult += texture(ao, inTexCoords + offset).a ;
        }
    }

    blurResult = blurResult / (4.f * 4.f) ;
    fragColor = vec4(texture(ao, inTexCoords).xyz, blurResult) ;
}
