// Screen-space ambient occlusion.

layout(location = UNIFORM_AO_USE_LOCATION) uniform int useSSAO ;
layout(location = UNIFORM_AO_KERNEL_LOCATION) uniform vec3 kernel[AO_KERNEL_SIZE] ;
layout(binding = 0) uniform sampler2D albedo ;
layout(binding = 1) uniform sampler2D normal ;
layout(binding = 2) uniform sampler2D noise ;
layout(binding = 3) uniform sampler2D depth ;

layout(location = 0) in vec2 inTexCoords ;

layout(location = 0) out vec4 gAlbedoAO ;

// Texture coordinates of the noise texture for the current fragment.
vec2 noiseTextureCoords() {
    vec2 noiseTextureSize = textureSize(noise, 0) ;
    vec2 coordScaling = viewportSize / noiseTextureSize.x ;
    return inTexCoords * coordScaling ;
}

// Compute a TBN matrix with a random orientation.
mat3 computeTBNMatrix() {
    vec2 noiseTexCoords = noiseTextureCoords() ;
    vec3 random = normalize(texture(noise, noiseTexCoords).xyz) ;
    vec3 normal = DecodeSpheremapNormals(texture(normal, inTexCoords).xy) ;

    vec3 tangent = normalize(random - normal * dot(random, normal)) ;
    vec3 bitangent = cross(normal, tangent) ;
    return mat3(tangent, bitangent, normal) ;
}

// Compute the view-space position of the current fragment.
vec3 computePosition() {
    float depthValue = texture(depth, inTexCoords).r ;
    return ComputeViewSpacePosition(inTexCoords, depthValue).xyz ;
}

void main() {
    if (useSSAO == 1) {
        vec3 position = computePosition() ;
        mat3 tbnMatrix = computeTBNMatrix() ;

        float occlusion = 0.f ;
        for (int sampleIndex = 0 ; sampleIndex < AO_KERNEL_SIZE ; ++sampleIndex) {
            // Sample position.
            vec3 kernelSample = tbnMatrix * kernel[sampleIndex] ;
            kernelSample = position + (kernelSample * AO_RADIUS) ;

            // Project the sample onto the texture (screen-space position).
            vec4 offset = vec4(kernelSample, 1.f) ;
            offset = projectionMatrix * offset ;
            offset /= offset.w ;
            offset.xyz = offset.xyz * 0.5f + 0.5f ;

            // Kernel sample depth.
            float depthValue = texture(depth, offset.xy).r ;
            float sampleDepth = ComputeViewSpacePosition(offset.xy, depthValue).z ;

            // Range check and accumulate.
            float rangeCheck = smoothstep(0.f, 1.f, AO_RADIUS / abs(position.z - sampleDepth)) ;
            occlusion += (sampleDepth >= kernelSample.z + AO_BIAS ? 1.f : 0.f) * rangeCheck ;
        }

        //occlusion = 1.f - (occlusion / AO_KERNEL_SIZE) ;
        gAlbedoAO = vec4(texture(albedo, inTexCoords).rgb, occlusion) ;
    }
    else {
        gAlbedoAO = vec4(texture(albedo, inTexCoords).rgb, 1.f) ;
    }
}
