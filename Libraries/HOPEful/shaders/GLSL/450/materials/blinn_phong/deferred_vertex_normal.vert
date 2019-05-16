layout(location = 0) in vec3 position ;
layout(location = 2) in vec3 normal ;

layout(location = 0) out vec3 outNormal ;

void main() {
    gl_Position = mvpMatrix * vec4(position, 1.f) ;
    outNormal = normalize(vec3(normalMatrix * vec4(normal, 0.f))) ;
}
