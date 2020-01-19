// Cubemap material shader.

layout(binding = 0) uniform samplerCube cubemap ;

layout(location = 0) in vec3 inTexCoord ;

layout(location = 0) out vec4 gAlbedo ;
layout(location = 1) out vec4 gSpecular ;
layout(location = 2) out vec2 gNormal ;

void main() {
    const vec4 NoColor = vec4(0.f, 0.f, 0.f, 1.f) ;
    gAlbedo = texture(cubemap, inTexCoord) ;
    gNormal = NoColor.xy ;
    gSpecular = NoColor ;
}
