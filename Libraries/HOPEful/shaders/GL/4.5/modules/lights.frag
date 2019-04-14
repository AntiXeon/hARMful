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
