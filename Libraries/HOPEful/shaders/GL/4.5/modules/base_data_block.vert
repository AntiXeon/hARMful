layout (std140) uniform BaseData
{
    mat4 viewMatrix ;
    mat4 projectionMatrix ;
    mat4 viewProjectionMatrix ;
    mat4 inverseViewMatrix ;
    mat4 inverseProjectionMatrix ;
    mat4 inverseViewProjectionMatrix ;
    mat3 viewportMatrix ;
    mat3 inverseViewportMatrix ;
    float aspectRatio ;
    float time ;
    vec3 eyePosition ;
} ;
