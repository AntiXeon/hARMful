layout(location = 0) in vec3 position ;

layout(location = 0) out vec3 outTexCoord ;

void main() {
    outTexCoord = position ;

    vec4 position4D = viewProjectionMatrix * vec4(position * farPlaneDistance, 1.f) ;
    gl_Position = position4D.xyww ;
}
