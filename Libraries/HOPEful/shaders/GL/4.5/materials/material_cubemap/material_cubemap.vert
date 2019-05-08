layout(location = 0) in vec3 position ;

layout(location = 0) out vec3 outTexCoord ;

void main() {
    outTexCoord = position ;

    const float FarPlaneDistance = 1000.f ;
    vec4 position4D = viewProjectionMatrix * vec4(position * FarPlaneDistance, 1.f) ;
    gl_Position = position4D.xyww ;
}
