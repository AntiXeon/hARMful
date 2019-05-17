// Blinn-Phong material shader.
layout(location = 0) in vec3 vertexWorldPosition ;

out vec4 outColor ;

void main() {
    outColor = vec4(vertexWorldPosition, 1.f) ;
}
