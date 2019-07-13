// Material for deferred rendering. Applied on a simple quad on the whole
// viewport area.

layout(binding = 0) uniform sampler2D albedoAO ;
layout(binding = 1) uniform sampler2D normal ;
layout(binding = 2) uniform sampler2D specular ;
layout(binding = 3) uniform sampler2D depth ;

layout(location = 0) in vec2 inTexCoords ;

out vec4 outColor ;

void main() {
    // Note: The lighting computations are performed in view-space.
    // Get the view-space positions of the 3D objects from the pixel coordinates
    // and the depth buffer.
    float depthValue = texture(depth, inTexCoords).r ;
    vec4 viewSpacePosition = ComputeViewSpacePosition(inTexCoords, depthValue) ;

    // Put values to perform the lighting pass for the current fragment.
    FragmentData currentFragment ;
    currentFragment.diffuseValue = texture(albedoAO, inTexCoords).rgb ;
    currentFragment.normalValue = DecodeSpheremapNormals(texture(normal, inTexCoords).xy) ;
    currentFragment.specularValue = texture(specular, inTexCoords).rgb ;
    currentFragment.shininess = texture(specular, inTexCoords).a ;
    currentFragment.position = viewSpacePosition ;
    currentFragment.depth = depthValue ;

    // Compute ligh shading.
    vec3 viewDirection = normalize(-currentFragment.position.xyz) ;
    vec3 shadedColor = ComputeLightsContribution(
        viewDirection,
        currentFragment
    ) ;

    // Compute the skybox mask to include it in the final render.
    // 1. Get the normal mask based on the length of the normal vector (the
    //    skybox material gives [0,0,0,0] during the off-screen pass).
    // 2. Revsere the values of the normal mask to get the sky mask.
    // 3. Extract the diffuse color of the sky by multiplying by the mask.
    // 4. Merge shading color and sky diffuse color.
    float normalMask = clamp(ceil(length(texture(normal, inTexCoords).rgb)), 0.f, 1f) ;
    float skyMask = 1.f - normalMask ;
    vec3 skyDiffuse = currentFragment.diffuseValue * skyMask ;

    outColor = vec4(shadedColor + skyDiffuse, 1.f) ;
    //outColor = vec4(vec3(texture(albedoAO, inTexCoords).rgb), 1.f) ;


    //#define DEBUG_CSM
    #ifdef DEBUG_CSM
        const vec3 CascadeColors[] = {
            vec3(1.f, 0.3f, 0.3f),
            vec3(0.3f, 1.f, 0.3f),
            vec3(0.3f, 0.3f, 1.f)
        } ;

       float distanceCamera = distanceFromCamera(currentFragment.position) ;
       int selectedCascade = 0 ;
        for (int cascadeIndex = amountCascades - 1 ; cascadeIndex >= 0 ; cascadeIndex--) {
            if (distanceCamera < cascadedSplits[cascadeIndex]) {
                selectedCascade = cascadeIndex ;
                break ;
            }
        }

        outColor += vec4(CascadeColors[selectedCascade], 0.f) ;
        normalize(outColor) ;
    #endif
}
