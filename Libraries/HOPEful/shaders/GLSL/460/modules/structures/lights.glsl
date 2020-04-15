/**
 * Structure to aggregate directional light data.
 */
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

/**
 * Structure to aggregate point light data.
 */
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
