struct PBRFragmentData {
    // Position of the fragment.
    vec4 viewPosition ;
	vec4 worldPosition ;

    // Albedo color value.
    vec3 albedo ;

	// Emissive color value.
    vec3 emissive ;

    // Normal value.
    vec3 normal ;

    // Metalness value.
    float metalness ;

	// Roughness value.
	float roughness ;

	// AO from material.
	float ao ;

    // Depth of the fragment.
    float depth ;
} ;
