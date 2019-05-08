layout (std140, binding = BASE_DATA_UBO_BINDING_INDEX) uniform BaseData
{
    mat4 viewMatrix ;
    mat4 projectionMatrix ;
    mat4 viewProjectionMatrix ;
    mat4 inverseViewMatrix ;
    mat4 inverseProjectionMatrix ;
    mat4 inverseViewProjectionMatrix ;
    mat3 viewportMatrix ;
    mat3 inverseViewportMatrix ;
    vec3 eyePosition ;
    float farPlaneDistance ;
    float aspectRatio ;
    float time ;
} ;
