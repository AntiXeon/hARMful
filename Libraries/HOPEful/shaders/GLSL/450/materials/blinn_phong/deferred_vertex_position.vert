layout(location = 0) in vec3 position ;

layout(location = 0) out vec4 vertexWorldPosition ;

void main() {
    vec4 position4D = vec4(position, 1.f) ;
    gl_Position = mvpMatrix * position4D ;

    vec4 vertexPosition4D = modelViewMatrix * position4D ;
    vertexWorldPosition = vec4(vertexPosition4D) / vertexPosition4D.w ;
}
