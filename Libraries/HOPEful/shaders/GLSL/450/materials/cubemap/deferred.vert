layout(location = 0) in vec3 position ;

layout(location = 0) out vec4 outPosition ;
layout(location = 1) out vec3 outTexCoord ;

void main() {
    outTexCoord = position ;

    vec4 position4D = viewProjectionMatrix * vec4(position * farPlaneDistance, 1.f) ;
    outPosition = position4D.xyww ;
    gl_Position = outPosition ;
}
