// Material for deferred rendering (PBR). Applied on a simple quad on the whole
// viewport area.

layout(binding = 0) uniform sampler2DMS gAlbedoMetalness ;
layout(binding = 1) uniform sampler2DMS gEmissiveRoughness ;
layout(binding = 2) uniform sampler2DMS gAO ;
layout(binding = 3) uniform sampler2DMS gNormal ;
layout(binding = 4) uniform sampler2DMS gDepth ;
layout(location = 5) uniform int msaaQuality ;
layout(location = 6) uniform float exposure ;

// Image-based lighting related maps.
layout(binding = 10) uniform sampler2D iblBrdfLUT ;
layout(binding = 30) uniform samplerCube iblIrradiance ;
layout(binding = 40) uniform samplerCube iblSpecular ;

layout(location = 0) in vec2 inTexCoords ;

out vec3 outColor ;

const float Gamma = 2.2f ;

// TODO: Uniform value.
const float MaxReflectionLOD = 4.0f ;   // For 5 mipmap levels in [0-4].

void main() {
    const ivec2 FragCoords = ivec2(gl_FragCoord.xy) ;

	vec3 fragmentColor = vec3(0.f) ;
    PBRFragmentData currentFragment ;

    for (int sampleIndex = 0; sampleIndex < msaaQuality; ++sampleIndex) {
        // Note: The lighting computations are performed in view-space.
        // Get the view-space positions of the 3D objects from the pixel coordinates
        // and the depth buffer.
        float depthValue = texelFetch(gDepth, FragCoords, sampleIndex).r ;

        // Put values to perform the lighting pass for the current fragment.
        currentFragment.albedo = texelFetch(gAlbedoMetalness, FragCoords, sampleIndex).rgb ;
		currentFragment.metalness = texelFetch(gAlbedoMetalness, FragCoords, sampleIndex).a ;
		currentFragment.emissive = texelFetch(gEmissiveRoughness, FragCoords, sampleIndex).rgb ;
		currentFragment.roughness = texelFetch(gEmissiveRoughness, FragCoords, sampleIndex).a ;
		currentFragment.ao = texelFetch(gAO, FragCoords, sampleIndex).r ;
        currentFragment.normal = DecodeSpheremapNormals(texelFetch(gNormal, ivec2(gl_FragCoord), sampleIndex).rg) ;
        currentFragment.viewPosition = ComputeViewSpacePosition(inTexCoords, depthValue) ;
        currentFragment.depth = depthValue ;
        currentFragment.f0 = reflectivity(currentFragment.albedo, currentFragment.metalness) ;

        vec3 viewDirection = normalize(-currentFragment.viewPosition.xyz) ;

        // Compute ligh shading.
        vec3 lightsReflectance = ComputeLightsReflectance(
            viewDirection,
            currentFragment
        ) ;


        vec3 reflectVec = reflect(currentFragment.viewPosition.xyz, currentFragment.normal) ;
        reflectVec = normalize(mat3(inverseViewMatrix) * reflectVec) ;
        vec3 envSpecular = textureLod(
            iblSpecular,
            reflectVec,
            currentFragment.roughness * MaxReflectionLOD
        ).rgb ;

        vec2 envBrdf = texture(
            iblBrdfLUT,
            vec2(
                max(dot(viewDirection, currentFragment.normal), 0.f),
                currentFragment.roughness
            )
        ).rg ;

        // Get ambient color (IBL).
        float cosTheta = max(dot(currentFragment.normal, viewDirection), 0.f) ;
        vec3 f = fresnelSchlickRoughness(cosTheta, currentFragment.f0, currentFragment.roughness) ;
        vec3 kD = 1.f - f ;
        kD *= 1.f - currentFragment.metalness ;

        vec3 worldNormal = normalize(mat3(inverseViewMatrix) * currentFragment.normal).xyz ;
        vec3 irradiance = texture(iblIrradiance, worldNormal).rgb ;
        vec3 diffuse = irradiance * currentFragment.albedo ;
        vec3 specular = envSpecular * (f * envBrdf.x + envBrdf.y) ;
        vec3 ambientColor = (kD * diffuse + specular) * currentFragment.ao ;

        vec3 shadedColor = ambientColor + lightsReflectance ;

		// Apply fog.
        applyFog(abs(currentFragment.viewPosition.z), shadedColor) ;

		// Compute the skybox mask to include it in the final render.
        // 1. Get the normal mask based on the length of the normal vector (the
        //    skybox material gives [0,0,0,0] during the off-screen pass).
        // 2. Revsere the values of the normal mask to get the sky mask.
        // 3. Extract the diffuse color of the sky by multiplying by the mask.
        // 4. Merge shading color and sky diffuse color.
        float normalMask = clamp(ceil(length(texelFetch(gNormal, FragCoords, sampleIndex).rgb)), 0.f, 1f) ;
        shadedColor *= normalMask ; // remove fog from the skymap!
        float skyMask = 1.f - normalMask ;
        vec3 envMapColor = currentFragment.emissive * skyMask ;

		fragmentColor += shadedColor + envMapColor ;
    }

	fragmentColor /= msaaQuality ;
	fragmentColor = fragmentColor / (fragmentColor + vec3(1.f)) ;
    vec3 toneMappedColor = vec3(1.f) - exp(-fragmentColor * exposure) ;
	outColor = pow(toneMappedColor, vec3(1.f / Gamma)) ;
}
