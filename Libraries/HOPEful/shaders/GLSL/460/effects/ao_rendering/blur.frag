// Screen-space ambient occlusion blur and copy.

layout(binding = 0) uniform sampler2DMS ao ;

layout(location = 0) in vec2 inTexCoords ;

out vec4 fragColor ;

void main() {
    ivec2 texSize = textureSize(ao) ;
    vec2 texelSize = 1.f / viewportSize ;

    float blurResult = 0.f ;
    for (int x = -1 ; x <= 1 ; ++x) {
        for (int y = -1 ; y <= 1 ; ++y) {
            vec2 offset = vec2(float(x), float(y)) * texelSize ;
            vec2 normalizedCoords = inTexCoords + offset ;
            blurResult += texelFetch(ao, ivec2(normalizedCoords * texSize), 0).a ;
        }
    }

    blurResult = blurResult / 9.f ;
    fragColor = vec4(texelFetch(ao, ivec2(gl_FragCoord), 0).xyz, blurResult) ;
}
