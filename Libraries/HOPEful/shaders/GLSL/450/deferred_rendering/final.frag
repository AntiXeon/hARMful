// Material for deferred rendering. Applied on a simple quad on the whole
// viewport area.

layout(binding = 0) uniform sampler2D albedo ;
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
    currentFragment.diffuseValue = texture(albedo, inTexCoords).rgb ;
    currentFragment.normalValue = DecodeSpheremapNormals(texture(normal, inTexCoords).xy) ;
    currentFragment.specularValue = texture(specular, inTexCoords).rgb ;
    currentFragment.shininess = texture(specular, inTexCoords).a ;
    currentFragment.position = viewSpacePosition.xyz ;

    // Compute ligh shading.
    vec3 viewDirection = normalize(-currentFragment.position) ;
    vec3 shadedColor = ComputeLightsContribution(
        viewDirection,
        currentFragment
    ) ;

    outColor = vec4(shadedColor, 1.f) ;
}
