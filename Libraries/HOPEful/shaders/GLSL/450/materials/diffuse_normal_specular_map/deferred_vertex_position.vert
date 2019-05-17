// Diffuse/normal/specular material shader.
layout(location = 0) in vec3 position ;

layout(location = 0) out vec3 vertexWorldPosition ;

void main() {
    vec4 position4D = vec4(position, 1.f) ;
    gl_Position = mvpMatrix * position4D ;

    vertexWorldPosition = (modelMatrix * position4D).xyz ;
}
