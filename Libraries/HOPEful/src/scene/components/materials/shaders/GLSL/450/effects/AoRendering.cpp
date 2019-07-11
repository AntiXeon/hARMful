// WARNING: This file is automatically generated. Any manual modification will be removed.
#include <scene/components/materials/shaders/GLSL/450/effects/AoRendering.hpp>

std::string AoRenderingSsaoVertexCode =
"\
// Screen-space ambient occlusion.\n\
\n\
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

std::string AoRenderingBlurFragmentCode =
"\
// Screen-space ambient occlusion blur and copy.\n\
\n\
layout(binding = 0) uniform sampler2D ao ;\n\
\n\
layout(location = 0) in vec2 inTexCoords ;\n\
\n\
layout(location = 0) out vec4 gAlbedoAO ;\n\
\n\
void main() {\n\
    gAlbedoAO = texture(ao, inTexCoords).rgba ;\n\
}\n\
" ;

std::string AoRenderingSsaoFragmentCode =
"\
// Screen-space ambient occlusion.\n\
\n\
uniform int useSSAO ;\n\
uniform vec3 kernel[AO_KERNEL_SIZE] ;\n\
layout(binding = 0) uniform sampler2D albedo ;\n\
layout(binding = 1) uniform sampler2D normal ;\n\
layout(binding = 2) uniform sampler2D noise ;\n\
layout(binding = 3) uniform sampler2D depth ;\n\
\n\
layout(location = 0) in vec2 inTexCoords ;\n\
\n\
layout(location = 0) out vec4 gAlbedoAO ;\n\
\n\
// Texture coordinates of the noise texture for the current fragment.\n\
vec2 noiseTextureCoords() {\n\
    vec2 noiseTextureSize = textureSize(noise, 0) ;\n\
    vec2 coordScaling = viewportSize / noiseTextureSize.x ;\n\
    return inTexCoords * coordScaling ;\n\
}\n\
\n\
// Compute a TBN matrix with a random orientation.\n\
mat3 computeTBNMatrix() {\n\
    vec2 noiseTexCoords = noiseTextureCoords() ;\n\
    vec3 random = normalize(texture(noise, noiseTexCoords).xyz) ;\n\
    vec3 normal = DecodeSpheremapNormals(texture(normal, inTexCoords).xy) ;\n\
\n\
    vec3 tangent = normalize(random - normal * dot(random, normal)) ;\n\
    vec3 bitangent = cross(normal, tangent) ;\n\
    return mat3(tangent, bitangent, normal) ;\n\
}\n\
\n\
// Compute the view-space position of the current fragment.\n\
vec3 computePosition() {\n\
    float depthValue = texture(depth, inTexCoords).r ;\n\
    return ComputeViewSpacePosition(inTexCoords, depthValue).xyz ;\n\
}\n\
\n\
void main() {\n\
    if (useSSAO == 1) {\n\
        vec3 position = computePosition() ;\n\
        mat3 tbnMatrix = computeTBNMatrix() ;\n\
\n\
        float occlusion = 0.f ;\n\
        for (int sampleIndex = 0 ; sampleIndex < AO_KERNEL_SIZE ; ++sampleIndex) {\n\
            // Sample position.\n\
            vec3 kernelSample = tbnMatrix * kernel[sampleIndex] ;\n\
            kernelSample = position + (kernelSample * AO_RADIUS) ;\n\
\n\
            // Project the sample onto the texture (screen-space position).\n\
            vec4 offset = vec4(kernelSample, 1.f) ;\n\
            offset = projectionMatrix * offset ;\n\
            offset /= offset.w ;\n\
            offset.xyz = offset.xyz * 0.5f + 0.5f ;\n\
\n\
            // Kernel sample depth.\n\
            float depthValue = texture(depth, offset.xy).r ;\n\
            float sampleDepth = ComputeViewSpacePosition(offset.xy, depthValue).z ;\n\
\n\
            // Range check and accumulate.\n\
            float rangeCheck = smoothstep(0.f, 1.f, AO_RADIUS / abs(position.z - sampleDepth)) ;\n\
            occlusion += float(sampleDepth >= kernelSample.z + AO_BIAS) * rangeCheck ;\n\
        }\n\
\n\
        occlusion = 1.f - (occlusion / AO_KERNEL_SIZE) ;\n\
        gAlbedoAO = vec4(texture(albedo, inTexCoords).rgb, cos(time)) ;\n\
    }\n\
    else {\n\
        gAlbedoAO = vec4(texture(albedo, inTexCoords).rgb, sin(time)) ;\n\
    }\n\
}\n\
" ;

