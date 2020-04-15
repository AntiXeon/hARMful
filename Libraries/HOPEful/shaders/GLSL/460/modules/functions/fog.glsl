layout (std140, binding = FOG_DATA_UBO_BINDING_INDEX) uniform FogData
{
    vec4 color ;
    float minDistance ;
    float maxDistance ;
} fog ;

// Apply fog.
void applyFog(in float distance, inout vec3 shadedColor) {
    float fogFactor = (distance - fog.minDistance) / (fog.maxDistance - fog.minDistance) ;
    fogFactor = fog.color.a * clamp(fogFactor, 0.f, 1.f) ;

    shadedColor = mix(
        shadedColor,
        fog.color.rgb,
        fogFactor
    ) ;
}
