struct DirectionalLight {
    // Direction of the light.
    vec3 direction ;

    // Color of the light.
    vec3 color ;

    // Power of the light.
    float power ;

    // Does the light produce a specular?
    bool generateSpecular ;
} ;

uniform DirectionalLight dirLights[MAX_DIRECTIONAL_LIGHTS] ;

struct PointLight {
    // Distance of the light effect.
    float falloffDistance ;

    // Color of the light.
    vec3 color ;

    // Power of the light.
    float power ;

    // Does the light produce a specular?
    bool generateSpecular ;
} ;

uniform PointLight pointLights[MAX_POINT_LIGHTS] ;
