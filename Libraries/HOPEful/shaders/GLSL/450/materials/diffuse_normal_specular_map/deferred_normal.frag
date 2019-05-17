// Diffuse/normal/specular material shader.
layout(location = 0) in vec3 normal ;

out vec4 outColor ;

void main() {
    outColor = vec4(normalize(normal), 1.f) ;
}
