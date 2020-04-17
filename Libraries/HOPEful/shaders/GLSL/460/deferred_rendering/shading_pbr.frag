// Material for deferred rendering (PBR). Applied on a simple quad on the whole
// viewport area.

layout(binding = 0) uniform sampler2DMS gAlbedoMetalness ;
layout(binding = 1) uniform sampler2DMS gEmissiveRoughness ;
layout(binding = 2) uniform sampler2DMS gAO ;
layout(binding = 3) uniform sampler2DMS gNormal ;
layout(binding = 4) uniform sampler2DMS gDepth ;
// layout(binding = 5) uniform vec3 ambientLightColor ;
layout(location = 10) uniform int msaaQuality ;

layout(location = 0) in vec2 inTexCoords ;

out vec3 outColor ;

const float Gamma = 2.2f ;

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
		currentFragment.metalness = texelFetch(gAlbedoMetalness, FragCoords, sampleIndex).a ;	/**/
		currentFragment.emissive = texelFetch(gEmissiveRoughness, FragCoords, sampleIndex).rgb ;
		currentFragment.roughness = texelFetch(gEmissiveRoughness, FragCoords, sampleIndex).a ;
		currentFragment.ao = texelFetch(gAO, FragCoords, sampleIndex).r ;
        currentFragment.normal = normalize(DecodeSpheremapNormals(texelFetch(gNormal, FragCoords, sampleIndex).xy)) ;
        currentFragment.viewPosition = ComputeViewSpacePosition(inTexCoords, depthValue) ;
        currentFragment.depth = depthValue ;

        // Compute ligh shading.
		vec3 ambient = /*ambientLightColor **/ vec3(0.01f) * currentFragment.albedo * currentFragment.ao;

        vec3 viewDirection = normalize(-currentFragment.viewPosition.xyz) ;
        vec3 lightsReflectance = ComputeLightsReflectance(
            viewDirection,
            currentFragment
        ) ;

		vec3 shadedColor = ambient + lightsReflectance ;

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
        vec3 skyDiffuse = currentFragment.emissive * skyMask ;

        fragmentColor += shadedColor + skyDiffuse ;
    }

	fragmentColor /= msaaQuality ;

	fragmentColor = fragmentColor / (fragmentColor + vec3(1.f)) ;
	outColor = pow(fragmentColor, vec3(1.f / Gamma)) ;
}
