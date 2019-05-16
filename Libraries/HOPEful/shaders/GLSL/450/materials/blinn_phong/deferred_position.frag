// Blinn-Phong material shader.
layout(location = 0) in vec4 vertexWorldPosition ;

out vec4 outColor ;

void main() {
    outColor = vertexWorldPosition ;
}
