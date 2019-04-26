struct DirectionalLight {
    // Direction of the light.
    vec3 direction ;

    // Color of the light.
    vec3 color ;

    // Power of the light.
    float power ;

    // Does the light produce a specular?
    float generateSpecular ;
} ;

struct PointLight {
    // Position of the light in the 3D space.
    vec3 position ;

    // Color of the light.
    vec3 color ;

    // Distance of the light effect.
    float falloffDistance ;

    // Linear attenuation of the light.
    float linearAttenuation ;

    // Quadratic attenuation of the light.
    float quadraticAttenuation ;

    // Power of the light.
    float power ;

    // Does the light produce a specular?
    float generateSpecular ;
} ;

layout (std140, binding = LIGHTS_DATA_UBO_BINDING_INDEX) uniform LightsData
{
    DirectionalLight dirLights[MAX_DIRECTIONAL_LIGHTS] ;
    PointLight pointLights[MAX_POINT_LIGHTS] ;
    int amountDirectionalLights ;
    int amountPointLights ;
} ;
