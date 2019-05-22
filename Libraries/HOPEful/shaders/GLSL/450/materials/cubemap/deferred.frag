// Cubemap material shader.

uniform layout(binding = 0) samplerCube cubemap ;

layout(location = 0) in vec4 inPosition ;
layout(location = 1) in vec3 inTexCoord ;

layout(location = 0) out vec4 gAlbedo ;
layout(location = 1) out vec4 gNormal ;
layout(location = 2) out vec4 gSpecular ;
layout(location = 3) out vec4 gPosition ;

void main() {
    const vec4 NoColor = vec4(0.f, 0.f, 0.f, 1.f) ;
    gAlbedo = texture(cubemap, inTexCoord) ;
    gNormal = NoColor ;
    gSpecular = NoColor ;
    gPosition = inPosition ;
}
