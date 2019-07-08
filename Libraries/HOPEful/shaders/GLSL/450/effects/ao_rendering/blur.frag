// Screen-space ambient occlusion blur and copy.

layout(binding = 0, rgba8ui) uniform coherent uimage2D gAlbedoAO ;
layout(binding = 1) uniform sampler2D ao ;

layout(location = 0) in vec2 inTexCoords ;

layout(location = 0) out vec4 albedoAO ;

void main() {
    ivec2 coordinates = ivec2(viewportSize * inTexCoords) ;
    uvec4 albedo = imageLoad(gAlbedoAO, coordinates) ;

    //albedoAO = vec4((albedo / 255.f).rgb, texture(ao, inTexCoords).r) ;

    albedoAO = vec4(1,0,0,1);

    // memoryBarrier() ;
    // imageStore(gAlbedoAO, coordinates, uvec4(albedo.rrr, texture(ao, inTexCoords).r)) ;
    // memoryBarrier() ;
}
