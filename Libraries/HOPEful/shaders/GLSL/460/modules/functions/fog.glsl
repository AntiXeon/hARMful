layout (std140, binding = FOG_DATA_UBO_BINDING_INDEX) uniform FogData
{
    vec4 color ;
    float minDistance ;
    float maxDistance ;
} fog ;
