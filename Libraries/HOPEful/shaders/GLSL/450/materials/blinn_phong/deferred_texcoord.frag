// Blinn-Phong material shader.
layout(location = 0) in vec2 texCoord ;

out vec4 outColor ;

void main() {
    outColor = vec4(texCoord, 0.f, 1.f) ;
}
