// Cubemap material shader.
layout(location = 0) out vec4 gAlbedo ;
layout(location = 1) out vec2 gNormal ;
layout(location = 2) out vec4 gSpecular ;

void main() {
    const vec4 NoColor = vec4(0.f, 0.f, 0.f, 1.f) ;
    gAlbedo = NoColor ;
    gNormal = NoColor.xy ;
    gSpecular = NoColor ;
}
