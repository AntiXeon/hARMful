// WARNING: This file is automatically generated. Any manual modification will be removed.
#include <scene/components/materials/shaders/GLSL/450/DeferredRendering.hpp>

std::string DeferredRenderingFinalFragmentCode =
"\
// Material for deferred rendering. Applied on a simple quad on the whole\n\
// viewport area.\n\
\n\
layout(binding = 0) uniform sampler2D albedo ;\n\
layout(binding = 1) uniform sampler2D normal ;\n\
layout(binding = 2) uniform sampler2D specular ;\n\
layout(binding = 3) uniform sampler2D depth ;\n\
\n\
layout(location = 0) in vec2 inTexCoords ;\n\
\n\
out vec4 outColor ;\n\
\n\
void main() {\n\
    // Note: The lighting computations are performed in view-space.\n\
    // Get the view-space positions of the 3D objects from the pixel coordinates\n\
    // and the depth buffer.\n\
    float depthValue = texture(depth, inTexCoords).r ;\n\
    vec4 viewSpacePosition = ComputeViewSpacePosition(inTexCoords, depthValue) ;\n\
\n\
    // Put values to perform the lighting pass for the current fragment.\n\
    FragmentData currentFragment ;\n\
    currentFragment.diffuseValue = texture(albedo, inTexCoords).rgb ;\n\
    currentFragment.normalValue = DecodeSpheremapNormals(texture(normal, inTexCoords).xy) ;\n\
    currentFragment.specularValue = texture(specular, inTexCoords).rgb ;\n\
    currentFragment.shininess = texture(specular, inTexCoords).a ;\n\
    currentFragment.position = viewSpacePosition ;\n\
    currentFragment.depth = depthValue ;\n\
\n\
    // Compute ligh shading.\n\
    vec3 viewDirection = normalize(-currentFragment.position.xyz) ;\n\
    vec3 shadedColor = ComputeLightsContribution(\n\
        viewDirection,\n\
        currentFragment\n\
    ) ;\n\
\n\
    // Compute the skybox mask to include it in the final render.\n\
    // 1. Get the normal mask based on the length of the normal vector (the\n\
    //    skybox material gives [0,0,0,0] during the off-screen pass).\n\
    // 2. Revsere the values of the normal mask to get the sky mask.\n\
    // 3. Extract the diffuse color of the sky by multiplying by the mask.\n\
    // 4. Merge shading color and sky diffuse color.\n\
    float normalMask = clamp(ceil(length(texture(normal, inTexCoords).rgb)), 0.f, 1f) ;\n\
    float skyMask = 1.f - normalMask ;\n\
    vec3 skyDiffuse = currentFragment.diffuseValue * skyMask ;\n\
\n\
    outColor = vec4(shadedColor + skyDiffuse, 1.f) ;\n\
\n\
\n\
    #define DEBUG_CSM\n\
    #ifdef DEBUG_CSM\n\
        const vec3 CascadeColors[] = {\n\
            vec3(1.f, 0.3f, 0.3f),\n\
            vec3(0.3f, 1.f, 0.3f),\n\
            vec3(0.3f, 0.3f, 1.f)\n\
        } ;\n\
\n\
       float distanceCamera = distanceFromCamera(currentFragment.position) ;\n\
       int selectedCascade = 0 ;\n\
        for (int cascadeIndex = amountCascades - 1 ; cascadeIndex >= 0 ; cascadeIndex--) {\n\
            if (distanceCamera < cascadedSplits[cascadeIndex]) {\n\
                selectedCascade = cascadeIndex ;\n\
                break ;\n\
            }\n\
        }\n\
\n\
        outColor += vec4(CascadeColors[selectedCascade], 0.f) ;\n\
        normalize(outColor) ;\n\
    #endif\n\
}\n\
" ;

std::string DeferredRenderingFinalVertexCode =
"\
layout(location = 0) in vec3 position ;\n\
layout(location = 1) in vec2 texCoords ;\n\
\n\
layout(location = 0) out vec2 outTexCoords ;\n\
\n\
void main() {\n\
    outTexCoords = texCoords ;\n\
    gl_Position = vec4(position, 1.f) ;\n\
}\n\
" ;

