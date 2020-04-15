// Screen-space ambient occlusion.

layout(location = UNIFORM_AO_USE_LOCATION) uniform int useSSAO ;
layout(location = UNIFORM_AO_KERNEL_LOCATION) uniform vec3 kernel[AO_KERNEL_SIZE] ;
layout(binding = 0) uniform sampler2DMS albedo ;
layout(binding = 1) uniform sampler2D noise ;
layout(binding = 3) uniform sampler2DMS normal ;
layout(binding = 4) uniform sampler2DMS depth ;

layout(location = 0) in vec2 inTexCoords ;

out vec4 fragColor ;

const float Epsilon = 0.0001f ;

// Compute the world position of the current fragment.
vec3 computeWorldPosition(vec2 texCoords) {
    ivec2 texSize = textureSize(depth) ;
    float depthValue = texelFetch(depth, ivec2(texCoords * texSize), 0).r ;
    return ComputeWorldSpacePosition(inTexCoords, depthValue).xyz ;
}

// Compute the view-space position of the current fragment.
vec3 computeViewSpacePosition(vec2 texCoords) {
    ivec2 texSize = textureSize(depth) ;
    float depthValue = texelFetch(depth, ivec2(texCoords * texSize), 0).r ;
    return ComputeViewSpacePosition(inTexCoords, depthValue).xyz ;
}

// Texture coordinates of the noise texture for the current fragment.
vec2 noiseTextureCoords() {
    vec2 coordScaling = viewportSize / AO_NOISE_TEXTURE_SIZE ;
    return inTexCoords * coordScaling ;
}

// Compute a TBN matrix with a random orientation.
mat3 computeTBNMatrix() {
    vec3 randDirection = normalize(texture(noise, noiseTextureCoords()).xyz) ;
    vec3 normalValue = DecodeSpheremapNormals(texelFetch(normal, ivec2(gl_FragCoord), 0).xy) ;
    vec3 bitangent = cross(normalValue, randDirection) ;

    if (length(bitangent) < Epsilon) {
        bitangent = cross(normalValue, vec3(0,0,1)) ;
    }

    bitangent = normalize(bitangent) ;
    vec3 tangent = cross(bitangent, normalValue) ;
    return mat3(tangent, bitangent, normalValue) ;
}

void main() {
    float occlusion = 1.f ;

    if (useSSAO == 1) {
        vec3 worldPosition = computeViewSpacePosition(inTexCoords) ;
        mat3 tbnMatrix = computeTBNMatrix() ;

        occlusion = 0.f ;
        for (int sampleIndex = 0 ; sampleIndex < AO_KERNEL_SIZE ; ++sampleIndex) {
            // Sample position.
            vec3 kernelSample = tbnMatrix * kernel[sampleIndex] ;
            kernelSample = worldPosition + AO_RADIUS * kernelSample ;

            // Project the sample onto the texture (screen-space position).
            vec4 offset = vec4(kernelSample, 1.f) ;
            offset = projectionMatrix * offset ;
            offset.xyz /= offset.w ;
            offset.xyz = offset.xyz * 0.5f + 0.5f ;

            // Kernel sample depth.
            float sampleDepth = computeViewSpacePosition(offset.xy).z ;
            float EpsilonZ = sampleDepth - worldPosition.z ;

            // Range check and accumulate points that are occluded.
            float rangeCheck = smoothstep(0.f, 1.f, AO_RADIUS / EpsilonZ) ;
            occlusion += (sampleDepth >= (kernelSample.z + AO_BIAS) ? 1.f : 0.f) * rangeCheck ;
        }

        occlusion = 1.f - (occlusion / AO_KERNEL_SIZE) ;
    }

    fragColor = vec4(occlusion) ;
}
